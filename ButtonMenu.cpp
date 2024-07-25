#include "ButtonMenu.h"
#include <iostream>

// inicializa un bloque con una posici�n(x, y), un tama�o(width, height), y un color de relleno azul.
Block::Block(float x, float y, float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);
}
// Similar al primer constructor, pero incluye una textura (que actualmente no se aplica, ver m�s abajo).
Block::Block(sf::Texture texture, float x, float y, float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);
}

// Cambia el tama�o del bloque.
void Block::setSize(float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
}

// Cambia la posici�n del bloque.
void Block::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

// Debe establecer la textura del bloque, pero actualmente no hace nada.
void Block::setTexture(sf::Texture texture) {
    
}

// Cambia el color de relleno del bloque.
void Block::setFillColor(const sf::Color& color) {
    shape.setFillColor(color);
}

// Dibuja el bloque en la ventana proporcionada.
void Block::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// Inicializa un textBlock con texto, fuente, posici�n (x, y), tama�o predeterminado (200, 50) y configuraci�n del texto.
textBlock::textBlock(const std::string& textString, const sf::Font& font, float x, float y)
    : Block(x, y, 200.f, 50.f)
{
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 50.f, y + 15.f);
}

// Similar al primer constructor pero permite especificar el tama�o del bloque (width, height).
textBlock::textBlock(const std::string& textString, const sf::Font& font, float x, float y,float width,float height) 
    : Block(x, y, width, height) 
    {
        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(width / 2 - 50.f, height / 2 - 10.f);
    }

// Cambia el texto del textBlock.
void textBlock::setText(const std::string& textString) {
    text.setString(textString);
}

// Dibuja el bloque y el texto en la ventana proporcionada.
void textBlock::draw(sf::RenderWindow& window) {
    Block::draw(window);
    window.draw(text);
}

// Inicializa un Button con texto, fuente, posici�n (x, y),
// usando el tama�o predeterminado del textBlock y establece la selecci�n en false.
Button::Button(const std::string& textString, const sf::Font& font, float x, float y)
    : textBlock(textString, font, x, y), Selection(false) {}

// Similar al primer constructor pero permite especificar el tama�o del bot�n (width, height).
Button::Button(const std::string& textString, const sf::Font& font, float x, float y, float width, float height)
    : textBlock(textString, font, x, y, width, height), Selection(false) {}

// Cambia el estado de selecci�n del bot�n y ajusta el color de relleno en consecuencia (Rojo si est� seleccionado, Azul si no).
void Button::setSelected(bool selected) {
    Selection = selected;
    if (Selection) {
        shape.setFillColor(sf::Color::Red);
    }
    else {
        shape.setFillColor(sf::Color::Blue);
    }
}

// Dibuja el bot�n en la ventana proporcionada.
void Button::draw(sf::RenderWindow& window) {
    textBlock::draw(window); 
}

// Inicializa un ButtonMenu con referencia al juego, configurando el �ndice seleccionado en 0.
void ButtonMenu::handleButtonInput(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            buttons[selectedIndex].setSelected(false);
            selectedIndex = (selectedIndex - 1 + buttons.size()) % buttons.size();
            buttons[selectedIndex].setSelected(true);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            buttons[selectedIndex].setSelected(false);
            selectedIndex = (selectedIndex + 1) % buttons.size();
            buttons[selectedIndex].setSelected(true);
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            onSelect(window);
        }
    }
}

// Maneja la entrada del teclado para navegar entre los botones. Si se presiona Arriba,
// mueve la selecci�n al bot�n anterior. Si se presiona Abajo, mueve la selecci�n al siguiente bot�n.
// Si se presiona Enter, llama a onSelect.
void ButtonMenu::onSelect(sf::RenderWindow& window) {
    // Acci�n predeterminada para la selecci�n del bot�n.
    // Se puede sobrescribir en las clases derivadas para definir acciones espec�ficas.
    std::cout << "Selected Option: " << selectedIndex + 1 << std::endl;
}

//Dibuja todos los botones y bloques de texto en la ventana proporcionada.
void ButtonMenu::drawButtons(sf::RenderWindow& window) {
    for (auto& button : buttons) {
        button.draw(window);
    }
    for (auto& textBlock : blocks) {
        textBlock.draw(window);
    }
}