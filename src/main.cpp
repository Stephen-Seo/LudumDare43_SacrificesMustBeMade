#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GDT/GameLoop.hpp>
#include <EC/Manager.hpp>

#include "ECStuff.hpp"

using AllComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Vel,
    ECStuff::Acc,
    ECStuff::Size
>;

using AllTags = EC::Meta::TypeList<
>;

int main(int argc, char** argv)
{
    EC::Manager<AllComponents, AllTags> manager;

    sf::Music music;
    if(music.openFromFile("ld43_music.ogg"))
    {
        music.setLoop(true);
        music.play();
    }

    const char* title = "LudumDare43 - Sacrifices must be made - "
        "Entry by Stephen \"BurnedKirby\" Seo";
    sf::RenderWindow window(
        sf::VideoMode(480, 270),
        title,
        sf::Style::Close | sf::Style::Titlebar);

    bool isRunning = true;
    GDT::IntervalBasedGameLoop(
        &isRunning,
        [&isRunning, &window] (float dt) { // update fn
            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    isRunning = false;
                }
            }
        },
        [&window] () { // draw fn
            window.clear();

            window.display();
        },
        60,
        1.0f / 120.0f);

    window.close();
    music.stop();
    return 0;
}
