#include "Lista.h"
#include <assert.h>

Lista::Lista() : prim(nullptr), ult(nullptr) {
}

Lista::Lista(const Lista& l) : Lista(){
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    destruirNodos();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    destruirNodos();
    copiarNodos(aCopiar);
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(nullptr, elem, nullptr);
    if (longitud() == 0) {
        prim = nuevo;
        ult = nuevo;
    } else {
        nuevo->sig = prim;
        prim->prev = nuevo;
        prim = nuevo;
    }
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo(nullptr, elem, nullptr);
    if (longitud() == 0) {
        prim = nuevo;
        ult = nuevo;
    } else {
        nuevo->prev = ult;
        ult->sig = nuevo;
        ult = nuevo;
    }
}

void Lista::eliminar(Nat i) {
    Nodo* actual = prim;
    for (int j = 0; j < i; ++j) {
        actual = actual->sig;
    }
    if (longitud() == 1){
        delete actual;
        prim = nullptr;
        ult = nullptr;
    }
    else if ( actual == prim){
        (actual->sig)->prev = nullptr;
        prim = actual->sig;
        delete actual;
    }
    else if (actual == ult){
        (actual->prev)->sig = nullptr;
        ult = actual->prev;
        delete actual;
    }
    else {
        (actual->sig)->prev = actual->prev;
        (actual->prev)->sig = actual->sig;
        delete actual;
    }
}

int Lista::longitud() const {
    Nodo* actual = prim;
    int i = 0;
    while (actual != nullptr) {
        actual = actual->sig;
        i++;
    }
    return i;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* actual = prim;
    for (int j = 0; j < i; ++j) {
        actual = actual->sig;
    }
    return actual->valor;
// i = 3 (busco el elem 3)
// {1 , 2, 3, 4, 5}
}

int& Lista::iesimo(Nat i) {
    Nodo* actual = prim;
    for (int j = 0; j < i; ++j) {
        actual = actual->sig;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    // Completar
}

void Lista::copiarNodos(const Lista &o) {
    int i = o.longitud();
    for (int j = 0; j < i; ++j) {
        agregarAtras(o.iesimo(j));
    }
}

void Lista::destruirNodos() {
    Nodo* actual = prim;
    while (actual != nullptr){
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
    prim = nullptr;
    ult = nullptr;
}
