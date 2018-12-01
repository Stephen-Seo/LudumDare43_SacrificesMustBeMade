#include <unordered_set>
#include <bitset>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GDT/GameLoop.hpp>
#include <GDT/CollisionDetection.hpp>
#include <EC/Manager.hpp>

#include "ECStuff.hpp"

#define DELTA_TIME (1.0f / 120.0f)
#define GRAVITY_ACC 5000.0f
#define VEL_DAMPENING 1.4f
#define JUMP_VEL 2000.0f
#define MOVE_SPEED 100.0f

using BitsetT = std::bitset<32>;

using AllComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Vel,
    ECStuff::Acc,
    ECStuff::Size,
    ECStuff::Drawable,
    BitsetT
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

using AllTags = EC::Meta::TypeList<
>;

using ManagerT = EC::Manager<AllComponents, AllTags>;

struct Context
{
    ManagerT* manager;
    std::unordered_set<std::size_t> revertPos;
};

int main(int argc, char** argv)
{
    Context context;

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
            float points[8] = {
                pos->x          , pos->y,
                pos->x + size->w, pos->y,
                pos->x + size->w, pos->y + size->h,
                pos->x,           pos->y + size->h
            };
            context->manager->forMatchingSignature<ColComponents>(
                [&context, &id, &points] (std::size_t cid, void* ptr,
                        ECStuff::Pos* pos, ECStuff::Size* size) {
                    if(id != cid
                        && context->revertPos.find(cid) == context->revertPos.end())
                    {
                        if(GDT::isWithinPolygon(points, 8, pos->x, pos->y)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y + size->h)
                            || GDT::isWithinPolygon(points, 8, pos->x, pos->y + size->h)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w / 2.0f, pos->y + size->h / 2.0f))
                        {
                            context->revertPos.insert(id);
                            context->revertPos.insert(cid);
                            return;
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
            float points[8] = {
                pos->x          , pos->y,
                pos->x + size->w, pos->y,
                pos->x + size->w, pos->y + size->h,
                pos->x,           pos->y + size->h
            };
            context->manager->forMatchingSignature<ColComponents>(
                [&context, &id, &points] (std::size_t cid, void* ptr,
                        ECStuff::Pos* pos, ECStuff::Size* size) {
                    if(id != cid
                        && context->revertPos.find(cid) == context->revertPos.end())
                    {
                        if(GDT::isWithinPolygon(points, 8, pos->x, pos->y)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y + size->h)
                            || GDT::isWithinPolygon(points, 8, pos->x, pos->y + size->h)
                            || GDT::isWithinPolygon(points, 8, pos->x + size->w / 2.0f, pos->y + size->h / 2.0f))
                        {
                            context->revertPos.insert(id);
                            context->revertPos.insert(cid);
                            return;
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
                pos->y = pos->py;
//                vel->y = 0.0f;
                context->revertPos.erase(id);
            }
        },
        &context);


    // create player
    auto playerID = manager.addEntity();
    manager.addComponent<ECStuff::Pos>(playerID);
    manager.addComponent<ECStuff::Vel>(playerID);
    manager.addComponent<ECStuff::Acc>(playerID, 0.0f, GRAVITY_ACC);
    manager.addComponent<ECStuff::Size>(playerID, 50.0f, 50.0f);
    manager.addComponent<ECStuff::Drawable>(playerID);
    manager.addComponent<BitsetT>(playerID);

    // world boundaries
    {
        auto id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, -50.0f, 0.0f);
        manager.addComponent<ECStuff::Vel>(id);
        manager.addComponent<ECStuff::Acc>(id);
        manager.addComponent<ECStuff::Size>(id, 50.0f, 270.0f);

        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 0.0f, 270.0f);
        manager.addComponent<ECStuff::Vel>(id);
        manager.addComponent<ECStuff::Acc>(id);
        manager.addComponent<ECStuff::Size>(id, 480.0f, 50.0f);

        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 480.0f, 0.0f);
        manager.addComponent<ECStuff::Vel>(id);
        manager.addComponent<ECStuff::Acc>(id);
        manager.addComponent<ECStuff::Size>(id, 50.0f, 270.0f);

        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 0.0f, -50.0f);
        manager.addComponent<ECStuff::Vel>(id);
        manager.addComponent<ECStuff::Acc>(id);
        manager.addComponent<ECStuff::Size>(id, 480.0f, 50.0f);
    }


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
        [&isRunning, &manager, &playerID, &window] (float dt) { // update fn
            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    isRunning = false;
                }
                else if(event.type == sf::Event::KeyPressed
                    && event.key.code == sf::Keyboard::Space)
                {
                    manager.getEntityData<ECStuff::Vel>(playerID)->y -= JUMP_VEL;
                }
                else if(event.type == sf::Event::KeyPressed
                    && (event.key.code == sf::Keyboard::A
                        || event.key.code == sf::Keyboard::Left))
                {
                    manager.getEntityData<BitsetT>(playerID)->set(0);
                }
                else if(event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::A
                        || event.key.code == sf::Keyboard::Left))
                {
                    manager.getEntityData<BitsetT>(playerID)->reset(0);
                }
                else if(event.type == sf::Event::KeyPressed
                    && (event.key.code == sf::Keyboard::D
                        || event.key.code == sf::Keyboard::Right))
                {
                    manager.getEntityData<BitsetT>(playerID)->set(1);
                }
                else if(event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::D
                        || event.key.code == sf::Keyboard::Right))
                {
                    manager.getEntityData<BitsetT>(playerID)->reset(1);
                }
            }
            manager.callForMatchingFunctions();
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
