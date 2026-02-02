#ifndef VALIDACION_H
#define VALIDACION_H

#include <string>
using namespace std;

class Validacion {
public:
    // Validaciones de texto
    static string pedirTexto(const string& mensaje, int minLen = 1, int maxLen = 50);
    static string pedirTextoConEspacios(const string& mensaje, int minLen = 1, int maxLen = 100);
    
    // Validaciones numericas
    static int pedirEntero(const string& mensaje, int min = 0, int max = 9999);
    static float pedirDecimal(const string& mensaje, float min = 0.0f, float max = 10.0f);
    static int pedirOpcion(const string& mensaje, int maxOpciones);
    
    // Validaciones especificas del sistema
    static string pedirAlias();
    static string pedirContrasenia();
    static string pedirNombreCompleto();
    static string pedirCorreo();
    static int pedirId();
    static string pedirTitulo();
    static string pedirTipoContenido();
    static string pedirGenero();
    static int pedirAnio();
    static string pedirDescripcion();
    static float pedirCalificacion();
    
    // Confirmaciones
    static char pedirConfirmacion(const string& mensaje);
};

#endif
