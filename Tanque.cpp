#include "Tanque.h"

// Establece el ID del joystick que controlará este tanque.
void TankPlayer::setJoystickId(unsigned int id) {
    joystickId = id;
}

TankPlayer::TankPlayer() : tankSpd(200.f), tankRotSpd(90.f), joystickId(0){
    // Constructor por defecto que inicializa las velocidades del tanque y el ID del joystick.
    // Configura el tamaño y el origen del cuerpo y la cabeza del tanque.
    body.setSize(sf::Vector2f(50.f, 50.f));
    body.setOrigin(25.f, 25.f);
    head.setSize(sf::Vector2f(50.f, 30.f));
    head.setOrigin(15.f, 15.f);
    bulletTexture.loadFromFile("Sprites/Tanque Bullet.png");
}

// Establece la posición del cuerpo y la cabeza del tanque.
void TankPlayer::setTankPosition(sf::Vector2f position) {
    body.setPosition(position);
    head.setPosition(position);
}

// Establece las texturas del cuerpo y la cabeza del tanque.
void TankPlayer::setTankTexture(const sf::Texture& bodyTexture, const sf::Texture& headTexture) {
    body.setTexture(&bodyTexture);
    head.setTexture(&headTexture);
}

// Actualiza el estado del tanque, maneja el movimiento, la rotación y el disparo.
void TankPlayer::update(float deltaTime) {
    handleMovement(deltaTime);
    handleRotation(deltaTime);
    handleShoot();
    for (auto& bullet : bullets) {
        bullet->update(deltaTime);
    }
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const std::shared_ptr<Bullet>& bullet) {
        return bullet->getBounds().left > 800 || bullet->getBounds().left + bullet->getBounds().width < 0 ||
            bullet->getBounds().top > 600 || bullet->getBounds().top + bullet->getBounds().height < 0;
        }), bullets.end());
}
// Dibuja el cuerpo y la cabeza del tanque en la ventana.
void TankPlayer::draw(sf::RenderWindow& window) const {
    window.draw(body);
    window.draw(head);
    for (const auto& bullet : bullets) {
        bullet->draw(window);
    }
}

// Maneja el movimiento del tanque utilizando el joystick.
void TankPlayer::handleMovement(float deltaTime) {
    float moveX = 0.f;
    float moveY = 0.f;
    //esta sección comentada contiene el manejo del tanque mediante teclado
    //no está calibrada para manejar un tanque respectivo, siempre toma el primero
    /*

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveX -= tankSpd * deltaTime;
        body.rotate(-tankRotSpd * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveX += tankSpd * deltaTime;
        body.rotate(tankRotSpd * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        moveY -= tankSpd * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        moveY += tankSpd * deltaTime;
    }
    if (moveX != 0.f || moveY != 0.f) {
        body.move(moveX, moveY);
        float angle = std::atan2(moveY, moveX) * 180 / 3.14159265f;
        body.setRotation(angle + 90);
    }
    */
    // Implementacion del joystick para manejar el tanque, esta vez contiene un indice para
    // que cada Joystick maneje un tanque respectivamente
    if (sf::Joystick::isConnected(joystickId)) {
        float axisX = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
        float axisY = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y);

        moveX += (axisX / 100.f) * tankSpd * deltaTime;
        moveY += (axisY / 100.f) * tankSpd * deltaTime;

        if (axisX != 0.f || axisY != 0.f) {
            float angle = std::atan2(axisX, axisY) * 180 / 3.14159265f;
            body.setRotation(angle + 90);
        }
    }

    if (moveX != 0.f || moveY != 0.f) {
        body.move(moveX, moveY);
    }

    head.move(moveX, moveY);

    // Limites para que el tanque no salga de la ventana
    sf::FloatRect tankBounds = body.getGlobalBounds();

    if (body.getPosition().x - 25 <= 0) {
        body.setPosition(0 + tankBounds.width / 2, body.getPosition().y);
        head.setPosition(0 + tankBounds.width / 2, body.getPosition().y);
    }
    if (body.getPosition().x + 25 >= 800) {
        body.setPosition(800 - tankBounds.width / 2, body.getPosition().y);
        head.setPosition(800 - tankBounds.width / 2, body.getPosition().y);
    }
    if (body.getPosition().y - 25 <= 0) {
        body.setPosition(body.getPosition().x, 0 + tankBounds.height / 2);
        head.setPosition(body.getPosition().x, 0 + tankBounds.height / 2);
    }
    if (body.getPosition().y + 25 >= 600) {
        body.setPosition(body.getPosition().x, 600 - tankBounds.height / 2);
        head.setPosition(body.getPosition().x, 600 - tankBounds.height / 2);
    }
}

void TankPlayer::handleRotation(float deltaTime) {
    // Maneja la rotación de la cabeza del tanque utilizando el joystick.
    if (sf::Joystick::isConnected(joystickId)) {
        float axisZ = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Z);
        float axisR = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::R);

        if (std::abs(axisZ) > 10.f || std::abs(axisR) > 10.f) { // Umbral para evitar movimiento involuntario
            float angle = std::atan2(axisZ, axisR) * 180 / 3.14159265f;
            head.setRotation(angle);
        }
    }
    // Implementación para teclado
    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        head.rotate(-tankRotSpd * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        head.rotate(tankRotSpd * deltaTime);
    }
    */
}

// Maneja el disparo de balas utilizando el joystick.
void TankPlayer::handleShoot() {
    if (sf::Joystick::isConnected(joystickId) && sf::Joystick::isButtonPressed(joystickId, 5)){
    // Implementacion para teclado
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!isSpacePressed) {
            shoot();
        }
    }
    else {
        isSpacePressed = false;
    }
}

// Dispara una bala desde la posición y la rotación de la "boca" del tanque.
void TankPlayer::shoot() {
    bullets.push_back(std::make_shared<Bullet>(head.getPosition(), head.getRotation(),bulletTexture));
    isSpacePressed = true;
}