#ifndef CONTENIDOMANAGER_H
#define CONTENIDOMANAGER_H

#include "ListaDoble.h"
#include "Contenido.h"

class ContenidoManager{
    private:
        ListaDoble<Contenido> listaContenidos;  

    public:
        void agregarContenido(const Contenido& c);
        Contenido* buscarPorId(int id);
        bool eliminarPorId(int id);
        ListaDoble<Contenido>& getListaContenidos();
};

#endif