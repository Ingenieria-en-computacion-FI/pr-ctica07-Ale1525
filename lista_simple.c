#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>   // malloc, free
#include <string.h>   // memcpy
#include <stdio.h>    // printf
#include "lista_simple.h"

// FUNCIONES PARA NODO
Nodo* crearNodo(void *dato, size_t size) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));  
    if (nuevo != NULL) {
        nuevo->siguiente = NULL;
        nuevo->dato = malloc(size);
        if (nuevo->dato == NULL) {             
            free(nuevo);
            return NULL;
        }
        memcpy(nuevo->dato, dato, size);
    }
    return nuevo;
}

void LiberarNodo(Nodo* n) {
    if (n != NULL && n->siguiente == NULL) {
        free(n->dato);
        free(n);
    }
}

bool ModificarNodo(Nodo* n, void* d, size_t size) {
    if (n != NULL) {
        memcpy(n->dato, d, size);
        return true;   
    }
    return false;
}

// CREAR / ESTADO

Lista* crearLista() {
    Lista* l = (Lista*)malloc(sizeof(Lista));  
    if (l != NULL) {                           
        l->head = l->tail = NULL;
    }
    return l;
}

bool esVacia(Lista* lista) {
    return lista->head == NULL;
}

// INSERCIONES

void insertarInicio(Lista* l, void* dato, size_t size) {  
    Nodo *nuevoNodo = crearNodo(dato, size);
    if (nuevoNodo == NULL) return;

    if (esVacia(l)) {
        l->head = l->tail = nuevoNodo;        
    } else {
        nuevoNodo->siguiente = l->head;
        l->head = nuevoNodo;
    }
}

void insertarFinal(Lista* l, void* dato, size_t size) {  
    Nodo *nuevoNodo = crearNodo(dato, size);
    if (nuevoNodo == NULL) return;

    if (esVacia(l)) {                         
        l->head = l->tail = nuevoNodo;
    } else {
        l->tail->siguiente = nuevoNodo;
        l->tail = nuevoNodo;                  
    }
}

void insertarPorPosicion(Lista* lista, void* dato, size_t size, int pos) {
    if (pos < 0) {
        printf("La posicion no es valida\n");
        return;
    }

    if (esVacia(lista) || pos == 0) {
        insertarInicio(lista, dato, size);
        return;
    }

    // Contar nodos
    int total = 0;
    for (Nodo *tmp = lista->head; tmp != NULL; tmp = tmp->siguiente) {  
        total++;
    }

    if (pos == total) {
        insertarFinal(lista, dato, size);
    } else if (pos >= 1 && pos < total) {
        Nodo *nuevoNodo = crearNodo(dato, size);
        if (nuevoNodo == NULL) return;

        Nodo *tmp = lista->head;
        for (int i = 0; i < pos - 1; i++) {   
            tmp = tmp->siguiente;
        }
        nuevoNodo->siguiente = tmp->siguiente;
        tmp->siguiente = nuevoNodo;
    } else {
        printf("La posicion no es valida\n");
    }
}
// ELIMINACIONES

void eliminarInicio(Lista* lista) {            
    if (esVacia(lista)) return;

    Nodo *tmp = lista->head;
    lista->head = lista->head->siguiente;
    if (lista->head == NULL)                   
        lista->tail = NULL;
    tmp->siguiente = NULL;
    LiberarNodo(tmp);
}

void eliminarFinal(Lista* lista) {             
    if (esVacia(lista)) return;

    if (lista->head == lista->tail) {          
        LiberarNodo(lista->head);
        lista->head = lista->tail = NULL;
        return;
    }

    Nodo *tmp = lista->head;                   
    for (; tmp->siguiente != lista->tail; tmp = tmp->siguiente);

    Nodo *aBorrar = lista->tail;
    lista->tail = tmp;
    lista->tail->siguiente = NULL;
    LiberarNodo(aBorrar);
}

void eliminarPorPosicion(Lista* lista, int pos) {
    if (esVacia(lista) || pos < 0) return;

    if (pos == 0) {
        eliminarInicio(lista);
        return;
    }

    Nodo *tmp = lista->head;                  
    for (int i = 0; i < pos - 1; i++) {
        if (tmp->siguiente == NULL) return;    
        tmp = tmp->siguiente;
    }

    Nodo *aBorrar = tmp->siguiente;
    if (aBorrar == NULL) return;

    if (aBorrar == lista->tail)                
        lista->tail = tmp;

    tmp->siguiente = aBorrar->siguiente;
    aBorrar->siguiente = NULL;
    LiberarNodo(aBorrar);
}

void eliminarPorElemento(Lista* lista, void* dato, CompararFunc cmp) {
    if (esVacia(lista)) return;

    // Caso: el primer nodo coincide
    while (lista->head != NULL && cmp(lista->head->dato, dato) == 0) {
        eliminarInicio(lista);
        return;
    }

    Nodo *prev = lista->head;
    Nodo *curr = lista->head ? lista->head->siguiente : NULL;

    while (curr != NULL) {
        if (cmp(curr->dato, dato) == 0) {
            prev->siguiente = curr->siguiente;
            if (curr == lista->tail)
                lista->tail = prev;
            curr->siguiente = NULL;
            LiberarNodo(curr);
            return;
        }
        prev = curr;
        curr = curr->siguiente;
    }
}

void eliminarTodosIguales(Lista* lista, void* dato, CompararFunc cmp) {
    if (esVacia(lista)) return;

    // Eliminar coincidencias al inicio
    while (lista->head != NULL && cmp(lista->head->dato, dato) == 0) {
        eliminarInicio(lista);
    }

    if (esVacia(lista)) return;

    Nodo *prev = lista->head;
    Nodo *curr = lista->head->siguiente;

    while (curr != NULL) {
        if (cmp(curr->dato, dato) == 0) {
            prev->siguiente = curr->siguiente;
            if (curr == lista->tail)
                lista->tail = prev;
            curr->siguiente = NULL;
            LiberarNodo(curr);
            curr = prev->siguiente;
        } else {
            prev = curr;
            curr = curr->siguiente;
        }
    }
}

// BÚSQUEDAS

void* buscarPorPosicion(Lista* lista, int pos) {
    if (esVacia(lista) || pos < 0) return NULL;

    Nodo *tmp = lista->head;
    for (int i = 0; i < pos; i++) {
        if (tmp == NULL) return NULL;
        tmp = tmp->siguiente;
    }
    return tmp ? tmp->dato : NULL;
}

int buscarPorElemento(Lista* lista, void* dato, CompararFunc cmp) {
    int i = 0;
    for (Nodo *tmp = lista->head; tmp != NULL; tmp = tmp->siguiente, i++) {
        if (cmp(tmp->dato, dato) == 0)
            return i;
    }
    return -1;  // no encontrado
}

// NAVEGACIÓN

Nodo* primero(Lista* lista) {
    return lista->head;
}

Nodo* ultimo(Lista* lista) {
    return lista->tail;
}

Nodo* siguiente(Nodo* actual) {
    return actual ? actual->siguiente : NULL;
}

// MODIFICAR

void modificar(Lista* lista, int pos, void* dato, size_t size) {
    Nodo *tmp = lista->head;
    for (int i = 0; i < pos; i++) {
        if (tmp == NULL) return;
        tmp = tmp->siguiente;
    }
    if (tmp != NULL)
        ModificarNodo(tmp, dato, size);
}

// UTILIDAD

void imprimirLista(Lista* lista, ImprimirFunc imprimir) {
    for (Nodo *tmp = lista->head; tmp != NULL; tmp = tmp->siguiente) {
        imprimir(tmp->dato);
    }
}

void vaciarLista(Lista* lista) {
    while (!esVacia(lista)) {
        eliminarInicio(lista);
    }
}

void borrarLista(Lista* lista) {
    vaciarLista(lista);
    free(lista);
}
