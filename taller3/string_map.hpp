template <typename T>
string_map<T>::string_map() : raiz(new Nodo), _size(0) {
    // COMPLETAR
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& original) {
    raiz->borrarNodos();
    delete raiz;
    raiz = new Nodo();
    raiz->copiarNodos(original.raiz);
    _size = original.size();
}

template <typename T>
string_map<T>::~string_map() {
    raiz->borrarNodos();
    delete raiz;
    raiz = nullptr;
}


template <typename T>
void string_map<T>::Nodo::copiarNodos(Nodo* original) {
    for (int i = 0; i < 256; ++i) {
        if (original->definicion != nullptr) {
            delete definicion;
            definicion = new T(*original->definicion);
        }
        if(original->siguientes[i] != nullptr){
            delete siguientes[i];
            siguientes[i] = new Nodo();
            siguientes[i]->copiarNodos(original->siguientes[i]);
        } else {
            delete siguientes[i];
            siguientes[i] = nullptr;
        }
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}

template<typename T>
void string_map<T>::insert(const pair<string, T>& cv){
    Nodo* actual = raiz;
    bool nuevaClave = false;
    for (int i = 0; i < cv.first.size(); ++i) {
        if(actual->siguientes[int(cv.first[i])] == nullptr){
            actual->siguientes[int(cv.first[i])] = new Nodo;
            actual = actual->siguientes[int(cv.first[i])];
            if (!nuevaClave) {
                nuevaClave = true;
            }
        }
        else {
            actual = actual->siguientes[int(cv.first[i])];
        }
    }
    if (nuevaClave){
        _size++;
        actual->definicion = new T (cv.second);
    } else {
        delete actual->definicion;
        actual->definicion = new T (cv.second);
    }
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if (_size == 0){
        return 0;
    }
    Nodo* actual = raiz;
    int i = 0;
    while(i < clave.size()){
        int letra = int(clave[i]);
        if (actual->siguientes[int(clave[i])] != nullptr){
            actual = actual->siguientes[int(clave[i])];
            i++;
        } else {
            return 0;
        }
        }
    if (i == clave.size() && actual->definicion != nullptr){
        return 1;
    }
    else {
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        actual = actual->siguientes[int(clave[i])];
    }
    return actual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        actual = actual->siguientes[int(clave[i])];
    }
    return *actual->definicion;
}
template <typename T>
bool string_map<T>::Nodo::trieVacio(vector<Nodo*> v){
    bool res = true;
    for(int i = 0; i < 256; i++){
        if(v[i] != nullptr){
            res = false;
        }
    }
    return res;
}

template <typename T>
void string_map<T>::Nodo::borrarNodos() {
    for(int i = 0; i < 256; i++){
        if (this->siguientes[i] != nullptr){
            this->siguientes[i]->borrarNodos();
            delete siguientes[i];
        }
    }
    delete this->definicion;
    definicion = nullptr;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo *ultimoNodoUtil = raiz;
    int ultimoIndice = 0;
    Nodo* actual = raiz;
    for(int i = 0; i < clave.size(); i++) {
        for (int j = 0; j < 256; j++) {
            if (j != int(clave[i]) && actual->siguientes[j] != nullptr){
                ultimoNodoUtil = actual;
                ultimoIndice = i;
            }
        }
        actual = actual->siguientes[int(clave[i])];
        if (actual->definicion != nullptr){
            ultimoNodoUtil = actual;
        }
        }
    if (actual == ultimoNodoUtil) {
        delete actual->definicion;
        actual->definicion = nullptr;
    } else if (actual->trieVacio(actual->siguientes) && ultimoNodoUtil != raiz) {
        ultimoNodoUtil->siguientes[ultimoIndice]->borrarNodos(); //mirar aca
        ultimoNodoUtil->siguientes[ultimoIndice] = nullptr; //mirar aca
    }
    else if (ultimoNodoUtil == raiz){
        ultimoNodoUtil->siguientes[int(clave[0])]->borrarNodos();
    }
    _size--;
    }

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}