#ifndef RECOMENDACIONES_H
#define RECOMENDACIONES_H

#include "ListaDoble.h"
#include "Contenido.h"
#include "Historial.h"
#include <string>
using namespace std;

class Recomendaciones{
    private:
        ListaDoble<Contenido> sugerencias;

        // Funciones auxiliares privadas
        string obtenerGeneroMasVisto(Historial& historial);
        bool yaFueVisto(Historial& historial, int idContenido);

    public:
        // Constructor
        Recomendaciones();

        // Getter
        ListaDoble<Contenido>& getSugerencias();

        // Algoritmos de recomendación
        void recomendarPorGenero(Historial& historial, ListaDoble<Contenido>& catalogoCompleto, int limite = 10);
        void recomendarPorUltimoContenido(Historial& historial, ListaDoble<Contenido>& catalogoCompleto, int limite = 10);
        void recomendarPorCalificacion(Historial& historial, ListaDoble<Contenido>& catalogoCompleto, int limite = 10);

        // Utilidades
        void limpiarSugerencias();
};

#endif