#include <SFML/Graphics.hpp>
#include <GDT/GameLoop.hpp>

int main(int argc, char** argv)
{
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
    return 0;
}
