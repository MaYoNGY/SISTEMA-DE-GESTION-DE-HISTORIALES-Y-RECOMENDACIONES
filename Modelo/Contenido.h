#ifndef CONTENIDO_H
#define CONTENIDO_H

#include <string>
using namespace std;

class Contenido{
    private:
        int id;
        string titulo;
        string tipo;
        string genero;
        int anio;
        string descripcion;
        float calificacion;
        bool activo;

    public:
        // Constructores
        Contenido();
        Contenido(int id, const string& titulo, const string& tipo, const string& genero, int anio, const string& descripcion, float calificacion);

        // Getters
        int getId() const;
        string getTitulo() const;
        string getTipo() const;
        string getGenero() const;
        int getAnio() const;
        string getDescripcion() const;
        float getCalificacion() const;
        bool esActivo() const;
        
        // Setters
        void setId(int id);
        void setTitulo(const string& titulo);
        void setTipo(const string& tipo);
        void setGenero(const string& genero);
        void setAnio(int anio);
        void setDescripcion(const string& descripcion);
        void setCalificacion(float calificacion);
        void setActivo(bool activo);
        
};

#endif