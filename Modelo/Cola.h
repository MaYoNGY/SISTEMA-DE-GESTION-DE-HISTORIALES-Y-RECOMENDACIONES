#ifndef COLA_H
#define COLA_H

template <typename T>
struct Nodo{
    T dato;
    Nodo<T>* siguiente;
    
        Nodo(const T& u){
            dato = u;
            siguiente = nullptr;
        }
};

template <typename T>
class Cola{
    private:
        Nodo<T>* frente;
        Nodo<T>* fondo;
        int tamanio;
        int limite;
        
    public:
        // Constructor
        Cola(int limite){
            frente = nullptr;
            fondo = nullptr;
            tamanio = 0;
            this->limite = limite; // Establece un limite predeterminado
        }

        ~Cola(){
            while (!estaVacia()){
                desencolar();
            }
        }

        // Constructor de copia
        Cola(const Cola<T>& otra) : frente(nullptr), fondo(nullptr), tamanio(0), limite(otra.limite) {
            Nodo<T>* actual = otra.frente;
            while (actual != nullptr) {
                encolar(actual->dato);
                actual = actual->siguiente;
            }
        }

        // Operador de asignacion
        Cola<T>& operator=(const Cola<T>& otra) {
            if (this != &otra) {
                while (!estaVacia()) {
                    desencolar();
                }
                limite = otra.limite;
                Nodo<T>* actual = otra.frente;
                while (actual != nullptr) {
                    encolar(actual->dato);
                    actual = actual->siguiente;
                }
            }
            return *this;
        }

        // Getter
        Nodo<T>* getFrente() const{
            return frente;
        }

        int getLimite() const{
            return limite;
        }

        int getTamanio() const{
            return tamanio;
        }

        // Funciones
        bool estaVacia() const{
            return frente == nullptr;
        }

        void encolar(const T& dato){
            Nodo<T>* nuevo = new Nodo<T>(dato);
            if(estaVacia()){
                frente = fondo = nuevo;
            }else{
                fondo->siguiente = nuevo;
                fondo = nuevo;
            }

            tamanio++;

            if(tamanio > limite){
                desencolar();
            }
        }

        void desencolar(){
            if (!estaVacia()){
                Nodo<T>* temp = frente;
                frente = frente->siguiente;
                delete temp;
                tamanio--;

                if(frente == nullptr){
                    fondo = nullptr;
                }
            }
        }            
};

#endif
