#include <cstdio>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GDT/GameLoop.hpp>

#include "ECStuff.hpp"
#include "CommonValues.hpp"
#include "CommonFunctions.hpp"

int main(int argc, char** argv)
{
    Context context;
    context.currentSize = 50;
    context.currentLevel = 0;

    // sounds
    context.soundPool.resize(7);

    context.sfxMap.insert(std::make_pair(0, sf::SoundBuffer{}));
    context.sfxMap.at(0).loadFromFile("sfx_goalreached.ogg");

    context.sfxMap.insert(std::make_pair(1, sf::SoundBuffer{}));
    context.sfxMap.at(1).loadFromFile("sfx_jump.ogg");

    // set up manager
    ManagerT manager;
    context.manager = &manager;

    // create world
    CommonFns::resetWorld(manager, context);
    CommonFns::loadLevel(context.currentLevel, manager);

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
        [&isRunning, &manager, &window, &context]
                (float dt) { // update fn
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
                    BitsetT* bitset = manager.getEntityData<BitsetT>(context.playerID);
                    if(bitset->test(2))
                    {
                        context.playSfx(1);
                        if(bitset->test(10))
                        {
                            manager.getEntityData<ECStuff::Vel>(context.playerID)->y -= JUMP_SPRING_VEL;
                            bitset->reset(10);
                        }
                        else
                        {
                            manager.getEntityData<ECStuff::Vel>(context.playerID)->y -= JUMP_VEL;
                        }
                        bitset->reset(2);

                        // create fragment
                        auto id = manager.addEntity();
                        ECStuff::Pos* ppos = manager.getEntityData<ECStuff::Pos>(context.playerID);
                        ECStuff::Size* psize = manager.getEntityData<ECStuff::Size>(context.playerID);
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
                            manager.deleteEntity(context.playerID);
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
                    manager.getEntityData<BitsetT>(context.playerID)->set(0);
                }
                else if(event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::A
                        || event.key.code == sf::Keyboard::Left)
                    && !context.globalFlags.test(1))
                {
                    manager.getEntityData<BitsetT>(context.playerID)->reset(0);
                }
                else if(event.type == sf::Event::KeyPressed
                    && (event.key.code == sf::Keyboard::D
                        || event.key.code == sf::Keyboard::Right)
                    && !context.globalFlags.test(1))
                {
                    manager.getEntityData<BitsetT>(context.playerID)->set(1);
                }
                else if(event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::D
                        || event.key.code == sf::Keyboard::Right)
                    && !context.globalFlags.test(1))
                {
                    manager.getEntityData<BitsetT>(context.playerID)->reset(1);
                }
                else if(event.type == sf::Event::KeyPressed
                    && event.key.code == sf::Keyboard::Escape)
                {
                    CommonFns::resetWorld(manager, context);
                    CommonFns::loadLevel(context.currentLevel, manager);
                }
            }
            manager.callForMatchingFunctions();
            if(context.globalFlags.test(0))
            {
                context.globalFlags.reset(0);
                context.playSfx(0);
                CommonFns::cleanupLevel(context.preserveSet, manager);
                CommonFns::loadLevel(++context.currentLevel, manager);
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
