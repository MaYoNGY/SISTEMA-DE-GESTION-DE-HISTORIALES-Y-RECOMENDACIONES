#ifndef LISTADOBLE_H
#define LISTADOBLE_H

template <typename T>
struct NodoDoble{
	T dato;
	NodoDoble<T>* siguiente;
	NodoDoble<T>* anterior;
	
		NodoDoble(const T& d){
			dato = d;
			siguiente = nullptr;
			anterior = nullptr;
		}
};

template <typename T>
class ListaDoble{
    private:
        NodoDoble<T>* cabeza;
        NodoDoble<T>* cola;
        
    public:
        // Constructor
        ListaDoble() : cabeza(nullptr), cola(nullptr){}

        ~ListaDoble(){
            while(cabeza != nullptr){
                NodoDoble<T>* temp = cabeza;
                cabeza = cabeza->siguiente;
                delete temp;
            }
            cola = nullptr;
        }

        // Getter
        NodoDoble<T>* getCabeza() const{
                    return cabeza;
        }
        
        // Funciones
        bool estaVacia() const{
            return cabeza == nullptr;
        }

        void insertar(const T& dato){
            NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
            if(estaVacia()){
                cabeza = cola = nuevo;
            }else{
                cola->siguiente = nuevo;
                nuevo->anterior = cola;
                cola = nuevo;
            }
        }

        void eliminarNodo(NodoDoble<T>* nodo){
            if(estaVacia() || nodo == nullptr) return;
                
            if(nodo == cabeza && nodo == cola){  // Si es el unico nodo
                cabeza = nullptr;
                cola = nullptr;
            }else if(nodo == cabeza){  // Si es la cabeza 
                cabeza = nodo->siguiente;
                cabeza->anterior = nullptr;
            }else if(nodo == cola){  // Si es la cola
                cola = nodo->anterior;
                cola->siguiente = nullptr;
            }else{   // Nodo intermedio
                nodo->anterior->siguiente = nodo->siguiente;
                nodo->siguiente->anterior = nodo->anterior;
            }
            delete nodo;
        }
};

#endif