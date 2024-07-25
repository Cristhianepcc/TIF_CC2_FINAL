#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Temporizador {
private:
    sf::Clock reloj;        // Reloj de SFML para medir el tiempo transcurrido
    float tiempoObjetivo;   // Tiempo objetivo en segundos que debe transcurrir
    bool enCurso;           // Bandera para saber si el temporizador está en curso

public:
    Temporizador() : tiempoObjetivo(0), enCurso(false) {}

    void iniciar(float segundos);
    bool comprobar();
    bool isRunning() const;
    void reset();
};

#endif // !TOOLS_H