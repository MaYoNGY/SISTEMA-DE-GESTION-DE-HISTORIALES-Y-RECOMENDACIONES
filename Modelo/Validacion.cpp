#include "Validacion.h"
#include <iostream>
#include <conio.h>

using namespace std;

string Validacion::pedirTexto(const string& mensaje, int minLen, int maxLen) {
    string texto;
    
    do {
        cout << mensaje;
        texto = "";
        char c;
        
        while (true) {
            c = _getch();
            
            if (c == 13) { // Enter
                cout << endl;
                break;
            } else if (c == 8) { // Backspace
                if (!texto.empty()) {
                    texto.pop_back();
                    cout << "\b \b";
                }
            } else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) 
                       && (int)texto.length() < maxLen) {
                texto += c;
                cout << c;
            }
        }
        
        if ((int)texto.length() < minLen) {
            cout << "Debe tener al menos " << minLen << " caracter(es). Intente de nuevo..." << endl;
        }
    } while ((int)texto.length() < minLen);
    
    return texto;
}

string Validacion::pedirTextoConEspacios(const string& mensaje, int minLen, int maxLen) {
    string texto;
    
    do {
        cout << mensaje;
        texto = "";
        char c;
        
        while (true) {
            c = _getch();
            
            if (c == 13) { // Enter
                cout << endl;
                break;
            } else if (c == 8) { // Backspace
                if (!texto.empty()) {
                    texto.pop_back();
                    cout << "\b \b";
                }
            } else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ') 
                       && (int)texto.length() < maxLen) {
                texto += c;
                cout << c;
            }
        }
        
        if ((int)texto.length() < minLen) {
            cout << "Debe tener al menos " << minLen << " caracter(es). Intente de nuevo..." << endl;
        }
    } while ((int)texto.length() < minLen);
    
    return texto;
}

int Validacion::pedirEntero(const string& mensaje, int min, int max) {
    string numero;
    int valor;
    
    do {
        cout << mensaje;
        numero = "";
        char c;
        
        while (true) {
            c = _getch();
            
            if (c == 13) { // Enter
                cout << endl;
                break;
            } else if (c == 8) { // Backspace
                if (!numero.empty()) {
                    numero.pop_back();
                    cout << "\b \b";
                }
            } else if ((c >= '0' && c <= '9') && (int)numero.length() < 10) {
                numero += c;
                cout << c;
            }
        }
        
        if (numero.empty()) {
            cout << "No puede estar vacio. Intente de nuevo..." << endl;
            continue;
        }
        
        valor = stoi(numero);
        
        if (valor < min || valor > max) {
            cout << "Debe estar entre " << min << " y " << max << ". Intente de nuevo..." << endl;
            numero = "";
        }
    } while (numero.empty() || valor < min || valor > max);
    
    return valor;
}

float Validacion::pedirDecimal(const string& mensaje, float min, float max) {
    string numero;
    float valor;
    bool tienePunto = false;
    
    do {
        cout << mensaje;
        numero = "";
        tienePunto = false;
        char c;
        
        while (true) {
            c = _getch();
            
            if (c == 13) { // Enter
                cout << endl;
                break;
            } else if (c == 8) { // Backspace
                if (!numero.empty()) {
                    if (numero.back() == '.') tienePunto = false;
                    numero.pop_back();
                    cout << "\b \b";
                }
            } else if ((c >= '0' && c <= '9') && (int)numero.length() < 6) {
                numero += c;
                cout << c;
            } else if (c == '.' && !tienePunto && !numero.empty() && (int)numero.length() < 5) {
                numero += c;
                tienePunto = true;
                cout << c;
            }
        }
        
        if (numero.empty()) {
            cout << "No puede estar vacio. Intente de nuevo..." << endl;
            continue;
        }
        
        valor = stof(numero);
        
        if (valor < min || valor > max) {
            cout << "Debe estar entre " << min << " y " << max << ". Intente de nuevo..." << endl;
            numero = "";
        }
    } while (numero.empty() || valor < min || valor > max);
    
    return valor;
}

int Validacion::pedirOpcion(const string& mensaje, int maxOpciones) {
    string opc;
    int valor;
    
    do {
        cout << mensaje;
        opc = "";
        char c;
        
        while (true) {
            c = _getch();
            
            if (c == 13) { // Enter
                cout << endl;
                break;
            } else if (c == 8) { // Backspace
                if (!opc.empty()) {
                    opc.pop_back();
                    cout << "\b \b";
                }
            } else if ((c >= '0' && c <= '9') && opc.length() < 2) {
                opc += c;
                cout << c;
            }
        }
        
        if (opc.empty()) {
            cout << "Entrada invalida. Intente de nuevo..." << endl;
            continue;
        }
        
        valor = stoi(opc);
        
        if (valor < 0 || valor > maxOpciones) {
            cout << "Opcion no valida. Intente de nuevo..." << endl;
            opc = "";
        }
    } while (opc.empty() || valor < 0 || valor > maxOpciones);
    
    return valor;
}

string Validacion::pedirAlias() {
    return pedirTexto("Ingrese su alias: ", 3, 20);
}

string Validacion::pedirContrasenia() {
    string contrasenia;
    
    do {
        cout << "Ingrese su contrasenia: ";
        contrasenia = "";
        char c;
        
        while (true) {
            c = _getch();
            
            if (c == 13) { // Enter
                cout << endl;
                break;
            } else if (c == 8) { // Backspace
                if (!contrasenia.empty()) {
                    contrasenia.pop_back();
                    cout << "\b \b";
                }
            } else if ((int)contrasenia.length() < 20) {
                contrasenia += c;
                cout << '*'; // Ocultar contrasenia
            }
        }
        
        if (contrasenia.length() < 4) {
            cout << "La contrasenia debe tener al menos 4 caracteres. Intente de nuevo..." << endl;
        }
    } while (contrasenia.length() < 4);
    
    return contrasenia;
}

string Validacion::pedirNombreCompleto() {
    return pedirTextoConEspacios("Nombre completo: ", 3, 50);
}

string Validacion::pedirCorreo() {
    string correo;
    bool tieneArroba = false;
    bool tienePunto = false;
    
    do {
        cout << "Correo electronico: ";
        correo = "";
        tieneArroba = false;
        tienePunto = false;
        char c;
        
        while (true) {
            c = _getch();
            
            if (c == 13) { // Enter
                cout << endl;
                break;
            } else if (c == 8) { // Backspace
                if (!correo.empty()) {
                    if (correo.back() == '@') tieneArroba = false;
                    if (correo.back() == '.') tienePunto = false;
                    correo.pop_back();
                    cout << "\b \b";
                }
            } else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '-') 
                       && (int)correo.length() < 50) {
                correo += c;
                cout << c;
            } else if (c == '@' && !tieneArroba && !correo.empty()) {
                correo += c;
                tieneArroba = true;
                cout << c;
            } else if (c == '.' && tieneArroba && (int)correo.length() < 50) {
                correo += c;
                tienePunto = true;
                cout << c;
            }
        }
        
        if (correo.length() < 5 || !tieneArroba || !tienePunto) {
            cout << "Correo invalido. Intente de nuevo..." << endl;
        }
    } while (correo.length() < 5 || !tieneArroba || !tienePunto);
    
    return correo;
}

int Validacion::pedirId() {
    return pedirEntero("ID: ", 1, 9999);
}

string Validacion::pedirTitulo() {
    return pedirTextoConEspacios("Titulo: ", 1, 50);
}

string Validacion::pedirTipoContenido() {
    cout << "\nTipo de contenido:" << endl;
    cout << "1. Pelicula" << endl;
    cout << "2. Serie" << endl;
    cout << "3. Documental" << endl;
    
    int opcion = pedirOpcion("Seleccione el tipo: ", 3);
    
    switch (opcion) {
        case 1: return "Pelicula";
        case 2: return "Serie";
        case 3: return "Documental";
        default: return "Pelicula";
    }
}

string Validacion::pedirGenero() {
    cout << "\nGeneros disponibles:" << endl;
    cout << "1. Accion" << endl;
    cout << "2. Comedia" << endl;
    cout << "3. Drama" << endl;
    cout << "4. Terror" << endl;
    cout << "5. Ciencia Ficcion" << endl;
    cout << "6. Romance" << endl;
    cout << "7. Animacion" << endl;
    cout << "8. Documental" << endl;
    
    int opcion = pedirOpcion("Seleccione el genero: ", 8);
    
    switch (opcion) {
        case 1: return "Accion";
        case 2: return "Comedia";
        case 3: return "Drama";
        case 4: return "Terror";
        case 5: return "Ciencia Ficcion";
        case 6: return "Romance";
        case 7: return "Animacion";
        case 8: return "Documental";
        default: return "Drama";
    }
}

int Validacion::pedirAnio() {
    return pedirEntero("Anio de lanzamiento: ", 1900, 2026);
}

string Validacion::pedirDescripcion() {
    return pedirTextoConEspacios("Descripcion: ", 5, 200);
}

float Validacion::pedirCalificacion() {
    return pedirDecimal("Calificacion (0.0 - 10.0): ", 0.0f, 10.0f);
}

char Validacion::pedirConfirmacion(const string& mensaje) {
    char c;
    
    cout << mensaje << " (S/N): ";
    
    while (true) {
        c = _getch();
        
        if (c == 's' || c == 'S' || c == 'n' || c == 'N') {
            cout << c << endl;
            break;
        }
    }
    
    return (c == 's' || c == 'S') ? 'S' : 'N';
}
