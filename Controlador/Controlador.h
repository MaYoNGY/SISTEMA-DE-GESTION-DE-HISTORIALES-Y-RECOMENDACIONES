#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "../Modelo/UsuarioManager.h"
#include "../Modelo/ContenidoManager.h"
#include "../Modelo/Historial.h"
#include "../Modelo/Recomendaciones.h"
#include "../Modelo/GestorArchivos.h"
#include "../Modelo/Validacion.h"
#include "../Vista/Vista.h"

class Controlador {
private:
    UsuarioManager usuarioManager;
    ContenidoManager contenidoManager;
    GestorArchivos gestorArchivos;
    Vista vista;
    
    Usuario* usuarioActual;
    Historial* historialActual;
    Recomendaciones recomendaciones;
    
    int nextIdUsuario;
    int nextIdContenido;

    // Estructura para almacenar historiales de usuarios
    struct HistorialUsuario {
        string aliasUsuario;
        Historial* historial;
        HistorialUsuario* siguiente;
        
        HistorialUsuario(const string& alias) : aliasUsuario(alias), historial(new Historial()), siguiente(nullptr) {}
        ~HistorialUsuario() { delete historial; }
    };
    
    HistorialUsuario* listaHistoriales;
    
    // Metodos auxiliares
    Historial* obtenerHistorialUsuario(const string& alias);
    void cargarDatos();
    void guardarDatos();
    void cargarDatosIniciales();

public:
    Controlador();
    ~Controlador();
    
    // Flujo principal
    void ejecutar();
    
    // Autenticacion
    bool login();
    bool registrarUsuario();
    void cerrarSesion();
    
    // Funcionalidades Admin
    void menuAdmin();
    void menuGestionContenido();
    void menuGestionUsuarios();
    void agregarContenido();
    void modificarContenido();
    void eliminarContenido();
    void verCatalogo();
    void verUsuarios();
    void desactivarUsuario();
    void activarUsuario();
    void verHistorialDeUsuario();
    void menuModificarHistoriales();
    void eliminarEntradaHistorial();
    void limpiarHistorialUsuario();
    
    // Funcionalidades Usuario Comun
    void menuUsuarioComun();
    void filtrarContenido();
    void filtrarPorGenero();
    void filtrarPorTipo();
    void marcarComoVisto();
    void verHistorial();
    void verRecomendaciones();
    
    // Getter para catalogo
    ListaDoble<Contenido>& getCatalogo();
};

#endif
