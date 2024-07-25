#ifndef GAME_H
#define GAME_H

#include "ButtonMenu.h"
#include "Gamestates.h"

class GameState;

class Game {
private:
    //Contiene el estado actual que se muestra en ventana
    std::unique_ptr<GameState> currentState;
public:
    Game();
    void changeState(std::unique_ptr<GameState> newState);
    void handleInput(sf::RenderWindow& window);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

};
#endif
