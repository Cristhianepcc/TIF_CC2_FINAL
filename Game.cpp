#include "Game.h"

Game::Game() : currentState(nullptr) {}

// Cambia el estado actual del juego a un nuevo estado.
// Recibe un puntero único al nuevo estado y lo asigna a `currentState`.
void Game::changeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}
// Maneja la entrada del usuario.
// Delegar esta tarea al estado actual, si existe.
void Game::handleInput(sf::RenderWindow& window) {
    if (currentState) {
        currentState->handleInput(window);
    }
}

// Actualiza el estado del juego.
// Llama a la función de actualización del estado actual, si existe.
void Game::update(float deltaTime) {
    if (currentState) {
        currentState->update(deltaTime);
    }
}

// Dibuja el contenido del juego en la ventana.
// Llama a la función de dibujo del estado actual, si existe.
void Game::draw(sf::RenderWindow& window) {
    if (currentState) {
        currentState->draw(window);
    }
}