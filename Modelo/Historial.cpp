#include "Historial.h"

Historial::Historial() : acciones(1000) {} // Sin limite automatico, se controla manualmente

int Historial::contarActivos() const {
    int contador = 0;
    Nodo<RegistroHistorial>* actual = acciones.getFrente();
    while (actual != nullptr) {
        if (actual->dato.esActivo()) {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

void Historial::inhabilitarMasAntiguo() {
    // Buscar el primer registro ACTIVO (el mas antiguo activo) y desactivarlo
    Nodo<RegistroHistorial>* actual = acciones.getFrente();
    while (actual != nullptr) {
        if (actual->dato.esActivo()) {
            actual->dato.setActivo(false);
            return; // Solo desactivar el primero activo
        }
        actual = actual->siguiente;
    }
}

void Historial::desactivarContenido(int idContenido) {
    // Desactivar un contenido especifico por su ID
    Nodo<RegistroHistorial>* actual = acciones.getFrente();
    while (actual != nullptr) {
        if (actual->dato.esActivo() && actual->dato.getContenido().getId() == idContenido) {
            actual->dato.setActivo(false);
            return;
        }
        actual = actual->siguiente;
    }
}

bool Historial::existeContenido(int idContenido) const {
    Nodo<RegistroHistorial>* actual = acciones.getFrente();
    while (actual != nullptr) {
        // Solo verificar entradas activas
        if (actual->dato.esActivo() && actual->dato.getContenido().getId() == idContenido) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void Historial::registrarVisualizacion(const Contenido& c){
    // Si ya existe en el historial (activo), desactivarlo para moverlo al final
    if (existeContenido(c.getId())) {
        desactivarContenido(c.getId());
    } else {
        // Solo verificar limite si es contenido nuevo (no existia antes)
        // Contar registros activos
        if (contarActivos() >= LIMITE) {
            inhabilitarMasAntiguo();
        }
    }
    
    // Agregar el contenido al final (mas reciente)
    RegistroHistorial r(c);
    acciones.encolar(r);
}

void Historial::eliminarPorId(int idContenido) {
    // Solo marcar como inactivo, no eliminar
    Nodo<RegistroHistorial>* actual = acciones.getFrente();
    while (actual != nullptr) {
        if (actual->dato.getContenido().getId() == idContenido) {
            actual->dato.setActivo(false);
        }
        actual = actual->siguiente;
    }
}

void Historial::inhabilitarTodo() {
    // Marcar todas las entradas como inactivas
    Nodo<RegistroHistorial>* actual = acciones.getFrente();
    while (actual != nullptr) {
        actual->dato.setActivo(false);
        actual = actual->siguiente;
    }
}

void Historial::vaciar() {
    while (!acciones.estaVacia()) {
        acciones.desencolar();
    }
}

Cola<RegistroHistorial>& Historial::getAcciones() {
    return acciones;
}