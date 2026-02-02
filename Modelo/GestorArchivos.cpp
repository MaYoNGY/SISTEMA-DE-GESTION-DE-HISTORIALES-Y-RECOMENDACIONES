#include "GestorArchivos.h"
#include <sstream>
#include <cstdlib>

GestorArchivos::GestorArchivos() {
    rutaUsuarios = "datos/usuarios.csv";
    rutaContenido = "datos/contenido.csv";
    rutaHistoriales = "datos/historiales/";
}

GestorArchivos::GestorArchivos(const string& carpetaDatos) {
    rutaUsuarios = carpetaDatos + "/usuarios.csv";
    rutaContenido = carpetaDatos + "/contenido.csv";
    rutaHistoriales = carpetaDatos + "/historiales/";
}

string GestorArchivos::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

int GestorArchivos::contarCaracter(const string& str, char c) {
    int count = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == c) count++;
    }
    return count;
}

void GestorArchivos::crearArchivosIniciales() {
    // Crear carpeta datos si no existe
    system("mkdir datos 2>nul");
    system("mkdir datos\\historiales 2>nul");
}

bool GestorArchivos::existenArchivos() {
    ifstream archivoUsuarios(rutaUsuarios);
    ifstream archivoContenido(rutaContenido);
    
    bool existen = archivoUsuarios.good() && archivoContenido.good();
    
    archivoUsuarios.close();
    archivoContenido.close();
    
    return existen;
}

void GestorArchivos::guardarUsuarios(ListaDoble<Usuario>& usuarios) {
    crearArchivosIniciales();
    
    ofstream archivo(rutaUsuarios);
    if (!archivo.is_open()) return;
    
    // Escribir cabecera
    archivo << "id,alias,nombreCompleto,correo,contrasenia,tipo,activo" << endl;
    
    NodoDoble<Usuario>* actual = usuarios.getCabeza();
    while (actual != nullptr) {
        Usuario& u = actual->dato;
        archivo << u.getId() << ","
                << u.getAlias() << ","
                << u.getNombreCompleto() << ","
                << u.getCorreo() << ","
                << u.getContrasenia() << ","
                << (u.esAdmin() ? "ADMIN" : "USUARIO") << ","
                << (u.esActivo() ? "1" : "0") << endl;
        actual = actual->siguiente;
    }
    
    archivo.close();
}

void GestorArchivos::cargarUsuarios(ListaDoble<Usuario>& usuarios, int& nextId) {
    ifstream archivo(rutaUsuarios);
    if (!archivo.is_open()) return;
    
    string linea;
    bool primeraLinea = true;
    nextId = 1;
    
    while (getline(archivo, linea)) {
        if (primeraLinea) {
            primeraLinea = false;
            continue; // Saltar cabecera
        }
        
        if (linea.empty() || contarCaracter(linea, ',') < 6) continue;
        
        // Parsear CSV manualmente
        string campos[7];
        int campoActual = 0;
        string valorActual = "";
        
        for (size_t i = 0; i < linea.length() && campoActual < 7; i++) {
            if (linea[i] == ',') {
                campos[campoActual++] = trim(valorActual);
                valorActual = "";
            } else {
                valorActual += linea[i];
            }
        }
        if (campoActual < 7) {
            campos[campoActual] = trim(valorActual);
        }
        
        int id = stoi(campos[0]);
        string alias = campos[1];
        string nombreCompleto = campos[2];
        string correo = campos[3];
        string contrasenia = campos[4];
        TipoUsuario tipo = (campos[5] == "ADMIN") ? TipoUsuario::ADMIN : TipoUsuario::USUARIO_COMUN;
        bool activo = (campos[6] == "1");
        
        Usuario u(id, alias, nombreCompleto, correo, contrasenia, tipo, activo);
        usuarios.insertar(u);
        
        if (id >= nextId) nextId = id + 1;
    }
    
    archivo.close();
}

void GestorArchivos::guardarContenido(ListaDoble<Contenido>& contenidos) {
    crearArchivosIniciales();
    
    ofstream archivo(rutaContenido);
    if (!archivo.is_open()) return;
    
    // Escribir cabecera
    archivo << "id,titulo,tipo,genero,anio,descripcion,calificacion,activo" << endl;
    
    NodoDoble<Contenido>* actual = contenidos.getCabeza();
    while (actual != nullptr) {
        Contenido& c = actual->dato;
        archivo << c.getId() << ","
                << c.getTitulo() << ","
                << c.getTipo() << ","
                << c.getGenero() << ","
                << c.getAnio() << ","
                << c.getDescripcion() << ","
                << c.getCalificacion() << ","
                << (c.esActivo() ? "1" : "0") << endl;
        actual = actual->siguiente;
    }
    
    archivo.close();
}

void GestorArchivos::cargarContenido(ListaDoble<Contenido>& contenidos, int& nextId) {
    ifstream archivo(rutaContenido);
    if (!archivo.is_open()) return;
    
    string linea;
    bool primeraLinea = true;
    nextId = 1;
    
    while (getline(archivo, linea)) {
        if (primeraLinea) {
            primeraLinea = false;
            continue; // Saltar cabecera
        }
        
        int numComas = contarCaracter(linea, ',');
        if (linea.empty() || numComas < 6) continue;
        
        // Parsear CSV manualmente (soporta 7 u 8 campos)
        string campos[8];
        int campoActual = 0;
        string valorActual = "";
        
        for (size_t i = 0; i < linea.length() && campoActual < 8; i++) {
            if (linea[i] == ',') {
                campos[campoActual++] = trim(valorActual);
                valorActual = "";
            } else {
                valorActual += linea[i];
            }
        }
        if (campoActual < 8) {
            campos[campoActual] = trim(valorActual);
        }
        
        int id = stoi(campos[0]);
        string titulo = campos[1];
        string tipo = campos[2];
        string genero = campos[3];
        int anio = stoi(campos[4]);
        string descripcion = campos[5];
        float calificacion = stof(campos[6]);
        
        // Campo activo es opcional (para compatibilidad con archivos antiguos)
        bool activo = true;
        if (numComas >= 7 && !campos[7].empty()) {
            activo = (campos[7] == "1");
        }
        
        Contenido c(id, titulo, tipo, genero, anio, descripcion, calificacion);
        c.setActivo(activo);
        contenidos.insertar(c);
        
        if (id >= nextId) nextId = id + 1;
    }
    
    archivo.close();
}

void GestorArchivos::guardarHistoriales(const string& alias, Cola<RegistroHistorial>& historial) {
    // No guardar historial del admin
    if (alias == "admin") return;
    
    crearArchivosIniciales();
    
    string rutaArchivo = rutaHistoriales + alias + ".csv";
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) return;
    
    // Escribir cabecera
    archivo << "idContenido,titulo,tipo,genero,fecha,activo" << endl;
    
    Nodo<RegistroHistorial>* actual = historial.getFrente();
    while (actual != nullptr) {
        RegistroHistorial& r = actual->dato;
        Contenido c = r.getContenido();
        archivo << c.getId() << ","
                << c.getTitulo() << ","
                << c.getTipo() << ","
                << c.getGenero() << ","
                << r.getFecha() << ","
                << (r.esActivo() ? "1" : "0") << endl;
        actual = actual->siguiente;
    }
    
    archivo.close();
}

void GestorArchivos::cargarHistoriales(const string& alias, Cola<RegistroHistorial>& historial, ListaDoble<Contenido>& catalogo) {
    // No cargar historial del admin
    if (alias == "admin") return;
    
    string rutaArchivo = rutaHistoriales + alias + ".csv";
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) return;
    
    string linea;
    bool primeraLinea = true;
    
    while (getline(archivo, linea)) {
        if (primeraLinea) {
            primeraLinea = false;
            continue; // Saltar cabecera
        }
        
        int numComas = contarCaracter(linea, ',');
        if (linea.empty() || numComas < 4) continue;
        
        // Parsear CSV manualmente (soporta 5 o 6 campos)
        string campos[6];
        int campoActual = 0;
        string valorActual = "";
        
        for (size_t i = 0; i < linea.length() && campoActual < 6; i++) {
            if (linea[i] == ',') {
                campos[campoActual++] = trim(valorActual);
                valorActual = "";
            } else {
                valorActual += linea[i];
            }
        }
        if (campoActual < 6) {
            campos[campoActual] = trim(valorActual);
        }
        
        int idContenido = stoi(campos[0]);
        string fechaReg = campos[4];
        
        // Campo activo es opcional (para compatibilidad con archivos antiguos)
        bool activoReg = true;
        if (numComas >= 5 && !campos[5].empty()) {
            activoReg = (campos[5] == "1");
        }
        
        // Buscar contenido en el catalogo
        NodoDoble<Contenido>* actualCat = catalogo.getCabeza();
        while (actualCat != nullptr) {
            if (actualCat->dato.getId() == idContenido) {
                RegistroHistorial reg(actualCat->dato);
                reg.setFecha(fechaReg);
                reg.setActivo(activoReg);
                historial.encolar(reg);
                break;
            }
            actualCat = actualCat->siguiente;
        }
    }
    
    archivo.close();
}
