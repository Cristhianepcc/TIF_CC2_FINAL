#include "Bullet.h"

// Constructor de la clase Bullet
Bullet::Bullet(sf::Vector2f position, float angle,const sf::Texture& bulletTexture) : speed(500.f) {
    // Configura el tamaño del proyectil, establece el origen del proyectil para la rotación,
    // configura el ángulo de rotación del proyectil, establece la posición inicial del proyectil,
    // aplica la textura al proyectil
    bullet.setSize(sf::Vector2f(40.f, 20.f));
    bullet.setOrigin(bullet.getSize().x - 70.f, bullet.getSize().y - 10.f);
    bullet.setRotation(angle);
    bullet.setPosition(position);
    bullet.setTexture(&bulletTexture);

    // Convierte el ángulo de grados a radianes
    float radians = angle * 3.14159265f / 180;
    // Calcula la velocidad en base al ángulo y la velocidad del proyectil
    velocity = sf::Vector2f(std::cos(radians), std::sin(radians)) * speed;
}

// Actualiza la posición del proyectil basándose en su velocidad y el tiempo transcurrido
void Bullet::update(float deltaTime) {
    bullet.move(velocity * deltaTime);
}

// Dibuja el proyectil en la ventana
void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(bullet);
}

// Devuelve los límites del proyectil para detección de colisiones
sf::FloatRect Bullet::getBounds() const {
    return bullet.getGlobalBounds();
}
