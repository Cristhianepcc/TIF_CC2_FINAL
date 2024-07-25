#include "Gamestates.h"
#include <iostream>

// Manejador de entradas del estado Logo
void Logo::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::JoystickConnected) {
            std::cout << "Joystick connected! ID: " << event.joystickConnect.joystickId << std::endl;
        }
    }
}

// Actualización del estado Logo
void Logo::update(float deltaTime) {
    // Actualizaciones del menú
    // Se aplican 2 temporizadores por separado, temporizador dura 5 seg y cuando termina el timerVerif se repite hasta
    // que se conecte 2 a más joysticks
    if (temporizador.comprobar()) {
        timerVerif.iniciar(1.0f);
    }
    if (timerVerif.comprobar() && !timerVerif.isRunning()) {
        timerVerif.iniciar(1.0f);
    }
}

// Dibujar elementos del estado Logo
void Logo::draw(sf::RenderWindow& window) {
    window.clear();
    //mientras timerVerif siga avanzando revisará si la cantidad de Joysticks es menor a 2, mostrando texto en pantalla
    window.draw(FondoLogo);
    if (temporizador.isRunning()) {
        mostrarTexto(window, "Cargando", 400, 500);

    }
    if (timerVerif.isRunning()) {
        if (joysticksVerif() < 2) {
            mostrarTexto(window, "Conecte 2 o mas Joysticks... (2 - 4)",250,500);
        }
        else {
            std::cout << "Joystick activo";
            game.changeState(std::make_unique<MainMenu>(game));
        }
    }
    window.display();
}

// Acción cuando se selecciona una opción en el menú principal
void MainMenu::onSelect(sf::RenderWindow& window) {
    if (selectedIndex == 0) {
        // Cambiar al estado de juego (TankState)
        game.changeState(std::make_unique<TankState>(game));
    }
    else if (selectedIndex == 1) {
        // Cambiar al estado de opciones (Options)
        game.changeState(std::make_unique<Options>(game));
    }
    else if (selectedIndex == 2) {
        exit(window);
    }
    std::cout << "Main Menu Option Selected: " << selectedIndex + 1 << std::endl;
}

// Manejar entradas en el menú principal
void MainMenu::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::JoystickConnected) {
            std::cout << "Joystick connected! ID: " << event.joystickConnect.joystickId << std::endl;
            joysticksOnline = joysticksVerif();
        }
        handleButtonInput(event,window);
    }
}

// Actualizaciones del menú principal
void MainMenu::update(float deltaTime) {
    // Actualizaciones del menú
    if (joysticksOnline < 2) {
        game.changeState(std::make_unique<Logo>(game));
    }
}

// Dibujar elementos del menú principal
void MainMenu::draw(sf::RenderWindow& window) {
    // Dibujar elementos del menú
    window.clear();
    window.draw(FondoMenu);
    drawButtons(window);
    window.display();
}

// Acción cuando se selecciona una opción en el menú de opciones
void Options::onSelect(sf::RenderWindow& window) {
    // Se trata de implementar el marcar si o no para la primera opcion
    if (selectedIndex == 0) {

    }
    // Se trata de implementar el marcar si o no para la primera opcion
    if (selectedIndex == 1) {
        
    }
    //Volver al Menu
    if (selectedIndex == 2) {
        game.changeState(std::make_unique<MainMenu>(game));
    }
    std::cout << "Options Menu Option Selected : " << selectedIndex + 1 << std::endl;
}

// Manejar entradas en el menú de opciones
void Options::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        handleButtonInput(event, window);
    }
}

// Actualizaciones del menú de opciones
void Options::update(float deltaTime) {
    // Actualizaciones del menú
}

// Dibujar elementos del menú de opciones
void Options::draw(sf::RenderWindow& window) {
    // Dibujar elementos del menú
    window.clear();
    drawButtons(window);
    window.display();
}

// Manejar entradas en el estado del tanque
void TankState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        /*
        if (!temporizador2.isRunning()) {
            mostrarTexto(window, "Aprete una tecla para skipear el tutorial", 200, 500);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                std::cout << "Start Key to SKIP Tutorial Sheet" << std::endl;
                temporizador.reset();
            }
        }
        */

    }
}

// Actualizaciones del estado del tanque
void TankState::update(float deltaTime) {
    Tank1->update(deltaTime);
    /*
    for (auto& player : players) {
        player.update(deltaTime, window);
    }
    */
}

// Dibujar elementos del estado del tanque
void TankState::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    if (sf::Joystick::isConnected(0)) {
        Tank1->draw(window);
    }
    if (sf::Joystick::isConnected(1)) {
        Tank2->draw(window);
    }
    if (sf::Joystick::isConnected(2)) {
        Tank3->draw(window);
    }
    if (sf::Joystick::isConnected(3)) {
        Tank4->draw(window);
    }
    // Aqui se intentaba aplicar el que mientras el temporizador no corra se muestre el juego
    // y cuando no esté corriendo se mostraría el tutorial antes de mostrar los tanques
    /*
    if (!temporizador.isRunning()) {
        //aquí debe mostrarse el contenido del juego
    }
    else {
        drawButtons(window);
        //muestra el título de la escena
        //se debe de mostrar la imagen del tutorial
    }
    */
    window.display();
}

// Estados de juego que se pudieron implementar... puede eliminarse o incluirse en el trabajo
// para denotar el como se iba a proceder
/*
void loadScreen::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            // Cambiar a otro estado, por ejemplo, al estado del juego
            std::cout << "Enter key pressed. Transition to Game State." << std::endl;
        }
    }
}

void Pause::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            // Cambiar a otro estado, por ejemplo, al estado del juego
            std::cout << "Enter key pressed. Transition to Game State." << std::endl;
        }
    }
}

void Results::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            // Cambiar a otro estado, por ejemplo, al estado del juego
            std::cout << "Enter key pressed. Transition to Game State." << std::endl;
        }
    }
}


void exitGame::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            // Cambiar a otro estado, por ejemplo, al estado del juego
            std::cout << "Enter key pressed. Transition to Game State." << std::endl;
        }
    }
}
*/