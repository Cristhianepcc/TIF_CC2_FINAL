#include "Tanque.h"
#include "Gamestates.h"

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
//#include <SFML/Graphics.hpp> incluido en Gamestates.h
//#include <SFML/Window/Joystick.hpp> incluido en Gamestates.h

int main() {
    //Inicializamos la ventana principal con un marco de 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minigames");
    // Administra los estados de j
    Game game;

    game.changeState(std::make_unique<Logo>(game));

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        game.handleInput(window);

        game.update(deltaTime);

        game.draw(window);
    }
    return 0;
}
