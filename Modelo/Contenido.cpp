#include "Contenido.h"

Contenido::Contenido() : id(0), titulo(""), tipo(""), genero(""), anio(0), descripcion(""), calificacion(0.0f), activo(true) {}
Contenido::Contenido(int id, const string& titulo, const string& tipo, const string& genero, int anio, const string& descripcion, float calificacion)
    : id(id), titulo(titulo), tipo(tipo), genero(genero), anio(anio), descripcion(descripcion), calificacion(calificacion), activo(true) {}

int Contenido::getId() const{
    return id;
}
string Contenido::getTitulo() const{
    return titulo;
}
string Contenido::getTipo() const{
    return tipo;
}

string Contenido::getGenero() const{
    return genero;
}
int Contenido::getAnio() const{
    return anio;
}
string Contenido::getDescripcion() const{
    return descripcion;
}
float Contenido::getCalificacion() const{
    return calificacion;
}
bool Contenido::esActivo() const{
    return activo;
}


void Contenido::setId(int id){
    this->id = id;
}
void Contenido::setTitulo(const string& titulo){
    this->titulo = titulo;
}
void Contenido::setTipo(const string& tipo){
    this->tipo = tipo;
}
void Contenido::setGenero(const string& genero){
    this->genero = genero;
}
void Contenido::setAnio(int anio){
    this->anio = anio;
}
void Contenido::setDescripcion(const string& descripcion){
    this->descripcion = descripcion;
}
void Contenido::setCalificacion(float calificacion){
    this->calificacion = calificacion;
}
void Contenido::setActivo(bool activo){
    this->activo = activo;
}
