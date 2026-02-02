#include "Usuario.h"

Usuario::Usuario() : id(0), alias(""), nombreCompleto(""), correo(""), contrasenia(""), tipo(TipoUsuario::USUARIO_COMUN), activo(true){}
Usuario::Usuario(int id, const string& alias, const string& nombreCompleto, const string& correo, const string& contrasenia, TipoUsuario tipo, bool activo)
    : id(id), alias(alias), nombreCompleto(nombreCompleto), correo(correo), contrasenia(contrasenia), tipo(tipo), activo(activo){}

int Usuario::getId() const{
    return id;
}
string Usuario::getAlias() const{
    return alias;
}
string Usuario::getNombreCompleto() const{
    return nombreCompleto;
}
string Usuario::getCorreo() const{
    return correo;
}
string Usuario::getContrasenia() const{
    return contrasenia;
}
TipoUsuario Usuario::getTipo() const{
    return tipo;
}


void Usuario::setId(int id){
    this->id = id;
}
void Usuario::setAlias(const string& alias){
    this->alias = alias;
}
void Usuario::setNombreCompleto(const string& nombreCompleto){
    this->nombreCompleto = nombreCompleto;
}
void Usuario::setCorreo(const string& correo){
    this->correo = correo;
}
void Usuario::setContrasenia(const string& contrasenia){
    this->contrasenia = contrasenia;
}
void Usuario::setTipo(TipoUsuario tipo){
    this->tipo = tipo;
}
void Usuario::setActivo(bool activo){
    this->activo = activo;
}

bool Usuario::esActivo() const{
    return activo;
}
bool Usuario::esAdmin() const{
    return tipo == TipoUsuario::ADMIN;
}
bool Usuario::validarContrasenia(const string& contrasenia) const{
    return this->contrasenia == contrasenia;
}
