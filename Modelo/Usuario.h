#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

enum class TipoUsuario{
    ADMIN,
    USUARIO_COMUN
};

class Usuario{
    private:
        int id;
        string alias;
        string nombreCompleto;
        string correo;
        string contrasenia;
        TipoUsuario tipo;
        bool activo;

    public:
        // Constructores
        Usuario();
        Usuario(int id, const string& alias, const string& nombreCompleto, const string& correo, const string& contrasenia, TipoUsuario tipo, bool activo = true);

        // Getters
        int getId() const;
        string getAlias() const;
        string getNombreCompleto() const;
        string getCorreo() const;
        string getContrasenia() const;
        TipoUsuario getTipo() const;

        // Setters
        void setId(int id);
        void setAlias(const string& alias);
        void setNombreCompleto(const string& nombreCompleto);
        void setCorreo(const string& correo);   
        void setContrasenia(const string& contrasenia);
        void setTipo(TipoUsuario tipo);
        void setActivo(bool activo);

        // Otros metodos
        bool esActivo() const;
        bool esAdmin() const;
        bool validarContrasenia(const string& contrasenia) const;
};

#endif