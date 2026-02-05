#ifndef VISTA_H
#define VISTA_H

#include <iostream>
#include <string>
#include "../Modelo/Usuario.h"
#include "../Modelo/Contenido.h"
#include "../Modelo/Historial.h"
#include "../Modelo/Recomendaciones.h"
#include "../Modelo/ListaDoble.h"
#include "../Modelo/Cola.h"
#include "../Modelo/RegistroHistorial.h"
#include "../Modelo/Validacion.h"

using namespace std;

class Vista {
public:
    // Utilidades
    void limpiarPantalla();
    void pausar();
    void mostrarMensaje(const string& mensaje);
    void mostrarError(const string& mensaje);
    void mostrarExito(const string& mensaje);
    void mostrarLinea(int longitud = 60);
    void mostrarLineaDoble(int longitud = 60);

    // Menus principales
    int mostrarMenuPrincipal();
    int mostrarMenuAdmin();
    int mostrarMenuUsuarioComun();

    // Submenus Admin
    int mostrarMenuGestionContenido();
    int mostrarMenuGestionUsuarios();
    int mostrarMenuGestionHistoriales();
    string pedirAliasUsuario();

    // Submenus Usuario
    int mostrarMenuFiltrar();

    // Login y registro
    void mostrarPantallaLogin();
    string pedirAlias();
    string pedirContrasenia();
    void mostrarFormularioRegistroUsuario(string& alias, string& nombreCompleto, string& correo, string& contrasenia);

    // Gestion de contenido (Admin)
    void mostrarFormularioAgregarContenido(int& id, string& titulo, string& tipo, string& genero, int& anio, string& descripcion, float& calificacion);
    int pedirIdContenido();

    // Mostrar informacion - FORMATO MEJORADO
    void mostrarContenido(const Contenido& c);
    void mostrarListaContenidos(ListaDoble<Contenido>& lista);
    void mostrarListaContenidosTodos(ListaDoble<Contenido>& lista);
    void mostrarTablaUsuarios(ListaDoble<Usuario>& lista);
    void mostrarHistorial(Historial& historial, const string& nombreUsuario);
    void mostrarRecomendaciones(ListaDoble<Contenido>& sugerencias);

    // Catalogos y visualizacion
    int mostrarCatalogoYSeleccionar(ListaDoble<Contenido>& catalogo);
    void mostrarDetallesContenido(const Contenido& c);

    // Menu de recomendaciones
    int mostrarMenuRecomendaciones();

    // Cabecera
    void mostrarCabecera(const string& titulo);
    void mostrarBienvenida(const string& alias, bool esAdmin);
};

#endif
