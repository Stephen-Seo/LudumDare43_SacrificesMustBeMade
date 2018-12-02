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

    context.sfxMap.insert(std::make_pair(2, sf::SoundBuffer{}));
    context.sfxMap.at(2).loadFromFile("sfx_death.ogg");

    context.sfxMap.insert(std::make_pair(3, sf::SoundBuffer{}));
    context.sfxMap.at(3).loadFromFile("sfx_keyget.ogg");

    // create world
    CommonFns::resetWorld(context);
    CommonFns::loadLevel(context.currentLevel, context);

    if(context.music.openFromFile("ld43_music.ogg"))
    {
        context.music.setLoop(true);
        context.music.play();
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
    float deathTimer = DEATH_TIMER;
    sf::RenderTexture renderT[2];
    renderT[0].create(480, 270);
    renderT[0].clear();
    renderT[1].create(480, 270);
    renderT[1].clear();
    GDT::IntervalBasedGameLoop(
        &isRunning,
        [&isRunning, &window, &context, &deathTimer]
                (float /*dt*/) { // update fn
            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    isRunning = false;
                }
                else if(event.type == sf::Event::KeyPressed
                    && event.key.code == sf::Keyboard::Space
                    && !context.globalFlags.test(1)
                    && !context.globalFlags.test(3))
                {
                    BitsetT* bitset = context.manager.getEntityData<BitsetT>(context.playerID);
                    if(bitset->test(2))
                    {
                        context.playSfx(1);
                        if(bitset->test(10))
                        {
                            context.manager.getEntityData<ECStuff::Vel>(context.playerID)->y -= JUMP_SPRING_VEL;
                            bitset->reset(10);
                        }
                        else
                        {
                            context.manager.getEntityData<ECStuff::Vel>(context.playerID)->y -= JUMP_VEL;
                        }
                        bitset->reset(2);

                        CommonFns::createPlayerFragment(context);
                    }
                }
                else if(event.type == sf::Event::KeyPressed
                    && (event.key.code == sf::Keyboard::A
                        || event.key.code == sf::Keyboard::Left)
                    && !context.globalFlags.test(1)
                    && !context.globalFlags.test(3))
                {
                    context.manager.getEntityData<BitsetT>(context.playerID)->set(0);
                }
                else if(event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::A
                        || event.key.code == sf::Keyboard::Left)
                    && !context.globalFlags.test(1)
                    && !context.globalFlags.test(3))
                {
                    context.manager.getEntityData<BitsetT>(context.playerID)->reset(0);
                }
                else if(event.type == sf::Event::KeyPressed
                    && (event.key.code == sf::Keyboard::D
                        || event.key.code == sf::Keyboard::Right)
                    && !context.globalFlags.test(1)
                    && !context.globalFlags.test(3))
                {
                    context.manager.getEntityData<BitsetT>(context.playerID)->set(1);
                }
                else if(event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::D
                        || event.key.code == sf::Keyboard::Right)
                    && !context.globalFlags.test(1)
                    && !context.globalFlags.test(3))
                {
                    context.manager.getEntityData<BitsetT>(context.playerID)->reset(1);
                }
                else if(event.type == sf::Event::KeyPressed
                    && event.key.code == sf::Keyboard::Escape
                    && !context.globalFlags.test(3))
                {
                    CommonFns::resetWorld(context);
                    CommonFns::loadLevel(context.currentLevel, context);
                }
            }
            context.manager.callForMatchingFunctions();
            if(context.globalFlags.test(0))
            {
                context.globalFlags.reset(0);
                context.playSfx(0);
                CommonFns::cleanupLevel(context);
                CommonFns::loadLevel(++context.currentLevel, context);
            }
            if(context.globalFlags.test(1))
            {
                context.globalFlags.set(4);
                deathTimer -= DELTA_TIME;
                if(deathTimer <= 0.0f)
                {
                    deathTimer = 0.0f;
                    CommonFns::resetWorld(context);
                    CommonFns::loadLevel(context.currentLevel, context);
                }
            }
            else if(context.globalFlags.test(4))
            {
                deathTimer += DELTA_TIME;
                if(deathTimer >= DEATH_TIMER)
                {
                    deathTimer = DEATH_TIMER;
                    context.globalFlags.reset(4);
                }
            }
            if(context.globalFlags.test(2))
            {
                context.globalFlags.reset(2);
                context.playSfx(3);
                context.manager.forMatchingSignature<EC::Meta::TypeList<BitsetT>>(
                    [&context] (std::size_t id, void* /*ptr*/, BitsetT* bitset) {
                        if(bitset->test(15))
                        {
                            context.manager.deleteEntity(id);
                        }
                    },
                    nullptr);
            }
            if(context.globalFlags.test(3))
            {
                ECStuff::Pos* ppos = context.manager.getEntityData<ECStuff::Pos>(context.playerID);
                ECStuff::Size* psize = context.manager.getEntityData<ECStuff::Size>(context.playerID);
                ECStuff::Acc* pacc = context.manager.getEntityData<ECStuff::Acc>(context.playerID);

                if(ppos->x <= 0.0f)
                {
                    ppos->x = 1.0f;
                }
                else if(ppos->x + psize->w >= 480.0f)
                {
                    ppos->x = 480.0f - psize->w - 1.0f;
                }
                if(ppos->y <= 0.0f)
                {
                    ppos->y = 1.0f;
                }
                else if(ppos->y + psize->h >= 270.0f)
                {
                    ppos->y = 270.0f - psize->h - 1.0f;
                }

                pacc->x = (240.0f - ppos->x) * WIN_CENTER_MAGNITUDE;
                pacc->y = (135.0f - ppos->y) * WIN_CENTER_MAGNITUDE;
            }
        },
        [&context, &window, &rect, &deathTimer, &renderT] () { // draw fn
            window.clear();

            // fade effect
            context.manager.forMatchingSignature<FadeDrawComponents>(
                [&renderT, &rect] (std::size_t /*id*/, void* /*ptr*/, ECStuff::Pos* pos,
                        ECStuff::Size* size, ECStuff::Drawable* drawable,
                        BitsetT* bitset) {
                    if(bitset->test(3) || bitset->test(8))
                    {
                        rect.setSize(sf::Vector2f(size->w, size->h));
                        rect.setPosition(pos->x, pos->y);
                        rect.setFillColor(sf::Color(
                            drawable->r, drawable->g, drawable->b, drawable->a));
                        renderT[0].draw(rect);
                    }
                },
                nullptr);

            renderT[0].display();
            sf::Sprite sprite;
            sprite.setTexture(renderT[0].getTexture(), true);
            sprite.setColor(sf::Color(255, 255, 255, 240));
            renderT[1].clear();
            renderT[1].draw(sprite);
            renderT[1].display();
            sprite.setTexture(renderT[1].getTexture(), true);
            sprite.setColor(sf::Color::White);
            renderT[0].clear();
            renderT[0].draw(sprite);
            renderT[0].display();
            sprite.setTexture(renderT[0].getTexture(), true);
            window.draw(sprite);

            // actual draw
            context.manager.forMatchingSignature<DrawComponents>(
                [&window, &rect] (std::size_t /*id*/, void* /*ptr*/, ECStuff::Pos* pos,
                        ECStuff::Size* size, ECStuff::Drawable* drawable) {
                    rect.setSize(sf::Vector2f(size->w, size->h));
                    rect.setPosition(pos->x, pos->y);
                    rect.setFillColor(sf::Color(
                        drawable->r, drawable->g, drawable->b, drawable->a));
                    window.draw(rect);
                },
                nullptr);

            if(context.globalFlags.test(4))
            {
                rect.setPosition(0.0f, 0.0f);
                rect.setSize(sf::Vector2f(480.0f, 270.0f));
                rect.setFillColor(sf::Color(0, 0, 0, (DEATH_TIMER - deathTimer) / DEATH_TIMER * 255));
                window.draw(rect);
            }

            window.display();
        },
        60,
        1.0f / 120.0f);

    window.close();
    context.music.stop();
    return 0;
}
