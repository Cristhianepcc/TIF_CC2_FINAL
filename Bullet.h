#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
    // Representa el proyectil como una forma rectangular
    sf::RectangleShape bullet;
    // Velocidad del proyectil en términos de dirección
    sf::Vector2f velocity;
    // Velocidad del proyectil
    float speed;

public:
    // Constructor que inicializa la posición, rotación y textura del proyectil
    Bullet(sf::Vector2f position, float rotation,const sf::Texture& bulletTexture);
    // Actualiza la posición del proyectil basándose en su velocidad y el tiempo transcurrido
    void update(float deltaTime);
    // Dibuja el proyectil en la ventana
    void draw(sf::RenderWindow& window) const;
    // Devuelve los límites del proyectil para detección de colisiones
    sf::FloatRect getBounds() const;
};
#endif // !BULLET_H