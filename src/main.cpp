#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    sf::RenderWindow window(
        sf::VideoMode(480, 270),
        "LudumDare43 - Sacrifices must be made",
        sf::Style::Close | sf::Style::Titlebar);



    window.close();
    return 0;
}
