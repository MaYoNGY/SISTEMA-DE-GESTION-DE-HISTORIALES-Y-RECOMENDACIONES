#ifndef REGISTROHISTORIAL_H
#define REGISTROHISTORIAL_H

#include <string>
#include <ctime>
#include "Contenido.h"

using namespace std;

class RegistroHistorial{
    private:
        Contenido contenido;
        string fecha;
        bool activo;

        string obtenerFechaHoraActual() {
            time_t now = time(0);
            tm* ltm = localtime(&now);
            char buffer[20];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
            return string(buffer);
        }

    public:
        // Constructores
        RegistroHistorial() : activo(true) {}
        RegistroHistorial(const Contenido& c) : contenido(c), fecha(obtenerFechaHoraActual()), activo(true) {}

        // Getters
        Contenido getContenido() const{
            return contenido;
        }
        string getFecha() const{
            return fecha;
        }
        bool esActivo() const{
            return activo;
        }
        
        // Setters
        void setFecha(const string& f) { fecha = f; }
        void setActivo(bool a) { activo = a; }
        
};

#endif