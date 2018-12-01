#include <unordered_set>
#include <bitset>
#include <cstdio>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GDT/GameLoop.hpp>
#include <GDT/CollisionDetection.hpp>
#include <EC/Manager.hpp>

#include "ECStuff.hpp"

#define DELTA_TIME (1.0f / 120.0f)
#define GRAVITY_ACC 5000.0f
#define VEL_DAMPENING 1.4f
#define JUMP_VEL 2400.0f
#define MOVE_SPEED 120.0f

#define PARTICLE1_GENTIME 0.2f
#define PARTICLE1_GEN_LIFETIME 0.7f

#define RNG_PART_VEL 400.0f
#define RNG_PART_ACC 200.0f

/*
 * 0 - move left
 * 1 - move right
 * 2 - is grounded
 * 3 - is player
 * 4 - is exit
 * 5 - is fragment
 * 6 - is fragment pick-upable (after player no longer collides with it)
 * 7 - collided with player
 * 8 - is particle
 */
using BitsetT = std::bitset<32>;

using AllComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Vel,
    ECStuff::Acc,
    ECStuff::Size,
    ECStuff::Drawable,
    BitsetT,
    ECStuff::ParticleGen
>;

using PhysComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Vel,
    ECStuff::Acc,
    ECStuff::Size
>;

using ColComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Size
>;

using ColFinComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Vel
>;

using DrawComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Size,
    ECStuff::Drawable
>;

using FragmentComponents = EC::Meta::TypeList<
    BitsetT
>;

using ParticleComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Size,
    ECStuff::ParticleGen
>;

using AllTags = EC::Meta::TypeList<
>;

using ManagerT = EC::Manager<AllComponents, AllTags>;

struct Context
{
    ManagerT* manager;
    std::unordered_set<std::size_t> revertPos;
    BitsetT globalFlags;
    std::unordered_map<unsigned int, sf::SoundBuffer> sfxMap;
    std::vector<sf::Sound> soundPool;
    std::size_t playerID;
    std::default_random_engine rng;
    unsigned int currentSize;

    /*
     * globalFlags:
     * 0 - exit reached
     * 1 - is player dead
     */

    /*
     * sfxMap:
     * 0 - sfx_goalreached.ogg
     * 1 - sfx_jump.ogg
     */

    void playSfx(const unsigned int& id)
    {
        try
        {
            sf::SoundBuffer& buf = sfxMap.at(id);
            for(auto iter = soundPool.begin(); iter != soundPool.end(); ++iter)
            {
                if(iter->getStatus() != sf::SoundSource::Playing)
                {
                    iter->setBuffer(buf);
                    iter->play();
                    break;
                }
            }
        } catch(const std::out_of_range& e)
        {
            fprintf(stderr, "ERROR: Context::playSfx got invalid sound id \"%d\"!", id);
        }
    }
};

void resetWorld(const std::unordered_set<std::size_t> preserveSet, ManagerT& manager)
{
    manager.forMatchingSignature<EC::Meta::TypeList<>>(
        [&preserveSet] (std::size_t id, void* ptr) {
            if(preserveSet.find(id) == preserveSet.end())
            {
                ManagerT* manager = (ManagerT*)ptr;
                manager->deleteEntity(id);
            }
        },
        &manager);
}

void loadLevel(const unsigned int id, ManagerT& manager)
{
    switch(id)
    {
    case 0:
    {
        auto id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 100.0f, 270.0f - 50.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 200.0f, 270.0f - 100.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 100.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 300.0f, 270.0f - 150.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 150.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);

        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 435.0f, 270.0f - 40.0f);
        manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        manager.addComponent<BitsetT>(id);
        manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 1:
    {
        auto id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 300.0f, 270.0f - 50.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);
    }
        break;
    default:
        fprintf(stderr, "ERROR: loadLevel got invalid level id!\n");
        break;
    }
}

int main(int argc, char** argv)
{
    Context context;
    context.currentSize = 50;

    // sounds
    context.soundPool.resize(7);

    context.sfxMap.insert(std::make_pair(0, sf::SoundBuffer{}));
    context.sfxMap.at(0).loadFromFile("sfx_goalreached.ogg");

    context.sfxMap.insert(std::make_pair(1, sf::SoundBuffer{}));
    context.sfxMap.at(1).loadFromFile("sfx_jump.ogg");

    // set up manager
    ManagerT manager;
    context.manager = &manager;

    // physics update x
    manager.addForMatchingFunction<PhysComponents>(
        [] (std::size_t id, void* ptr, ECStuff::Pos* pos, ECStuff::Vel* vel,
                ECStuff::Acc* acc, ECStuff::Size* size) {
            Context* context = (Context*)ptr;
            pos->px = pos->x;

            vel->x += acc->x * DELTA_TIME;
            if(context->manager->hasComponent<BitsetT>(id))
            {
                BitsetT* bitset = context->manager->getEntityData<BitsetT>(id);
                if(bitset->test(0) && !bitset->test(1) && vel->x > -MOVE_SPEED)
                {
                    vel->x = -MOVE_SPEED;
                }
                else if(bitset->test(1) && !bitset->test(0) && vel->x < MOVE_SPEED)
                {
                    vel->x = MOVE_SPEED;
                }
            }
            pos->x += vel->x * DELTA_TIME;

            vel->x /= VEL_DAMPENING;
        },
        &context);
    // collision detection x
    manager.addForMatchingFunction<ColComponents>(
        [] (std::size_t id, void* ptr, ECStuff::Pos* pos, ECStuff::Size* size) {
            Context* context = (Context*)ptr;
            if(context->manager->hasComponent<BitsetT>(id)
                && context->manager->getEntityData<BitsetT>(id)->test(8))
            {
                // do not collision check particles
                return;
            }
            float points[8] = {
                pos->x          , pos->y,
                pos->x + size->w, pos->y,
                pos->x + size->w, pos->y + size->h,
                pos->x,           pos->y + size->h
            };
            context->manager->forMatchingSignature<ColComponents>(
                [&context, &id, &points] (std::size_t cid, void* ptr,
                        ECStuff::Pos* pos, ECStuff::Size* size) {
                    if(id != cid)
//                        && context->revertPos.find(cid) == context->revertPos.end())
                    {
                        if(context->manager->hasComponent<BitsetT>(cid)
                            && context->manager->getEntityData<BitsetT>(cid)->test(8))
                        {
                            // do not collision check particles
                            return;
                        }
                        else if(GDT::isWithinPolygon(points, 8, pos->x, pos->y)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y + size->h)
                            || GDT::isWithinPolygon(points, 8, pos->x, pos->y + size->h)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w / 2.0f, pos->y + size->h / 2.0f))
                        {
                            if(context->manager->hasComponent<BitsetT>(id)
                                && context->manager->hasComponent<BitsetT>(cid)
                                && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                        && context->manager->getEntityData<BitsetT>(cid)->test(4))
                                    || (context->manager->getEntityData<BitsetT>(id)->test(4)
                                        && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                            {
                                // is colliding with exit
                                context->globalFlags.set(0);
                            }
                            else if(context->manager->hasComponent<BitsetT>(id)
                                && context->manager->hasComponent<BitsetT>(cid)
                                && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                        && context->manager->getEntityData<BitsetT>(cid)->test(5))
                                    || (context->manager->getEntityData<BitsetT>(id)->test(5)
                                        && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                            {
                                // is colliding with fragment
                                if(context->manager->getEntityData<BitsetT>(id)->test(5))
                                {
                                    context->manager->getEntityData<BitsetT>(id)->set(7);
                                }
                                else
                                {
                                    context->manager->getEntityData<BitsetT>(cid)->set(7);
                                }
                            }
                            else
                            {
                                context->revertPos.insert(id);
                                context->revertPos.insert(cid);
                            }
                        }
                    }
                },
                nullptr);
        },
        &context);
    // finalize collision detection x
    manager.addForMatchingFunction<ColFinComponents>(
        [] (std::size_t id, void* ptr, ECStuff::Pos* pos, ECStuff::Vel* vel) {
            Context* context = (Context*)ptr;
            if(context->revertPos.find(id) != context->revertPos.end())
            {
                vel->x = pos->px - pos->x;
                pos->x = pos->px;
//                vel->x = 0.0f;
                context->revertPos.erase(id);
            }
        },
        &context);
    // physics update y
    manager.addForMatchingFunction<PhysComponents>(
        [] (std::size_t id, void* ptr, ECStuff::Pos* pos, ECStuff::Vel* vel,
                ECStuff::Acc* acc, ECStuff::Size* size) {
            pos->py = pos->y;

            vel->y += acc->y * DELTA_TIME;
            pos->y += vel->y * DELTA_TIME;

            vel->y /= VEL_DAMPENING;
        },
        nullptr);
    // collision detection y
    manager.addForMatchingFunction<ColComponents>(
        [] (std::size_t id, void* ptr, ECStuff::Pos* pos, ECStuff::Size* size) {
            Context* context = (Context*)ptr;
            if(context->manager->hasComponent<BitsetT>(id)
                && context->manager->getEntityData<BitsetT>(id)->test(8))
            {
                // do not collision check particles
                return;
            }
            float points[8] = {
                pos->x          , pos->y,
                pos->x + size->w, pos->y,
                pos->x + size->w, pos->y + size->h,
                pos->x,           pos->y + size->h
            };
            context->manager->forMatchingSignature<ColComponents>(
                [&context, &id, &points] (std::size_t cid, void* ptr,
                        ECStuff::Pos* pos, ECStuff::Size* size) {
                    if(id != cid)
//                        && context->revertPos.find(cid) == context->revertPos.end())
                    {
                        if(context->manager->hasComponent<BitsetT>(cid)
                            && context->manager->getEntityData<BitsetT>(cid)->test(8))
                        {
                            // do not collision check particles
                            return;
                        }
                        else if(GDT::isWithinPolygon(points, 8, pos->x, pos->y)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y + size->h)
                            || GDT::isWithinPolygon(points, 8, pos->x, pos->y + size->h)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w / 2.0f, pos->y + size->h / 2.0f))
                        {
                            if(context->manager->hasComponent<BitsetT>(id)
                                && context->manager->hasComponent<BitsetT>(cid)
                                && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                        && context->manager->getEntityData<BitsetT>(cid)->test(4))
                                    || (context->manager->getEntityData<BitsetT>(id)->test(4)
                                        && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                            {
                                // is colliding with exit
                                context->globalFlags.set(0);
                            }
                            else if(context->manager->hasComponent<BitsetT>(id)
                                && context->manager->hasComponent<BitsetT>(cid)
                                && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                        && context->manager->getEntityData<BitsetT>(cid)->test(5))
                                    || (context->manager->getEntityData<BitsetT>(id)->test(5)
                                        && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                            {
                                // is colliding with fragment
                                if(context->manager->getEntityData<BitsetT>(id)->test(5))
                                {
                                    context->manager->getEntityData<BitsetT>(id)->set(7);
                                }
                                else
                                {
                                    context->manager->getEntityData<BitsetT>(cid)->set(7);
                                }
                            }
                            else
                            {
                                context->revertPos.insert(id);
                                context->revertPos.insert(cid);
                            }
                        }
                    }
                },
                nullptr);
        },
        &context);
    // finalize collision detection y
    manager.addForMatchingFunction<ColFinComponents>(
        [] (std::size_t id, void* ptr, ECStuff::Pos* pos, ECStuff::Vel* vel) {
            Context* context = (Context*)ptr;
            if(context->revertPos.find(id) != context->revertPos.end())
            {
                vel->y = pos->py - pos->y;
                if(context->manager->hasComponent<BitsetT>(id) && vel->y < 0.0f)
                {
                    context->manager->getEntityData<BitsetT>(id)->set(2);
                }
                pos->y = pos->py;
//                vel->y = 0.0f;
                context->revertPos.erase(id);
            }
        },
        &context);
    // check fragments
    manager.addForMatchingFunction<FragmentComponents>(
        [] (std::size_t id, void* ptr, BitsetT* bitset) {
            if(bitset->test(5))
            {
                if(bitset->test(7))
                {
                    Context* context = (Context*)ptr;
                    if(bitset->test(6) && !context->globalFlags.test(1))
                    {
                        // player touched fragment, increase player
                        context->manager->deleteEntity(id);
                        ECStuff::Pos* ppos = context->manager->getEntityData<ECStuff::Pos>(context->playerID);
                        ECStuff::Size* psize = context->manager->getEntityData<ECStuff::Size>(context->playerID);
                        ppos->x -= 0.5f;
                        ppos->y -= 1.0f;
                        context->currentSize += 1;
                        psize->w = context->currentSize;
                        psize->h = context->currentSize;
                    }
                    bitset->reset(7);
                }
                else
                {
                    bitset->set(6);
                }
            }
        },
        &context);
    // particle update
    manager.addForMatchingFunction<ParticleComponents>(
        [] (std::size_t id, void* ptr, ECStuff::Pos* pos,
                ECStuff::Size* size, ECStuff::ParticleGen* particle) {
            Context* context = (Context*)ptr;
            switch(particle->type)
            {
            case 0:
                particle->timer -= DELTA_TIME;
                if(particle->timer <= 0.0f)
                {
                    context->manager->deleteEntity(id);
                }
                break;
            case 1:
                particle->timer -= DELTA_TIME;
                if(particle->timer <= 0.0f)
                {
                    particle->timer = PARTICLE1_GENTIME;
                    auto pid = context->manager->addEntity();
                    context->manager->addComponent<ECStuff::Pos>(pid,
                        pos->x + size->w / 2.0f,
                        pos->y + size->h / 2.0f);
                    context->manager->addComponent<ECStuff::Vel>(pid,
                        std::uniform_real_distribution<float>(
                            -RNG_PART_VEL, RNG_PART_VEL)(context->rng),
                        std::uniform_real_distribution<float>(
                            -RNG_PART_VEL, RNG_PART_VEL)(context->rng));
                    context->manager->addComponent<ECStuff::Acc>(pid,
                        std::uniform_real_distribution<float>(
                            -RNG_PART_ACC, RNG_PART_ACC)(context->rng),
                        std::uniform_real_distribution<float>(
                            -RNG_PART_ACC, RNG_PART_ACC)(context->rng));
                    context->manager->addComponent<ECStuff::Size>(pid,
                        1.0f, 1.0f);
                    context->manager->addComponent<ECStuff::ParticleGen>(pid);
                    context->manager->getEntityData<ECStuff::ParticleGen>(pid)->timer = PARTICLE1_GEN_LIFETIME;
                    context->manager->addComponent<ECStuff::Drawable>(pid,
                        255, 255, 255, 255);
                    context->manager->addComponent<BitsetT>(pid);
                    context->manager->getEntityData<BitsetT>(pid)->set(8);
                }
                break;
            default:
                break;
            }
        },
        &context);


    std::unordered_set<std::size_t> preserveSet;

    // create player
    auto playerID = manager.addEntity();
    manager.addComponent<ECStuff::Pos>(playerID, 2.0f, 200.0f);
    manager.addComponent<ECStuff::Vel>(playerID);
    manager.addComponent<ECStuff::Acc>(playerID, 0.0f, GRAVITY_ACC);
    manager.addComponent<ECStuff::Size>(playerID, 50.0f, 50.0f);
    manager.addComponent<ECStuff::Drawable>(playerID);
    manager.addComponent<BitsetT>(playerID);
    manager.getEntityData<BitsetT>(playerID)->set(3);
    preserveSet.insert(playerID);
    context.playerID = playerID;
    context.globalFlags.reset(1);

    // world boundaries
    {
        auto id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, -50.0f, 0.0f);
        manager.addComponent<ECStuff::Vel>(id);
        manager.addComponent<ECStuff::Acc>(id);
        manager.addComponent<ECStuff::Size>(id, 50.0f, 270.0f);
        preserveSet.insert(id);

        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 0.0f, 270.0f);
        manager.addComponent<ECStuff::Vel>(id);
        manager.addComponent<ECStuff::Acc>(id);
        manager.addComponent<ECStuff::Size>(id, 480.0f, 50.0f);
        preserveSet.insert(id);

        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 480.0f, 0.0f);
        manager.addComponent<ECStuff::Vel>(id);
        manager.addComponent<ECStuff::Acc>(id);
        manager.addComponent<ECStuff::Size>(id, 50.0f, 270.0f);
        preserveSet.insert(id);

        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 0.0f, -50.0f);
        manager.addComponent<ECStuff::Vel>(id);
        manager.addComponent<ECStuff::Acc>(id);
        manager.addComponent<ECStuff::Size>(id, 480.0f, 50.0f);
        preserveSet.insert(id);
    }

    unsigned int currentLevel = 0;
    loadLevel(currentLevel, manager);

    sf::Music music;
    if(music.openFromFile("ld43_music.ogg"))
    {
        music.setLoop(true);
        music.play();
    }

    const char* title = "LudumDare43 - Sacrifices must be made - "
        "Entry by Stephen \"BurnedKirby\" Seo";
    sf::RenderWindow window(
        sf::VideoMode(960, 540),
        title,
        sf::Style::Close | sf::Style::Titlebar);
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, 480.0f, 270.0f)));

    bool isRunning = true;
    sf::RectangleShape rect;
    GDT::IntervalBasedGameLoop(
        &isRunning,
        [&isRunning, &manager, &playerID, &window, &context,
                &preserveSet, &currentLevel] (float dt) { // update fn
            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    isRunning = false;
                }
                else if(event.type == sf::Event::KeyPressed
                    && event.key.code == sf::Keyboard::Space
                    && !context.globalFlags.test(1))
                {
                    BitsetT* bitset = manager.getEntityData<BitsetT>(playerID);
                    if(bitset->test(2))
                    {
                        context.playSfx(1);
                        manager.getEntityData<ECStuff::Vel>(playerID)->y -= JUMP_VEL;
                        bitset->reset(2);

                        // create fragment
                        auto id = manager.addEntity();
                        ECStuff::Pos* ppos = manager.getEntityData<ECStuff::Pos>(playerID);
                        ECStuff::Size* psize = manager.getEntityData<ECStuff::Size>(playerID);
                        manager.addComponent<ECStuff::Pos>(id,
                            ppos->x + psize->w / 2.0f - 2.0f,
                            ppos->y + psize->h / 2.0f - 2.0f);
                        manager.addComponent<ECStuff::Size>(id, 4.0f, 4.0f);
                        manager.addComponent<BitsetT>(id);
                        manager.getEntityData<BitsetT>(id)->set(5);
                        manager.getEntityData<BitsetT>(id)->set(7);
                        manager.addComponent<ECStuff::Drawable>(id);
                        manager.addComponent<ECStuff::ParticleGen>(id, 1);

                        // reduce player
                        context.currentSize -= 1;
                        if(context.currentSize <= 1)
                        {
                            // player reduced too much, player now dead
                            manager.deleteEntity(playerID);
                            context.globalFlags.set(1);
                        }
                        ppos->x += 0.5f;
                        ppos->y += 0.5f;
                        psize->w = context.currentSize;
                        psize->h = context.currentSize;
                    }
                }
                else if(event.type == sf::Event::KeyPressed
                    && (event.key.code == sf::Keyboard::A
                        || event.key.code == sf::Keyboard::Left)
                    && !context.globalFlags.test(1))
                {
                    manager.getEntityData<BitsetT>(playerID)->set(0);
                }
                else if(event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::A
                        || event.key.code == sf::Keyboard::Left)
                    && !context.globalFlags.test(1))
                {
                    manager.getEntityData<BitsetT>(playerID)->reset(0);
                }
                else if(event.type == sf::Event::KeyPressed
                    && (event.key.code == sf::Keyboard::D
                        || event.key.code == sf::Keyboard::Right)
                    && !context.globalFlags.test(1))
                {
                    manager.getEntityData<BitsetT>(playerID)->set(1);
                }
                else if(event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::D
                        || event.key.code == sf::Keyboard::Right)
                    && !context.globalFlags.test(1))
                {
                    manager.getEntityData<BitsetT>(playerID)->reset(1);
                }
            }
            manager.callForMatchingFunctions();
            if(context.globalFlags.test(0))
            {
                context.globalFlags.reset(0);
                context.playSfx(0);
                resetWorld(preserveSet, manager);
                loadLevel(++currentLevel, manager);
            }
        },
        [&manager, &window, &rect] () { // draw fn
            window.clear();

            manager.forMatchingSignature<DrawComponents>(
                [&window, &rect] (std::size_t id, void* ptr, ECStuff::Pos* pos,
                        ECStuff::Size* size, ECStuff::Drawable* drawable) {
                    rect.setSize(sf::Vector2f(size->w, size->h));
                    rect.setPosition(pos->x, pos->y);
                    rect.setFillColor(sf::Color(
                        drawable->r, drawable->g, drawable->b, drawable->a));
                    window.draw(rect);
                },
                nullptr);

            window.display();
        },
        60,
        1.0f / 120.0f);

    window.close();
    music.stop();
    return 0;
}
