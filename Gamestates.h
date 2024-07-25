#ifndef GAMESTATES_H
#define GAMESTATES_H

//#include <SFML/Graphics.hpp> incluido en "Temporizador.h"
#include <SFML/Window/Joystick.hpp>
#include "Tanque.h"
#include "ButtonMenu.h"
#include "Temporizador.h"
#include "Game.h"

class Game;

// Se implementa el patron de diseño State para crear diferentes estados de juego que serán administrados
// por la clase Game, que cambia de estado según se cumplan las condiciones
class GameState {
public:
    // Implementamos una fuente para textos
    sf::Font font;
    // Un temporizador
    Temporizador temporizador;
    GameState() {
        //carga fuente para los textos
        font.loadFromFile("arial-font/arial.ttf");
    }
    
    // Verifica la cantidad de joysticks conectados
    int joysticksVerif() {
        int joysticksOnline = 0;
        for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
            if (sf::Joystick::isConnected(i)) {
                joysticksOnline++;
                std::cout << "Joystick conectado:" << i << std::endl;
            }
        }
        return joysticksOnline;
    }
    // Recibe la cantidad de Joysticks y los almacena
    int joysticksOnline = joysticksVerif();
    // Funciones virtuales para que los otros estados modifiquen
    virtual void handleInput(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    // Funcion para mostrar texto en pantalla para cualquier estado;
    void mostrarTexto(sf::RenderWindow& window, std::string texto,float x, float y) {
        sf::Text text(texto, font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setPosition(x,y);
        text.setOrigin(60,25);
        window.draw(text);
    }
    // Destructor
    virtual ~GameState() {}
};

// Estado del juego donde se muestra el logo inicial
class Logo : public GameState {
private:
    //llamada a la clase Game, tiempo propio, carga de sus texturas para el fondo
    Game& game;
    Temporizador timerVerif;
    sf::Sprite FondoLogo;
    sf::Texture TexturaLogo;
public:
    Logo(Game& game) : game(game) {
        TexturaLogo.loadFromFile("Sprites/Fondo Logo.png");
        temporizador.iniciar(5.0f);
        FondoLogo.setTexture(TexturaLogo);
    }
    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};

// Estado del menú principal del juego
class MainMenu : public GameState, public ButtonMenu{
    // Carga de texturas para el fondo
    sf::Sprite FondoMenu;
    sf::Texture TexturaMenu;
public:
    MainMenu(Game& game) : ButtonMenu(game) {
        // Botones para mostrar en el Menú o solo bloques
        // Evitar crear emplace_back vacíos para todos los States (no constructor por defecto)
        blocks.emplace_back("TITLE",font,100,100,600,100);
        buttons.emplace_back("Play", font, 300, 300);
        buttons.emplace_back("Options", font, 300, 400);
        buttons.emplace_back("Exit", font, 300, 500);
        buttons[0].setSelected(true);
        TexturaMenu.loadFromFile("Sprites/Fondo Minigames.png");
        FondoMenu.setTexture(TexturaMenu);
    }
    // Funciones extra y sobreescritas
    void exit(sf::RenderWindow& window) { window.close(); }
    void onSelect(sf::RenderWindow& window) override;
    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};

// Estado de opciones del juego
class Options : public GameState , public ButtonMenu{
    sf::Sprite FondoOptions;
    sf::Texture TexturaOptions;
public:
    Options(Game& game) : ButtonMenu(game) {
        // Botones para mostrar en el Menú Opciones o solo bloques
        // Evitar crear emplace_back vacíos para todos los States (no constructor por defecto)
        buttons.emplace_back("No", font, 500, 100);
        buttons.emplace_back("No", font, 500, 300);
        buttons.emplace_back("Go Menu", font, 300, 500);
        buttons[0].setSelected(true);
        blocks.emplace_back("FullScreen", font, 100, 100);
        blocks.emplace_back("Tutorials", font, 100, 300);
    }
    void onSelect(sf::RenderWindow& window) override;
    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};

// Estado del juego donde se controlan los tanques
class TankState : public GameState, public ButtonMenu{
    //Creamos un prototipo para "Clonar" y cambiar texturas o posicion
    std::unique_ptr<Tank> prototype = std::make_unique<TankPlayer>();

    sf::Texture bodyTexture1;
    sf::Texture headTexture1;
    sf::Texture bodyTexture2;
    sf::Texture headTexture2;
    sf::Texture bodyTexture3;
    sf::Texture headTexture3;
    sf::Texture bodyTexture4;
    sf::Texture headTexture4;
    Temporizador temporizador2;
public:
    //Tanques para modificar a gusto (en base a posicion y texturas)
    std::unique_ptr<Tank> Tank1 = prototype->clone();
    std::unique_ptr<Tank> Tank2 = prototype->clone();
    std::unique_ptr<Tank> Tank3 = prototype->clone();
    std::unique_ptr<Tank> Tank4 = prototype->clone();
    TankState(Game& game) : ButtonMenu(game){
        //Implementación de las características para Tank1
        bodyTexture1.loadFromFile("Sprites/Tanque base1.png");
        headTexture1.loadFromFile("Sprites/Tanque Head1.png");
        Tank1->setTankPosition(sf::Vector2f(100,100));
        Tank1->setTankTexture(bodyTexture1, headTexture1);
        static_cast<TankPlayer*>(Tank1.get())->setJoystickId(0);
        //Implementación de las características para Tank2
        bodyTexture2.loadFromFile("Sprites/Tanque base2.png");
        headTexture2.loadFromFile("Sprites/Tanque Head2.png");
        Tank2->setTankPosition(sf::Vector2f(500, 100));
        Tank2->setTankTexture(bodyTexture2, headTexture2);
        static_cast<TankPlayer*>(Tank2.get())->setJoystickId(1);
        //Implementación de las características para Tank3
        bodyTexture3.loadFromFile("Sprites/Tanque base1.png");
        headTexture3.loadFromFile("Sprites/Tanque Head1.png");
        Tank3->setTankPosition(sf::Vector2f(100, 500));
        Tank3->setTankTexture(bodyTexture3, headTexture3);
        static_cast<TankPlayer*>(Tank3.get())->setJoystickId(2);
        //Implementación de las características para Tank4
        bodyTexture4.loadFromFile("Sprites/Tanque base2.png");
        headTexture4.loadFromFile("Sprites/Tanque Head2.png");
        Tank4->setTankPosition(sf::Vector2f(300, 500));
        Tank4->setTankTexture(bodyTexture4, headTexture4);
        static_cast<TankPlayer*>(Tank4.get())->setJoystickId(3);

        blocks.emplace_back("Tutorial", font, 300, 100, 200, 100);
        temporizador.iniciar(10.f);
        temporizador2.iniciar(5.f);
    }
    // Funciones a sobreescribir
    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};

/*
class loadScreen : public GameState {
public:
    void handleInput(sf::RenderWindow& window) override;
};

class Pause : public GameState {
public:
    void handleInput(sf::RenderWindow& window) override;
};

class Results : public GameState {
public:
    void handleInput(sf::RenderWindow& window) override;
};

class exitGame : public GameState {
public:
    void handleInput(sf::RenderWindow& window) override;
};
*/

#endif // GAMESTATES_H