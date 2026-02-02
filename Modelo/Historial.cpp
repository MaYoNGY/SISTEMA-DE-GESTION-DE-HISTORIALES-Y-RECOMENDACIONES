#include "Historial.h"

Historial::Historial() : acciones(1000) {} // Sin limite automatico, se controla manualmente

void Historial::inhabilitarMasAntiguo() {
    // Marcar como inactivo el registro mas antiguo (el del frente)
    Nodo<RegistroHistorial>* actual = acciones.getFrente();
    if (actual != nullptr) {
        actual->dato.setActivo(false);
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

bool Historial::registrarVisualizacion(const Contenido& c){
    // Verificar si ya existe en el historial (solo activos)
    if (existeContenido(c.getId())) {
        return false; // Ya existe, no agregar duplicado
    }
    
    // Si ya hay 8 registros, inhabilitar el mas antiguo
    if (acciones.getTamanio() >= LIMITE) {
        inhabilitarMasAntiguo();
    }
    
    RegistroHistorial r(c);
    acciones.encolar(r);
    return true; // Agregado exitosamente
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