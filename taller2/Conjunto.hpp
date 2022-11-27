
template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _cardinal(0) {
}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruirNodos(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res = false;
    Nodo *actual = _raiz;
    while (actual != nullptr && !res) {
        if (clave < actual->valor) {
            actual = actual->izq;
        } else if (clave > actual->valor) {
            actual = actual->der;
        } else {
            res = true;
        }
    }
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (this->cardinal() == 0) {
        _raiz = new Nodo(clave);
        _cardinal++;
    }
    Nodo* anterior;
    Nodo* actual = _raiz;
    while(actual != nullptr && actual->valor != clave) {
        if(clave < actual->valor){
            anterior = actual;
            actual = actual->izq;
        }
        else {
            anterior = actual;
            actual = actual->der;
        }
    }
    if(actual == nullptr){
        if(anterior->valor > clave) {
            anterior->izq = new Nodo(clave);
            //(anterior->izq)->p = anterior;
            _cardinal++;
        }
        else {
            anterior->der = new Nodo(clave);
            //(anterior->der)->p = anterior;
            _cardinal++;
        }
    }
    else if(clave == actual->valor){
        return;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    Nodo *actual = _raiz;
    Nodo *anterior;
    while (actual != nullptr && actual->valor != clave) {
        if (clave < actual->valor) {
            anterior = actual;
            actual = actual->izq;
        } else {
            anterior = actual;
            actual = actual->der;
        }
    } //o bien actual es null (y el elemento a remover no existe) o bien en actual esta el valor a remover.
    if (actual != nullptr) {
        if (actual->der == nullptr && actual->izq == nullptr) { // hoja
            if (actual == _raiz) {
                delete actual;
                _raiz = nullptr;
            } else {
                if (actual == anterior->izq) {
                    anterior->izq = nullptr;
                } else {
                    anterior->der = nullptr;
                }
                delete actual;
            }
            _cardinal--;
        }
        else if (actual->der == nullptr || actual->izq == nullptr) { // 1 hijo
            if (actual == _raiz) {
                if (actual->der == nullptr) { // es raiz con un hijo izq.
                    _raiz = actual->izq;
                } else if (actual->izq == nullptr) { // es raiz con un hijo der
                    _raiz = actual->der;
                }
            } else {
                    if (actual->der == nullptr) {
                        if (anterior->der == actual) {
                            anterior->der == actual->izq;
                        } else {
                            anterior->izq == actual->izq;
                        }
                    } else {
                        if (anterior->der == actual) {
                            anterior->der = actual->der;
                        } else {
                            anterior->izq = actual->der;
                        }
                    }
                }
            delete actual;
            _cardinal--;
        }
        else { // 2 hijos
            const T siguiente = this->siguiente(clave);// Tiene 2 hijos.
            remover(siguiente);
            actual->valor = siguiente;
        }
    }
}



template<class T>
const T& Conjunto<T>::ultimoPadreDerecho(Nodo* n, T clave){
    Nodo* actual = _raiz;
    Nodo* ultimoPadreDerecho;
    while (actual->valor != clave && actual != nullptr){
        if (actual->valor > clave){
            ultimoPadreDerecho = actual;
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }
    return ultimoPadreDerecho->valor;
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo *actual = _raiz;
    Nodo *anterior;
    while (actual->valor != clave) {
        if (clave < actual->valor) {
            anterior = actual;
            actual = actual->izq;
        } else if (clave > actual->valor) {
            anterior = actual;
            actual = actual->der;
        }
    }
    if (actual->der != nullptr) {
        actual = actual->der;
        while (actual->izq != nullptr) {
            actual = actual->izq;
        }
        return actual->valor;
    } else if (anterior->izq == actual) {
        return anterior->valor;
    }
    else if (anterior->der == actual){
        return ultimoPadreDerecho(anterior, clave);
    }
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = _raiz;
    while(actual->izq != nullptr){
            actual = actual->izq;
        }
        return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
        Nodo* actual = _raiz;
        while(actual->der != nullptr){
            actual = actual->der;
        }
        return actual->valor;
    }

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template <class T>
void Conjunto<T>::destruirNodos(Nodo* n) {
if (n != nullptr) {
    destruirNodos(n->izq);
    destruirNodos(n->der);
    delete n;
}
}


