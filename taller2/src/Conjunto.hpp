
template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _cardinal(0) {
}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruirNodos(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
        Nodo* actual = _raiz;
        while(actual !=nullptr && clave != actual->valor){
            if(clave < actual->valor){
                actual = actual->izq;
            }
            else {
                actual = actual->der;
            }
        }
        if (actual == nullptr){
            return false;
        }
        else return true;
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
        if(clave < anterior->valor) {
            anterior->izq = new Nodo(clave);
            (anterior->izq)->p = anterior;
            _cardinal++;
        }
        else {
            anterior->der = new Nodo(clave);
            (anterior->der)->p = anterior;
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
    while (actual != nullptr && actual->valor != clave) {
        if (clave < actual->valor) {
            actual = actual->izq;
        } else if (clave > actual->valor) {
            actual = actual->der;
        }
    } //o bien actual es null (y el elemento a remover no existe) o bien en actual esta el valor a remover.
    if (actual == nullptr) {
        return;
    }
    if(actual == _raiz && actual->izq == nullptr && actual->der == nullptr){ //solo es la raiz
        _raiz = nullptr;
        delete actual;
        _cardinal--;
    }
    else if (actual == _raiz && actual->der == nullptr){ // es raiz con un hijo izq.
        _raiz = actual->izq;
        (actual->izq)->p = nullptr;
        delete actual;
        _cardinal--;
    }
    else if (actual == _raiz && actual->izq == nullptr){ // es raiz con un hijo der
        _raiz = actual->der;
        (actual->der)->p = nullptr;
        delete actual;
        _cardinal--;
    }
    else if (actual->der == nullptr && actual->izq == nullptr){ // Es una hoja no raiz.
        Nodo* padre = actual->p;
        if(actual == padre->izq){
            padre->izq = nullptr;
            delete actual;
            _cardinal--;
        }
        else {
            padre->der = nullptr;
            delete actual;
            _cardinal--;
        }
    }
    else if (actual->der == nullptr || actual->izq == nullptr){ // Tiene un solo hijo.
        if (actual->der == nullptr){
            actual->p->izq = actual->izq;
            actual->izq->p = actual->p;
            delete actual;
            _cardinal--;
        }
        else {
            actual->p->der = actual->der;
            actual->der->p = actual->p;
            delete actual;
            _cardinal--;
        }
    }
    else {
        T siguiente = this->siguiente(actual->valor);// Tiene 2 hijos.
        remover(siguiente);
        actual->valor = siguiente;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo *actual = _raiz;
    while (actual->valor != clave) {
        if (clave < actual->valor) {
            actual = actual->izq;
        } else if (clave > actual->valor) {
            actual = actual->der;
        }
    }
    if (actual->der != nullptr) {
        actual = actual->der;
        while (actual->izq != nullptr) {
            actual = actual->izq;
        }
        return actual->valor;
    } else {
        Nodo *padre = actual->p;
        while (actual == padre->der) {
            actual = padre;
            padre = padre->p;
        }
        return padre->valor;
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
    return this->_cardinal;
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


