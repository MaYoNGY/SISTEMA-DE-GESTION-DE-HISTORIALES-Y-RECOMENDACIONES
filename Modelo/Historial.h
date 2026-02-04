#ifndef Historial_H
#define Historial_H

#include "Cola.h"
#include "RegistroHistorial.h"

class Historial{
    private:
        Cola<RegistroHistorial> acciones;
        static const int LIMITE = 10;
        
        void inhabilitarMasAntiguo();
        int contarActivos() const;
        void desactivarContenido(int idContenido);

    public:
        // Constructor
        Historial();

        // Usuario común
        bool existeContenido(int idContenido) const;
        void registrarVisualizacion(const Contenido& c);

        // Admin
        void eliminarPorId(int idContenido);
        void inhabilitarTodo();

        void vaciar();

        Cola<RegistroHistorial>& getAcciones();

};
#endif