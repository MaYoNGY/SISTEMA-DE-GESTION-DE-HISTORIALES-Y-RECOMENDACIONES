#include "Controlador.h"
#include <iostream>
#include <iomanip>

using namespace std;

Controlador::Controlador() : usuarioActual(nullptr), historialActual(nullptr), listaHistoriales(nullptr), nextIdUsuario(1), nextIdContenido(1) {
    cargarDatos();
}

Controlador::~Controlador() {
    guardarDatos();
    
    // Liberar memoria de historiales
    HistorialUsuario* actual = listaHistoriales;
    while (actual != nullptr) {
        HistorialUsuario* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void Controlador::cargarDatos() {
    // Intentar cargar desde archivos CSV
    if (gestorArchivos.existenArchivos()) {
        gestorArchivos.cargarUsuarios(usuarioManager.getListaUsuarios(), nextIdUsuario);
        gestorArchivos.cargarContenido(contenidoManager.getListaContenidos(), nextIdContenido);
        
        // Cargar historiales de usuarios existentes
        NodoDoble<Usuario>* actualUser = usuarioManager.getListaUsuarios().getCabeza();
        while (actualUser != nullptr) {
            Historial* hist = obtenerHistorialUsuario(actualUser->dato.getAlias());
            gestorArchivos.cargarHistoriales(actualUser->dato.getAlias(), hist->getAcciones(), contenidoManager.getListaContenidos());
            actualUser = actualUser->siguiente;
        }
    } else {
        // Cargar datos iniciales si no existen archivos
        cargarDatosIniciales();
        guardarDatos();
    }
}

void Controlador::guardarDatos() {
    gestorArchivos.guardarUsuarios(usuarioManager.getListaUsuarios());
    gestorArchivos.guardarContenido(contenidoManager.getListaContenidos());
    
    // Guardar historiales
    HistorialUsuario* actual = listaHistoriales;
    while (actual != nullptr) {
        gestorArchivos.guardarHistoriales(actual->aliasUsuario, actual->historial->getAcciones());
        actual = actual->siguiente;
    }
}

void Controlador::cargarDatosIniciales() {
    // Crear usuario administrador unico por defecto
    Usuario admin(1, "admin", "Administrador del Sistema", "admin@streaming.com", "admin123", TipoUsuario::ADMIN);
    usuarioManager.registrar(admin);
    
    // Crear usuarios comunes de prueba
    Usuario user1(2, "usuario1", "Juan Perez", "juan@email.com", "1234", TipoUsuario::USUARIO_COMUN);
    Usuario user2(3, "usuario2", "Maria Garcia", "maria@email.com", "1234", TipoUsuario::USUARIO_COMUN);
    usuarioManager.registrar(user1);
    usuarioManager.registrar(user2);
    
    nextIdUsuario = 4;
    
    // Cargar contenido de ejemplo
    contenidoManager.agregarContenido(Contenido(1, "El Padrino", "Pelicula", "Drama", 1972, "Historia de la familia Corleone", 9.2));
    contenidoManager.agregarContenido(Contenido(2, "Inception", "Pelicula", "Ciencia Ficcion", 2010, "Un ladron que roba secretos a traves de los suenos", 8.8));
    contenidoManager.agregarContenido(Contenido(3, "Breaking Bad", "Serie", "Drama", 2008, "Profesor de quimica se convierte en narcotraficante", 9.5));
    contenidoManager.agregarContenido(Contenido(4, "The Office", "Serie", "Comedia", 2005, "Vida cotidiana en una oficina de papel", 8.9));
    contenidoManager.agregarContenido(Contenido(5, "El Conjuro", "Pelicula", "Terror", 2013, "Investigadores paranormales enfrentan un caso aterrador", 7.5));
    contenidoManager.agregarContenido(Contenido(6, "Stranger Things", "Serie", "Ciencia Ficcion", 2016, "Ninos enfrentan fuerzas sobrenaturales en los 80s", 8.7));
    contenidoManager.agregarContenido(Contenido(7, "Titanic", "Pelicula", "Romance", 1997, "Historia de amor en el famoso transatlantico", 7.9));
    contenidoManager.agregarContenido(Contenido(8, "Planet Earth", "Serie", "Documental", 2006, "Exploracion de la naturaleza del planeta", 9.4));
    contenidoManager.agregarContenido(Contenido(9, "Spider-Man", "Pelicula", "Accion", 2002, "Joven obtiene poderes de arana", 7.4));
    contenidoManager.agregarContenido(Contenido(10, "Toy Story", "Pelicula", "Animacion", 1995, "Juguetes cobran vida", 8.3));
    contenidoManager.agregarContenido(Contenido(11, "The Dark Knight", "Pelicula", "Accion", 2008, "Batman enfrenta al Joker en Gotham City", 9.0));
    contenidoManager.agregarContenido(Contenido(12, "Friends", "Serie", "Comedia", 1994, "Seis amigos en Nueva York", 8.9));
    contenidoManager.agregarContenido(Contenido(13, "Interstellar", "Pelicula", "Ciencia Ficcion", 2014, "Viaje espacial para salvar la humanidad", 8.6));
    contenidoManager.agregarContenido(Contenido(14, "Game of Thrones", "Serie", "Drama", 2011, "Lucha por el Trono de Hierro", 9.3));
    contenidoManager.agregarContenido(Contenido(15, "El Exorcista", "Pelicula", "Terror", 1973, "Una nina es poseida por un demonio", 8.1));
    contenidoManager.agregarContenido(Contenido(16, "Avatar", "Pelicula", "Ciencia Ficcion", 2009, "Humanos en el planeta Pandora", 7.9));
    contenidoManager.agregarContenido(Contenido(17, "The Mandalorian", "Serie", "Ciencia Ficcion", 2019, "Cazarrecompensas en el universo Star Wars", 8.8));
    contenidoManager.agregarContenido(Contenido(18, "Coco", "Pelicula", "Animacion", 2017, "Nino mexicano en el mundo de los muertos", 8.4));
    contenidoManager.agregarContenido(Contenido(19, "La Casa de Papel", "Serie", "Accion", 2017, "Atraco al banco de Espana", 8.2));
    contenidoManager.agregarContenido(Contenido(20, "Forrest Gump", "Pelicula", "Drama", 1994, "Historia de un hombre con vida extraordinaria", 8.8));
    
    nextIdContenido = 21;
}

Historial* Controlador::obtenerHistorialUsuario(const string& alias) {
    HistorialUsuario* actual = listaHistoriales;
    
    while (actual != nullptr) {
        if (actual->aliasUsuario == alias) {
            return actual->historial;
        }
        actual = actual->siguiente;
    }
    
    HistorialUsuario* nuevo = new HistorialUsuario(alias);
    nuevo->siguiente = listaHistoriales;
    listaHistoriales = nuevo;
    
    return nuevo->historial;
}

void Controlador::ejecutar() {
    int opcion;
    bool salir = false;
    
    while (!salir) {
        vista.limpiarPantalla();
        opcion = vista.mostrarMenuPrincipal();
        
        switch (opcion) {
            case 1:
                if (login()) {
                    if (usuarioActual->esAdmin()) {
                        menuAdmin();
                    } else {
                        menuUsuarioComun();
                    }
                }
                break;
            case 2:
                registrarUsuario();
                break;
            case 0:
                guardarDatos();
                salir = true;
                vista.mostrarMensaje("Datos guardados. Gracias por usar el sistema!");
                break;
            default:
                vista.mostrarError("Opcion no valida.");
                vista.pausar();
        }
    }
}

bool Controlador::login() {
    vista.limpiarPantalla();
    vista.mostrarPantallaLogin();
    
    string alias = vista.pedirAlias();
    string contrasenia = vista.pedirContrasenia();
    
    Usuario* usuario = usuarioManager.buscarPorAlias(alias);
    
    if (usuario == nullptr) {
        vista.mostrarError("Usuario no encontrado.");
        vista.pausar();
        return false;
    }
    
    if (!usuario->validarContrasenia(contrasenia)) {
        vista.mostrarError("Contrasenia incorrecta.");
        vista.pausar();
        return false;
    }
    
    if (!usuario->esActivo()) {
        vista.mostrarError("Este usuario esta desactivado. Contacte al administrador.");
        vista.pausar();
        return false;
    }
    
    usuarioActual = usuario;
    historialActual = obtenerHistorialUsuario(alias);
    vista.mostrarExito("Inicio de sesion exitoso!");
    vista.mostrarBienvenida(usuario->getAlias(), usuario->esAdmin());
    vista.pausar();
    
    return true;
}

bool Controlador::registrarUsuario() {
    string alias, nombreCompleto, correo, contrasenia;
    
    vista.limpiarPantalla();
    vista.mostrarFormularioRegistroUsuario(alias, nombreCompleto, correo, contrasenia);
    
    // Verificar si el alias ya existe
    if (usuarioManager.buscarPorAlias(alias) != nullptr) {
        vista.mostrarError("El alias ya esta en uso. Elija otro.");
        vista.pausar();
        return false;
    }
    
    // Solo se pueden registrar usuarios comunes (admin es unico)
    Usuario nuevoUsuario(nextIdUsuario++, alias, nombreCompleto, correo, contrasenia, TipoUsuario::USUARIO_COMUN);
    usuarioManager.registrar(nuevoUsuario);
    
    guardarDatos();
    
    vista.mostrarExito("Usuario registrado correctamente!");
    vista.pausar();
    
    return true;
}

void Controlador::cerrarSesion() {
    guardarDatos();
    usuarioActual = nullptr;
    historialActual = nullptr;
    vista.mostrarMensaje("Sesion cerrada. Datos guardados.");
}

void Controlador::menuAdmin() {
    int opcion;
    bool salir = false;
    
    while (!salir) {
        vista.limpiarPantalla();
        vista.mostrarBienvenida(usuarioActual->getAlias(), true);
        opcion = vista.mostrarMenuAdmin();
        
        switch (opcion) {
            case 1:
                menuGestionContenido();
                break;
            case 2:
                menuGestionUsuarios();
                break;
            case 3:
                verHistorialDeUsuario();
                break;
            case 4:
                menuModificarHistoriales();
                break;
            case 0:
                cerrarSesion();
                salir = true;
                break;
            default:
                vista.mostrarError("Opcion no valida.");
                vista.pausar();
        }
    }
}

void Controlador::menuGestionContenido() {
    int opcion;
    bool salir = false;
    
    while (!salir) {
        vista.limpiarPantalla();
        opcion = vista.mostrarMenuGestionContenido();
        
        switch (opcion) {
            case 1:
                agregarContenido();
                break;
            case 2:
                modificarContenido();
                break;
            case 3:
                eliminarContenido();
                break;
            case 4:
                verCatalogo();
                break;
            case 0:
                salir = true;
                break;
            default:
                vista.mostrarError("Opcion no valida.");
                vista.pausar();
        }
    }
}

void Controlador::menuGestionUsuarios() {
    int opcion;
    bool salir = false;
    
    while (!salir) {
        vista.limpiarPantalla();
        opcion = vista.mostrarMenuGestionUsuarios();
        
        switch (opcion) {
            case 1:
                verUsuarios();
                break;
            case 2:
                desactivarUsuario();
                break;
            case 3:
                activarUsuario();
                break;
            case 0:
                salir = true;
                break;
            default:
                vista.mostrarError("Opcion no valida.");
                vista.pausar();
        }
    }
}

void Controlador::menuUsuarioComun() {
    int opcion;
    bool salir = false;
    
    while (!salir) {
        vista.limpiarPantalla();
        vista.mostrarBienvenida(usuarioActual->getAlias(), false);
        opcion = vista.mostrarMenuUsuarioComun();
        
        switch (opcion) {
            case 1:
                verCatalogo();
                break;
            case 2:
                filtrarContenido();
                break;
            case 3:
                marcarComoVisto();
                break;
            case 4:
                verHistorial();
                break;
            case 5:
                verRecomendaciones();
                break;
            case 0:
                cerrarSesion();
                salir = true;
                break;
            default:
                vista.mostrarError("Opcion no valida.");
                vista.pausar();
        }
    }
}

void Controlador::agregarContenido() {
    int id, anio;
    string titulo, tipo, genero, descripcion;
    float calificacion;
    
    vista.limpiarPantalla();
    vista.mostrarFormularioAgregarContenido(id, titulo, tipo, genero, anio, descripcion, calificacion);
    
    if (contenidoManager.buscarPorId(id) != nullptr) {
        vista.mostrarError("Ya existe un contenido con ese ID.");
        vista.pausar();
        return;
    }
    
    Contenido nuevoContenido(id, titulo, tipo, genero, anio, descripcion, calificacion);
    contenidoManager.agregarContenido(nuevoContenido);
    
    if (id >= nextIdContenido) nextIdContenido = id + 1;
    
    guardarDatos();
    
    vista.mostrarExito("Contenido agregado correctamente!");
    vista.pausar();
}

void Controlador::modificarContenido() {
    vista.limpiarPantalla();
    vista.mostrarListaContenidos(getCatalogo());
    
    cout << endl;
    int id = vista.pedirIdContenido();
    
    Contenido* contenido = contenidoManager.buscarPorId(id);
    if (contenido == nullptr) {
        vista.mostrarError("Contenido no encontrado.");
        vista.pausar();
        return;
    }
    
    vista.mostrarContenido(*contenido);
    
    cout << "\nQue desea modificar?" << endl;
    cout << "1. Titulo" << endl;
    cout << "2. Tipo" << endl;
    cout << "3. Genero" << endl;
    cout << "4. Anio" << endl;
    cout << "5. Descripcion" << endl;
    cout << "6. Calificacion" << endl;
    cout << "0. Cancelar" << endl;
    cout << endl;
    
    int opcion = Validacion::pedirOpcion("Seleccione: ", 6);
    
    switch (opcion) {
        case 1:
            contenido->setTitulo(Validacion::pedirTitulo());
            break;
        case 2:
            contenido->setTipo(Validacion::pedirTipoContenido());
            break;
        case 3:
            contenido->setGenero(Validacion::pedirGenero());
            break;
        case 4:
            contenido->setAnio(Validacion::pedirAnio());
            break;
        case 5:
            contenido->setDescripcion(Validacion::pedirDescripcion());
            break;
        case 6:
            contenido->setCalificacion(Validacion::pedirCalificacion());
            break;
        case 0:
            vista.mostrarMensaje("Operacion cancelada.");
            vista.pausar();
            return;
    }
    
    guardarDatos();
    
    vista.mostrarExito("Contenido modificado correctamente!");
    vista.mostrarContenido(*contenido);
    vista.pausar();
}

void Controlador::eliminarContenido() {
    vista.limpiarPantalla();
    vista.mostrarListaContenidos(getCatalogo());
    
    cout << endl;
    int id = vista.pedirIdContenido();
    
    Contenido* contenido = contenidoManager.buscarPorId(id);
    if (contenido == nullptr) {
        vista.mostrarError("Contenido no encontrado.");
        vista.pausar();
        return;
    }
    
    if (!contenido->esActivo()) {
        vista.mostrarError("Este contenido ya esta inhabilitado.");
        vista.pausar();
        return;
    }
    
    vista.mostrarContenido(*contenido);
    
    char confirmar = Validacion::pedirConfirmacion("Inhabilitar este contenido?");
    
    if (confirmar == 'S') {
        contenidoManager.eliminarPorId(id);
        guardarDatos();
        
        vista.mostrarExito("Contenido inhabilitado correctamente!");
    } else {
        vista.mostrarMensaje("Operacion cancelada.");
    }
    
    vista.pausar();
}

void Controlador::verCatalogo() {
    vista.limpiarPantalla();
    vista.mostrarListaContenidos(getCatalogo());
    vista.pausar();
}

void Controlador::verUsuarios() {
    vista.limpiarPantalla();
    vista.mostrarTablaUsuarios(usuarioManager.getListaUsuarios());
    vista.pausar();
}

void Controlador::desactivarUsuario() {
    vista.limpiarPantalla();
    vista.mostrarTablaUsuarios(usuarioManager.getListaUsuarios());
    
    cout << endl;
    int idUsuario = Validacion::pedirEntero("Ingrese el ID del usuario a desactivar: ");
    
    if (idUsuario == 1) {
        vista.mostrarError("No se puede desactivar al administrador.");
        vista.pausar();
        return;
    }
    
    Usuario* usuario = usuarioManager.buscarPorId(idUsuario);
    if (usuario == nullptr) {
        vista.mostrarError("Usuario no encontrado.");
        vista.pausar();
        return;
    }
    
    if (!usuario->esActivo()) {
        vista.mostrarError("El usuario ya esta desactivado.");
        vista.pausar();
        return;
    }
    
    char confirmar = Validacion::pedirConfirmacion("Desactivar a " + usuario->getNombreCompleto() + "?");
    
    if (confirmar == 'S') {
        usuario->setActivo(false);
        guardarDatos();
        vista.mostrarExito("Usuario desactivado correctamente!");
    } else {
        vista.mostrarMensaje("Operacion cancelada.");
    }
    
    vista.pausar();
}

void Controlador::activarUsuario() {
    vista.limpiarPantalla();
    vista.mostrarTablaUsuarios(usuarioManager.getListaUsuarios());
    
    cout << endl;
    int idUsuario = Validacion::pedirEntero("Ingrese el ID del usuario a activar: ");
    
    Usuario* usuario = usuarioManager.buscarPorId(idUsuario);
    if (usuario == nullptr) {
        vista.mostrarError("Usuario no encontrado.");
        vista.pausar();
        return;
    }
    
    if (usuario->esActivo()) {
        vista.mostrarError("El usuario ya esta activo.");
        vista.pausar();
        return;
    }
    
    char confirmar = Validacion::pedirConfirmacion("Activar a " + usuario->getNombreCompleto() + "?");
    
    if (confirmar == 'S') {
        usuario->setActivo(true);
        guardarDatos();
        vista.mostrarExito("Usuario activado correctamente!");
    } else {
        vista.mostrarMensaje("Operacion cancelada.");
    }
    
    vista.pausar();
}

void Controlador::verHistorialDeUsuario() {
    vista.limpiarPantalla();
    vista.mostrarCabecera("VER HISTORIAL DE USUARIO");
    
    vista.mostrarTablaUsuarios(usuarioManager.getListaUsuarios());
    
    cout << endl;
    int idUsuario = Validacion::pedirEntero("Ingrese el ID del usuario: ");
    
    Usuario* usuario = usuarioManager.buscarPorId(idUsuario);
    if (usuario == nullptr) {
        vista.mostrarError("Usuario no encontrado.");
        vista.pausar();
        return;
    }
    
    Historial* historialUsuario = obtenerHistorialUsuario(usuario->getAlias());
    
    vista.limpiarPantalla();
    vista.mostrarHistorial(*historialUsuario, usuario->getNombreCompleto());
    vista.pausar();
}

void Controlador::menuModificarHistoriales() {
    int opcion;
    bool salir = false;
    
    while (!salir) {
        vista.limpiarPantalla();
        opcion = vista.mostrarMenuGestionHistoriales();
        
        switch (opcion) {
            case 1:
                eliminarEntradaHistorial();
                break;
            case 2:
                limpiarHistorialUsuario();
                break;
            case 0:
                salir = true;
                break;
            default:
                vista.mostrarError("Opcion no valida.");
                vista.pausar();
        }
    }
}

void Controlador::eliminarEntradaHistorial() {
    vista.limpiarPantalla();
    vista.mostrarCabecera("INHABILITAR ENTRADA DE HISTORIAL");
    
    vista.mostrarTablaUsuarios(usuarioManager.getListaUsuarios());
    
    cout << endl;
    int idUsuario = Validacion::pedirEntero("Ingrese el ID del usuario: ");
    
    Usuario* usuario = usuarioManager.buscarPorId(idUsuario);
    if (usuario == nullptr) {
        vista.mostrarError("Usuario no encontrado.");
        vista.pausar();
        return;
    }
    
    Historial* historialUsuario = obtenerHistorialUsuario(usuario->getAlias());
    
    if (historialUsuario->getAcciones().estaVacia()) {
        vista.mostrarError("Este usuario no tiene historial.");
        vista.pausar();
        return;
    }
    
    vista.mostrarHistorial(*historialUsuario, usuario->getNombreCompleto());
    
    cout << endl;
    int idContenido = vista.pedirIdContenido();
    historialUsuario->eliminarPorId(idContenido);
    
    guardarDatos();
    
    vista.mostrarExito("Entrada inhabilitada del historial!");
    vista.pausar();
}

void Controlador::limpiarHistorialUsuario() {
    vista.limpiarPantalla();
    vista.mostrarCabecera("INHABILITAR HISTORIAL DE USUARIO");
    
    vista.mostrarTablaUsuarios(usuarioManager.getListaUsuarios());
    
    cout << endl;
    int idUsuario = Validacion::pedirEntero("Ingrese el ID del usuario: ");
    
    Usuario* usuario = usuarioManager.buscarPorId(idUsuario);
    if (usuario == nullptr) {
        vista.mostrarError("Usuario no encontrado.");
        vista.pausar();
        return;
    }
    
    Historial* historialUsuario = obtenerHistorialUsuario(usuario->getAlias());
    
    if (historialUsuario->getAcciones().estaVacia()) {
        vista.mostrarError("Este usuario no tiene historial.");
        vista.pausar();
        return;
    }
    
    char confirmar = Validacion::pedirConfirmacion("Inhabilitar historial de " + usuario->getNombreCompleto() + "?");
    
    if (confirmar == 'S') {
        historialUsuario->inhabilitarTodo();
        guardarDatos();
        vista.mostrarExito("Historial inhabilitado correctamente!");
    } else {
        vista.mostrarMensaje("Operacion cancelada.");
    }
    
    vista.pausar();
}

void Controlador::filtrarContenido() {
    int opcion;
    bool salir = false;
    
    while (!salir) {
        vista.limpiarPantalla();
        opcion = vista.mostrarMenuFiltrar();
        
        switch (opcion) {
            case 1:
                filtrarPorGenero();
                break;
            case 2:
                filtrarPorTipo();
                break;
            case 0:
                salir = true;
                break;
            default:
                vista.mostrarError("Opcion no valida.");
                vista.pausar();
        }
    }
}

void Controlador::filtrarPorGenero() {
    vista.limpiarPantalla();
    
    string genero = Validacion::pedirGenero();
    
    vista.limpiarPantalla();
    vista.mostrarCabecera("CONTENIDO DE GENERO: " + genero);
    
    cout << endl;
    cout << left << setw(5) << "ID" 
         << setw(28) << "TITULO" 
         << setw(12) << "TIPO" 
         << setw(6) << "ANIO" 
         << "CALIF" << endl;
    vista.mostrarLinea(55);
    
    NodoDoble<Contenido>* actual = getCatalogo().getCabeza();
    int contador = 0;
    
    while (actual != nullptr) {
        if (actual->dato.getGenero() == genero) {
            Contenido& c = actual->dato;
            string titulo = c.getTitulo();
            if (titulo.length() > 26) titulo = titulo.substr(0, 24) + "..";
            
            cout << left << setw(5) << c.getId()
                 << setw(28) << titulo
                 << setw(12) << c.getTipo()
                 << setw(6) << c.getAnio()
                 << fixed << setprecision(1) << c.getCalificacion() << endl;
            contador++;
        }
        actual = actual->siguiente;
    }
    
    vista.mostrarLinea(55);
    
    if (contador == 0) {
        cout << "No se encontro contenido de ese genero." << endl;
    } else {
        cout << "Total: " << contador << " resultado(s)" << endl;
    }
    
    vista.pausar();
}

void Controlador::filtrarPorTipo() {
    vista.limpiarPantalla();
    
    string tipo = Validacion::pedirTipoContenido();
    
    vista.limpiarPantalla();
    vista.mostrarCabecera("CONTENIDO TIPO: " + tipo);
    
    cout << endl;
    cout << left << setw(5) << "ID" 
         << setw(28) << "TITULO" 
         << setw(16) << "GENERO" 
         << setw(6) << "ANIO" 
         << "CALIF" << endl;
    vista.mostrarLinea(60);
    
    NodoDoble<Contenido>* actual = getCatalogo().getCabeza();
    int contador = 0;
    
    while (actual != nullptr) {
        if (actual->dato.getTipo() == tipo) {
            Contenido& c = actual->dato;
            string titulo = c.getTitulo();
            if (titulo.length() > 26) titulo = titulo.substr(0, 24) + "..";
            
            cout << left << setw(5) << c.getId()
                 << setw(28) << titulo
                 << setw(16) << c.getGenero()
                 << setw(6) << c.getAnio()
                 << fixed << setprecision(1) << c.getCalificacion() << endl;
            contador++;
        }
        actual = actual->siguiente;
    }
    
    vista.mostrarLinea(60);
    
    if (contador == 0) {
        cout << "No se encontro contenido de ese tipo." << endl;
    } else {
        cout << "Total: " << contador << " resultado(s)" << endl;
    }
    
    vista.pausar();
}

void Controlador::marcarComoVisto() {
    vista.limpiarPantalla();
    
    int id = vista.mostrarCatalogoYSeleccionar(getCatalogo());
    
    if (id == 0 || id == -1) {
        return;
    }
    
    Contenido* contenido = contenidoManager.buscarPorId(id);
    if (contenido == nullptr) {
        vista.mostrarError("Contenido no encontrado.");
        vista.pausar();
        return;
    }
    
    vista.limpiarPantalla();
    vista.mostrarDetallesContenido(*contenido);
    
    if (historialActual != nullptr) {
        if (historialActual->registrarVisualizacion(*contenido)) {
            guardarDatos();
            vista.mostrarExito("Contenido marcado como visto!");
        } else {
            vista.mostrarError("Este contenido ya esta en tu historial.");
        }
    }
    
    vista.pausar();
}

void Controlador::verHistorial() {
    vista.limpiarPantalla();
    
    if (historialActual != nullptr && usuarioActual != nullptr) {
        vista.mostrarHistorial(*historialActual, usuarioActual->getNombreCompleto());
    } else {
        vista.mostrarError("No hay historial disponible.");
    }
    
    vista.pausar();
}

void Controlador::verRecomendaciones() {
    vista.limpiarPantalla();
    
    int tipoRecomendacion = vista.mostrarMenuRecomendaciones();
    
    if (tipoRecomendacion == 0) {
        return;
    }
    
    if (historialActual == nullptr || historialActual->getAcciones().estaVacia()) {
        vista.mostrarError("Necesitas ver contenido primero para recibir recomendaciones.");
        vista.pausar();
        return;
    }
    
    vista.limpiarPantalla();
    
    switch (tipoRecomendacion) {
        case 1:
            recomendaciones.recomendarPorGenero(*historialActual, getCatalogo());
            vista.mostrarMensaje("Basado en tu genero favorito:");
            break;
        case 2:
            recomendaciones.recomendarPorUltimoContenido(*historialActual, getCatalogo());
            vista.mostrarMensaje("Similar a lo ultimo que viste:");
            break;
        case 3:
            recomendaciones.recomendarPorCalificacion(*historialActual, getCatalogo());
            vista.mostrarMensaje("Mejor calificado que no has visto:");
            break;
        default:
            return;
    }
    
    vista.mostrarRecomendaciones(recomendaciones.getSugerencias());
    vista.pausar();
}

ListaDoble<Contenido>& Controlador::getCatalogo() {
    return contenidoManager.getListaContenidos();
}
