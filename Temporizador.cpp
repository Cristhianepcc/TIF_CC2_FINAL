#include "Temporizador.h"

// Inicia el temporizador con un tiempo objetivo específico en segundos.
// Solo reinicia el reloj y establece enCurso a true si el temporizador no está en curso.
void Temporizador::iniciar(float segundos) {
    if (!enCurso) {
        tiempoObjetivo = segundos;
        reloj.restart();
        enCurso = true;
    }
}

// Comprueba si el tiempo objetivo ha transcurrido.
// Si el temporizador está en curso y el tiempo transcurrido es mayor o igual al tiempo objetivo,
// marca el temporizador como no en curso y retorna true.
bool Temporizador::comprobar() {
    if (enCurso && reloj.getElapsedTime().asSeconds() >= tiempoObjetivo) {
        enCurso = false;
        return true;
    }
    return false;
}

// Retorna true si el temporizador está en curso, de lo contrario retorna false.
bool Temporizador::isRunning() const {
    return enCurso;
}

// Resetea el temporizador, marcándolo como no en curso.
void Temporizador::reset() {
    enCurso = false;
}