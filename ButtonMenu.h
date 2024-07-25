#ifndef BUTTON_MENU_H
#define BUTTON_MENU_H

#include <SFML/Graphics.hpp>

class Game;

class Block {
public:
    sf::RectangleShape shape;
    sf::Texture texture;


    Block(float x, float y, float width, float height);
    Block(sf::Texture texture, float x, float y, float width, float height);

    void setSize(float width, float height);
    void setPosition(float x, float y);
    void setTexture(sf::Texture texture);
    void setFillColor(const sf::Color& color);
    void draw(sf::RenderWindow& window);
};

//Para cuando se apliquen texturas se eliminará (las texturas contendrán texto y no se tendrá que aplicar texto)
class textBlock : public Block{
public:
    sf::Text text;

    textBlock(const std::string& textString, const sf::Font& font, float x, float y);
    textBlock(const std::string& textString, const sf::Font& font, float x, float y, float width, float height);

    void setText(const std::string& textString);
    void draw(sf::RenderWindow& window);
};

//cuando se quite el TextBlock se deberá reemplazar por Block ya que este contendrá las texturas
class Button : public textBlock {
public:
    bool Selection;

    Button(const std::string& textString, const sf::Font& font, float x, float y);
    Button(const std::string& textString, const sf::Font& font, float x, float y, float width, float height);

    void setSelected(bool selected);
    void draw(sf::RenderWindow& window);
};

//Administra los Botones los guarda en Vectores, asi mismo con los bloques (con o sin texto);
class ButtonMenu {
protected:
    std::vector<Button> buttons;
    std::vector<textBlock> blocks;
    int selectedIndex;
    Game& game;
public:
    ButtonMenu(Game& game) : selectedIndex(0), game(game) {}

    void handleButtonInput(sf::Event event, sf::RenderWindow& window);

    virtual void onSelect(sf::RenderWindow& window);

    void drawButtons(sf::RenderWindow& window);
};

#endif //BUTTON_MENU_H