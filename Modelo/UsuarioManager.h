#ifndef USUARIOMANAGER_H
#define USUARIOMANAGER_H

#include "ListaDoble.h"
#include "Usuario.h"

class UsuarioManager{
    private:
        ListaDoble<Usuario> listaUsuarios;

    public:
        void registrar(const Usuario& u);
        Usuario* buscarPorAlias(const string& alias);
        Usuario* buscarPorId(int id);
        bool eliminarPorAlias(const string& alias);
        ListaDoble<Usuario>& getListaUsuarios();
};

#endif