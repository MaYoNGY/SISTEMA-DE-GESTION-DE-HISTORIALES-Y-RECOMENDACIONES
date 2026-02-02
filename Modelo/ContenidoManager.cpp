#include "ContenidoManager.h"

void ContenidoManager::agregarContenido(const Contenido& c){
    listaContenidos.insertar(c);
}

Contenido* ContenidoManager::buscarPorId(int id){
    NodoDoble<Contenido>* actual = listaContenidos.getCabeza();

    while(actual != nullptr){
        if (actual->dato.getId() == id){
            return &actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ContenidoManager::eliminarPorId(int id){
    // Solo marcar como inactivo, no eliminar fisicamente
    NodoDoble<Contenido>* actual = listaContenidos.getCabeza();

    while (actual != nullptr){
        if (actual->dato.getId() == id){
            actual->dato.setActivo(false);
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

ListaDoble<Contenido>& ContenidoManager::getListaContenidos(){
    return listaContenidos;
}
