#include "Recomendaciones.h"

Recomendaciones::Recomendaciones() {}

ListaDoble<Contenido>& Recomendaciones::getSugerencias(){
    return sugerencias;
}

string Recomendaciones::obtenerGeneroMasVisto(Historial& historial){
    struct ContadorGenero{
        string genero;
        int contador;
        ContadorGenero() : genero(""), contador(0) {}
    };
    
    ContadorGenero contadores[50];
    int numGeneros = 0;
    
    Nodo<RegistroHistorial>* actual = historial.getAcciones().getFrente();
    
    while(actual != nullptr){
        // Solo considerar entradas activas del historial
        if(actual->dato.esActivo()){
            string genero = actual->dato.getContenido().getGenero();
            
            bool encontrado = false;
            for(int i = 0; i < numGeneros; i++){
                if(contadores[i].genero == genero){
                    contadores[i].contador++;
                    encontrado = true;
                    break;
                }
            }
            
            if(!encontrado && numGeneros < 50){
                contadores[numGeneros].genero = genero;
                contadores[numGeneros].contador = 1;
                numGeneros++;
            }
        }
        
        actual = actual->siguiente;
    }
    
    string generoMasVisto = "";
    int maxContador = 0;
    for(int i = 0; i < numGeneros; i++){
        if(contadores[i].contador > maxContador){
            maxContador = contadores[i].contador;
            generoMasVisto = contadores[i].genero;
        }
    }
    
    return generoMasVisto;
}

bool Recomendaciones::yaFueVisto(Historial& historial, int idContenido){
    Nodo<RegistroHistorial>* actual = historial.getAcciones().getFrente();
    
    while(actual != nullptr){
        // Solo considerar como visto si la entrada está activa
        if(actual->dato.esActivo() && actual->dato.getContenido().getId() == idContenido){
            return true;
        }
        actual = actual->siguiente;
    }
    
    return false;
}

// Algoritmo 1: Recomienda contenido del genero más visto por el usuario
// Si no hay contenido del género favorito, busca en otros géneros vistos
void Recomendaciones::recomendarPorGenero(Historial& historial, ListaDoble<Contenido>& catalogoCompleto, int limite){
    limpiarSugerencias();
    
    // Obtener todos los géneros ordenados por frecuencia
    struct ContadorGenero{
        string genero;
        int contador;
        ContadorGenero() : genero(""), contador(0) {}
    };
    
    ContadorGenero contadores[50];
    int numGeneros = 0;
    
    Nodo<RegistroHistorial>* actual = historial.getAcciones().getFrente();
    
    while(actual != nullptr){
        if(actual->dato.esActivo()){
            string genero = actual->dato.getContenido().getGenero();
            
            bool encontrado = false;
            for(int i = 0; i < numGeneros; i++){
                if(contadores[i].genero == genero){
                    contadores[i].contador++;
                    encontrado = true;
                    break;
                }
            }
            
            if(!encontrado && numGeneros < 50){
                contadores[numGeneros].genero = genero;
                contadores[numGeneros].contador = 1;
                numGeneros++;
            }
        }
        
        actual = actual->siguiente;
    }
    
    if(numGeneros == 0){
        return;
    }
    
    // Ordenar géneros por frecuencia (mayor a menor)
    for(int i = 0; i < numGeneros - 1; i++){
        for(int j = 0; j < numGeneros - i - 1; j++){
            if(contadores[j].contador < contadores[j + 1].contador){
                ContadorGenero temp = contadores[j];
                contadores[j] = contadores[j + 1];
                contadores[j + 1] = temp;
            }
        }
    }
    
    int contador = 0;
    
    // Intentar con cada género en orden de preferencia
    for(int g = 0; g < numGeneros && contador < limite; g++){
        string generoActual = contadores[g].genero;
        
        NodoDoble<Contenido>* nodoContenido = catalogoCompleto.getCabeza();
        
        while(nodoContenido != nullptr && contador < limite){
            Contenido& c = nodoContenido->dato;
            
            if(c.esActivo() && c.getGenero() == generoActual && !yaFueVisto(historial, c.getId())){
                sugerencias.insertar(c);
                contador++;
            }
            
            nodoContenido = nodoContenido->siguiente;
        }
    }
    
    // Si aún no hay suficientes, agregar contenido bien calificado de cualquier género
    if(contador < limite){
        NodoDoble<Contenido>* nodoContenido = catalogoCompleto.getCabeza();
        
        while(nodoContenido != nullptr && contador < limite){
            Contenido& c = nodoContenido->dato;
            
            if(c.esActivo() && c.getCalificacion() >= 8.0 && !yaFueVisto(historial, c.getId())){
                // Verificar que no esté ya en sugerencias
                bool yaEnSugerencias = false;
                NodoDoble<Contenido>* sug = sugerencias.getCabeza();
                while(sug != nullptr){
                    if(sug->dato.getId() == c.getId()){
                        yaEnSugerencias = true;
                        break;
                    }
                    sug = sug->siguiente;
                }
                
                if(!yaEnSugerencias){
                    sugerencias.insertar(c);
                    contador++;
                }
            }
            
            nodoContenido = nodoContenido->siguiente;
        }
    }
}

// Algoritmo 2: Recomienda contenido similar al ultimo visto (mismo genero y tipo)
void Recomendaciones::recomendarPorUltimoContenido(Historial& historial, ListaDoble<Contenido>& catalogoCompleto, int limite){
    limpiarSugerencias();
    
    if(historial.getAcciones().estaVacia()){
        return;
    }
    
    // Buscar el último contenido visto que esté activo en el historial
    Nodo<RegistroHistorial>* ultimoActivo = nullptr;
    Nodo<RegistroHistorial>* nodoActual = historial.getAcciones().getFrente();
    while(nodoActual != nullptr){
        if(nodoActual->dato.esActivo()){
            ultimoActivo = nodoActual;
        }
        nodoActual = nodoActual->siguiente;
    }
    
    if(ultimoActivo == nullptr){
        return;
    }
    
    // Usar genero y tipo directamente del historial (no importa si esta inactivo en catalogo)
    string generoUltimo = ultimoActivo->dato.getContenido().getGenero();
    string tipoUltimo = ultimoActivo->dato.getContenido().getTipo();
    int idUltimo = ultimoActivo->dato.getContenido().getId();
    
    NodoDoble<Contenido>* actual = catalogoCompleto.getCabeza();
    int contador = 0;
    
    while(actual != nullptr && contador < limite){
        Contenido& c = actual->dato;
        
        // Recomendar contenido activo del catalogo del mismo genero y tipo
        if(c.esActivo() && 
           c.getGenero() == generoUltimo && 
           c.getTipo() == tipoUltimo && 
           c.getId() != idUltimo &&
           !yaFueVisto(historial, c.getId())){
            sugerencias.insertar(c);
            contador++;
        }
        
        actual = actual->siguiente;
    }
    
    // Si no hay del mismo tipo y genero, buscar solo por genero
    if(contador == 0){
        actual = catalogoCompleto.getCabeza();
        while(actual != nullptr && contador < limite){
            Contenido& c = actual->dato;
            
            if(c.esActivo() && 
               c.getGenero() == generoUltimo && 
               c.getId() != idUltimo &&
               !yaFueVisto(historial, c.getId())){
                sugerencias.insertar(c);
                contador++;
            }
            
            actual = actual->siguiente;
        }
    }
}

// Algoritmo 3: Recomienda contenido mejor calificado que no ha sido visto
void Recomendaciones::recomendarPorCalificacion(Historial& historial, ListaDoble<Contenido>& catalogoCompleto, int limite){
    limpiarSugerencias();
    
    struct ContenidoTemp{
        Contenido contenido;
        bool existe;
        ContenidoTemp() : existe(false) {}
    };
    
    ContenidoTemp mejoresContenidos[100];
    int numContenidos = 0;
    
    NodoDoble<Contenido>* actual = catalogoCompleto.getCabeza();
    
    while(actual != nullptr && numContenidos < 100){
        Contenido& c = actual->dato;
        
        // Solo considerar contenido activo que no haya sido visto
        if(c.esActivo() && !yaFueVisto(historial, c.getId())){
            mejoresContenidos[numContenidos].contenido = c;
            mejoresContenidos[numContenidos].existe = true;
            numContenidos++;
        }
        
        actual = actual->siguiente;
    }
    
    for(int i = 0; i < numContenidos - 1; i++){
        for(int j = 0; j < numContenidos - i - 1; j++){
            if(mejoresContenidos[j].contenido.getCalificacion() < 
               mejoresContenidos[j + 1].contenido.getCalificacion()){
                ContenidoTemp temp = mejoresContenidos[j];
                mejoresContenidos[j] = mejoresContenidos[j + 1];
                mejoresContenidos[j + 1] = temp;
            }
        }
    }
    
    int maxItems = (limite < numContenidos) ? limite : numContenidos;
    for(int i = 0; i < maxItems; i++){
        if(mejoresContenidos[i].existe){
            sugerencias.insertar(mejoresContenidos[i].contenido);
        }
    }
}

void Recomendaciones::limpiarSugerencias(){
    while(!sugerencias.estaVacia()){
        sugerencias.eliminarNodo(sugerencias.getCabeza());
    }
}
