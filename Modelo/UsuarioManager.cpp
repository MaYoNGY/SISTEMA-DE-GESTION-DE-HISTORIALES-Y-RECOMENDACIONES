#include "UsuarioManager.h"

void UsuarioManager::registrar(const Usuario& u){
    listaUsuarios.insertar(u);
}

Usuario* UsuarioManager::buscarPorAlias(const string& alias){
    NodoDoble<Usuario>* actual = listaUsuarios.getCabeza();

    while(actual != nullptr){
        if (actual->dato.getAlias() == alias){
            return &actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

Usuario* UsuarioManager::buscarPorId(int id){
    NodoDoble<Usuario>* actual = listaUsuarios.getCabeza();

    while(actual != nullptr){
        if (actual->dato.getId() == id){
            return &actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool UsuarioManager::eliminarPorAlias(const string& alias){
    NodoDoble<Usuario>* actual = listaUsuarios.getCabeza();

    while (actual != nullptr) {
        if (actual->dato.getAlias() == alias) {
            listaUsuarios.eliminarNodo(actual);
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

ListaDoble<Usuario>& UsuarioManager::getListaUsuarios(){
    return listaUsuarios;
}
