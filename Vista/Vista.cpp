#include "Vista.h"
#include <cstdlib>
#include <iomanip>

void Vista::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Vista::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Vista::mostrarMensaje(const string& mensaje) {
    cout << "\n" << mensaje << endl;
}

void Vista::mostrarError(const string& mensaje) {
    cout << "\n[ERROR] " << mensaje << endl;
}

void Vista::mostrarExito(const string& mensaje) {
    cout << "\n[EXITO] " << mensaje << endl;
}

void Vista::mostrarLinea(int longitud) {
    for (int i = 0; i < longitud; i++) cout << "-";
    cout << endl;
}

void Vista::mostrarLineaDoble(int longitud) {
    for (int i = 0; i < longitud; i++) cout << "=";
    cout << endl;
}

void Vista::mostrarCabecera(const string& titulo) {
    cout << endl;
    mostrarLineaDoble(60);
    // Centrar titulo
    int espacios = (60 - titulo.length()) / 2;
    for (int i = 0; i < espacios; i++) cout << " ";
    cout << titulo << endl;
    mostrarLineaDoble(60);
}

void Vista::mostrarBienvenida(const string& alias, bool esAdmin) {
    cout << "\nBienvenido, " << alias;
    if (esAdmin) {
        cout << " (Administrador)";
    }
    cout << "!" << endl;
}

int Vista::mostrarMenuPrincipal() {
    mostrarCabecera("SISTEMA DE STREAMING");
    cout << "\n1. Iniciar Sesion" << endl;
    cout << "2. Registrarse" << endl;
    cout << "0. Salir" << endl;
    cout << endl;
    return Validacion::pedirOpcion("Seleccione una opcion: ", 2);
}

int Vista::mostrarMenuAdmin() {
    mostrarCabecera("MENU ADMINISTRADOR");
    cout << "\n1. Gestionar Contenido" << endl;
    cout << "2. Gestionar Usuarios" << endl;
    cout << "3. Ver Historiales de Usuarios" << endl;
    cout << "4. Modificar Historiales" << endl;
    cout << "\n0. Cerrar Sesion" << endl;
    cout << endl;
    return Validacion::pedirOpcion("Seleccione una opcion: ", 4);
}

int Vista::mostrarMenuGestionContenido() {
    mostrarCabecera("GESTION DE CONTENIDO");
    cout << "\n1. Agregar contenido" << endl;
    cout << "2. Modificar contenido" << endl;
    cout << "3. Eliminar contenido" << endl;
    cout << "4. Ver catalogo completo" << endl;
    cout << "\n0. Volver" << endl;
    cout << endl;
    return Validacion::pedirOpcion("Seleccione una opcion: ", 4);
}

int Vista::mostrarMenuGestionUsuarios() {
    mostrarCabecera("GESTION DE USUARIOS");
    cout << "\n1. Ver todos los usuarios" << endl;
    cout << "2. Desactivar usuario" << endl;
    cout << "3. Activar usuario" << endl;
    cout << "\n0. Volver" << endl;
    cout << endl;
    return Validacion::pedirOpcion("Seleccione una opcion: ", 3);
}

int Vista::mostrarMenuGestionHistoriales() {
    mostrarCabecera("MODIFICAR HISTORIALES");
    cout << "\n1. Inhabilitar entrada de historial" << endl;
    cout << "2. Inhabilitar historial completo" << endl;
    cout << "\n0. Volver" << endl;
    cout << endl;
    return Validacion::pedirOpcion("Seleccione una opcion: ", 2);
}

string Vista::pedirAliasUsuario() {
    return Validacion::pedirAlias();
}

int Vista::mostrarMenuUsuarioComun() {
    mostrarCabecera("MENU USUARIO");
    cout << "\n1. Ver catalogo" << endl;
    cout << "2. Filtrar contenido" << endl;
    cout << "3. Marcar como visto (Reproducir)" << endl;
    cout << "4. Ver mi historial" << endl;
    cout << "5. Ver recomendaciones" << endl;
    cout << "\n0. Cerrar Sesion" << endl;
    cout << endl;
    return Validacion::pedirOpcion("Seleccione una opcion: ", 5);
}

int Vista::mostrarMenuFiltrar() {
    mostrarCabecera("FILTRAR CONTENIDO");
    cout << "\n1. Filtrar por genero" << endl;
    cout << "2. Filtrar por tipo (Pelicula/Serie/Documental)" << endl;
    cout << "\n0. Volver" << endl;
    cout << endl;
    return Validacion::pedirOpcion("Seleccione una opcion: ", 2);
}

void Vista::mostrarPantallaLogin() {
    mostrarCabecera("INICIAR SESION");
}

string Vista::pedirAlias() {
    return Validacion::pedirAlias();
}

string Vista::pedirContrasenia() {
    return Validacion::pedirContrasenia();
}

void Vista::mostrarFormularioRegistroUsuario(string& alias, string& nombreCompleto, string& correo, string& contrasenia) {
    mostrarCabecera("REGISTRO DE USUARIO");
    cout << endl;
    alias = Validacion::pedirAlias();
    nombreCompleto = Validacion::pedirNombreCompleto();
    correo = Validacion::pedirCorreo();
    contrasenia = Validacion::pedirContrasenia();
}

void Vista::mostrarFormularioAgregarContenido(int& id, string& titulo, string& tipo, string& genero, int& anio, string& descripcion, float& calificacion) {
    mostrarCabecera("AGREGAR NUEVO CONTENIDO");
    cout << endl;
    id = Validacion::pedirId();
    titulo = Validacion::pedirTitulo();
    tipo = Validacion::pedirTipoContenido();
    genero = Validacion::pedirGenero();
    anio = Validacion::pedirAnio();
    descripcion = Validacion::pedirDescripcion();
    calificacion = Validacion::pedirCalificacion();
}

int Vista::pedirIdContenido() {
    return Validacion::pedirEntero("Ingrese el ID del contenido: ", 1, 9999);
}

void Vista::mostrarContenido(const Contenido& c) {
    cout << "\n+------------------------------------------+" << endl;
    cout << "| ID: " << c.getId() << endl;
    cout << "| Titulo: " << c.getTitulo() << endl;
    cout << "| Tipo: " << c.getTipo() << endl;
    cout << "| Genero: " << c.getGenero() << endl;
    cout << "| Anio: " << c.getAnio() << endl;
    cout << "| Descripcion: " << c.getDescripcion() << endl;
    cout << "| Calificacion: " << fixed << setprecision(1) << c.getCalificacion() << "/10" << endl;
    cout << "+------------------------------------------+" << endl;
}

void Vista::mostrarListaContenidos(ListaDoble<Contenido>& lista) {
    mostrarCabecera("CATALOGO DE CONTENIDO");
    
    if (lista.estaVacia()) {
        cout << "\nNo hay contenido disponible." << endl;
        return;
    }
    
    // Cabecera de tabla
    cout << endl;
    cout << left << setw(5) << "ID" 
         << setw(28) << "TITULO" 
         << setw(12) << "TIPO" 
         << setw(16) << "GENERO" 
         << setw(6) << "ANIO" 
         << "CALIF" << endl;
    mostrarLinea(70);
    
    NodoDoble<Contenido>* actual = lista.getCabeza();
    int contador = 0;
    
    while (actual != nullptr) {
        Contenido& c = actual->dato;
        
        // Solo mostrar contenido activo
        if (c.esActivo()) {
            // Truncar titulo si es muy largo
            string titulo = c.getTitulo();
            if (titulo.length() > 26) {
                titulo = titulo.substr(0, 24) + "..";
            }
            
            cout << left << setw(5) << c.getId()
                 << setw(28) << titulo
                 << setw(12) << c.getTipo()
                 << setw(16) << c.getGenero()
                 << setw(6) << c.getAnio()
                 << fixed << setprecision(1) << c.getCalificacion() << endl;
            
            contador++;
        }
        
        actual = actual->siguiente;
    }
    
    mostrarLinea(70);
    cout << "  Total: " << contador << " titulo(s)" << endl;
}

void Vista::mostrarTablaUsuarios(ListaDoble<Usuario>& lista) {
    mostrarCabecera("USUARIOS REGISTRADOS");
    
    if (lista.estaVacia()) {
        cout << "\nNo hay usuarios registrados." << endl;
        return;
    }
    
    // Cabecera de tabla
    cout << endl;
    cout << left << setw(5) << "ID" 
         << setw(15) << "USUARIO" 
         << setw(28) << "NOMBRE" 
         << setw(10) << "ROL" 
         << "ESTADO" << endl;
    mostrarLinea(65);
    
    NodoDoble<Usuario>* actual = lista.getCabeza();
    
    while (actual != nullptr) {
        Usuario& u = actual->dato;
        
        // Truncar nombre si es muy largo
        string nombre = u.getNombreCompleto();
        if (nombre.length() > 26) {
            nombre = nombre.substr(0, 24) + "..";
        }
        
        cout << left << setw(5) << u.getId()
             << setw(15) << u.getAlias()
             << setw(28) << nombre
             << setw(10) << (u.esAdmin() ? "ADMIN" : "USUARIO")
             << (u.esActivo() ? "Activo" : "Inactivo") << endl;
        
        actual = actual->siguiente;
    }
    
    mostrarLinea(65);
}

void Vista::mostrarHistorial(Historial& historial, const string& nombreUsuario) {
    mostrarCabecera("HISTORIAL DE " + nombreUsuario);
    
    if (historial.getAcciones().estaVacia()) {
        cout << "\nNo hay visualizaciones registradas." << endl;
        return;
    }
    
    cout << endl;
    
    Nodo<RegistroHistorial>* actual = historial.getAcciones().getFrente();
    int contador = 0;
    
    while (actual != nullptr) {
        RegistroHistorial& r = actual->dato;
        
        // Solo mostrar entradas activas
        if (r.esActivo()) {
            Contenido c = r.getContenido();
            
            cout << "  - [" << r.getFecha() << "] " 
                 << c.getTitulo() << " (" << c.getGenero() << ") - ID: " << c.getId() << endl;
            contador++;
        }
        
        actual = actual->siguiente;
    }
    
    if (contador == 0) {
        cout << "\nNo hay visualizaciones activas." << endl;
    }
}

void Vista::mostrarRecomendaciones(ListaDoble<Contenido>& sugerencias) {
    mostrarCabecera("RECOMENDACIONES PARA TI");
    
    if (sugerencias.estaVacia()) {
        cout << "\nNo hay recomendaciones disponibles." << endl;
        cout << "Tip: Ve mas contenido para recibir mejores sugerencias!" << endl;
        return;
    }
    
    // Cabecera de tabla
    cout << endl;
    cout << left << setw(5) << "ID" 
         << setw(28) << "TITULO" 
         << setw(12) << "TIPO" 
         << setw(16) << "GENERO" 
         << "CALIF" << endl;
    mostrarLinea(65);
    
    NodoDoble<Contenido>* actual = sugerencias.getCabeza();
    int contador = 0;
    
    while (actual != nullptr) {
        Contenido& c = actual->dato;
        
        string titulo = c.getTitulo();
        if (titulo.length() > 26) {
            titulo = titulo.substr(0, 24) + "..";
        }
        
        cout << left << setw(5) << c.getId()
             << setw(28) << titulo
             << setw(12) << c.getTipo()
             << setw(16) << c.getGenero()
             << fixed << setprecision(1) << c.getCalificacion() << endl;
        
        actual = actual->siguiente;
        contador++;
    }
    
    mostrarLinea(65);
    cout << "  " << contador << " recomendacion(es) para ti" << endl;
}

int Vista::mostrarCatalogoYSeleccionar(ListaDoble<Contenido>& catalogo) {
    mostrarListaContenidos(catalogo);
    
    if (catalogo.estaVacia()) {
        return -1;
    }
    
    cout << "\n0. Cancelar" << endl;
    cout << endl;
    return Validacion::pedirEntero("Ingrese el ID del contenido: ", 0, 9999);
}

void Vista::mostrarDetallesContenido(const Contenido& c) {
    mostrarCabecera("REPRODUCIENDO CONTENIDO");
    cout << "\n*** Ahora viendo: " << c.getTitulo() << " ***\n" << endl;
    mostrarContenido(c);
    cout << "\n[Simulacion de reproduccion en curso...]" << endl;
}

int Vista::mostrarMenuRecomendaciones() {
    mostrarCabecera("TIPO DE RECOMENDACION");
    cout << "\n1. Por genero mas visto" << endl;
    cout << "2. Basado en ultimo contenido visto" << endl;
    cout << "3. Por mejor calificacion" << endl;
    cout << "0. Volver" << endl;
    cout << endl;
    return Validacion::pedirOpcion("Seleccione el tipo de recomendacion: ", 3);
}
