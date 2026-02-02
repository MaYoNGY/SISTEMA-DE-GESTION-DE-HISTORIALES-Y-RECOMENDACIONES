#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <string>
#include <fstream>
#include "Usuario.h"
#include "Contenido.h"
#include "ListaDoble.h"
#include "Cola.h"
#include "RegistroHistorial.h"

using namespace std;

class GestorArchivos {
private:
    string rutaUsuarios;
    string rutaContenido;
    string rutaHistoriales;
    
    // Utilidades para parseo
    static string trim(const string& str);
    static int contarCaracter(const string& str, char c);

public:
    GestorArchivos();
    GestorArchivos(const string& carpetaDatos);
    
    // Usuarios
    void guardarUsuarios(ListaDoble<Usuario>& usuarios);
    void cargarUsuarios(ListaDoble<Usuario>& usuarios, int& nextId);
    
    // Contenido
    void guardarContenido(ListaDoble<Contenido>& contenidos);
    void cargarContenido(ListaDoble<Contenido>& contenidos, int& nextId);
    
    // Historiales - estructura especial para guardar
    struct RegistroCSV {
        string aliasUsuario;
        int idContenido;
        string tituloContenido;
        string generoContenido;
        string tipoContenido;
        string fecha;
    };
    
    void guardarHistoriales(const string& alias, Cola<RegistroHistorial>& historial);
    void cargarHistoriales(const string& alias, Cola<RegistroHistorial>& historial, ListaDoble<Contenido>& catalogo);
    
    // Inicializacion
    void crearArchivosIniciales();
    bool existenArchivos();
};

#endif
