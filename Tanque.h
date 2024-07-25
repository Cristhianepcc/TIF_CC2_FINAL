#ifndef TANQUE_H
#define TANQUE_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <cmath>
#include <vector>
#include <memory>

// Prototype Tank
// Aplicamos el Patrón de Diseño Prototype para hacer una variedad de tanques diferenciados por
// Texturas y posicion, lo que se sobreescribe dentro de TankPlayer haciendo override
class Tank {
public:
    virtual ~Tank() = default;
    virtual std::unique_ptr<Tank> clone() const = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void update(float deltaTime) = 0;
    virtual void setTankPosition(sf::Vector2f position) = 0;
    virtual void setTankTexture(const sf::Texture& bodyTexture, const sf::Texture& headTexture) = 0;
};

// Clase TankPlayer, la cual tiene los valores por defecto y la inclusion de la clase Bullet
// Detalle linea 32: se crea un vector de la clase Bullet para almacenar las balas disparadas
// linea siguiente carga la textura de la bala
class TankPlayer : public Tank {
    sf::RectangleShape body;
    sf::RectangleShape head;
    float tankSpd;
    float tankRotSpd;
    bool isSpacePressed = false;
    std::vector<std::shared_ptr<Bullet>> bullets;
    sf::Texture bulletTexture;
    unsigned int joystickId;
public:
    TankPlayer();
    std::unique_ptr<Tank> clone() const override{
        return std::make_unique<TankPlayer>(*this);
    }
    void setTankPosition(sf::Vector2f position) override;
    void setTankTexture(const sf::Texture& bodyTexture, const sf::Texture& headTexture) override;
    void setJoystickId(unsigned int id);
    void handleMovement(float deltaTime);
    void handleRotation(float deltaTime);
    void handleShoot();
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    void shoot();
};

#endif // TANQUE_H