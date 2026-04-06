#include <stddef.h>
#include <stdbool.h>
#include "lista_simple.h"
//Funciones para nodo hola
Nodo* crearNodo(void *dato, size_t size){
    Nodo *nuevo= (Nodo*)malloc(sizeof(Nodo))
    if(nuevo!=NULL){
        nuevo->siguiente=NULL;
        nuevo->dato = malloc(size);
        memcpy(nuevo->dato, dato, size);
    }
    return nuevo;
}

void LiberarNodo(Nodo* n){
    if(n !=NULL && n->siguiente == NULL){  
        free(n->dato);
        free(n);
    }
}

bool ModificarNodo(Nodo* n, void *d, size_t size){
     if(n !=NULL){
        memcpy(n->dato, d, size);
     }
}
// Callbacks
typedef int (*CompararFunc)(void*, void*);
typedef void (*ImprimirFunc)(void*);

//funciones para nodo
Nodo* crearNodo(void *dato, size_t size);
void LiberarNodo(Nodo* n);
bool ModificarNodo(Nodo* n, void* d);

// Crear / estado
Lista* crearLista(){
    lista* l = (lista*)malloc(sizeof(lista));
    if(l = NULL){
        l->head = l->tail = NULL;
    }
    return l;
}

bool esVacia(Lista* lista){
    return lista->head == NULL;
}

// Inserciones
void insertarInicio(Lista* lista *l, void* dato, size_t size){
    Nodo *nuevoNodo = crearNodo(dato, size);
    nuevoNodo->siguiente = l->head;
    l->head = nuevoNodo;

}

void insertarFinal(Lista* lista *l, void* dato, size_t size){
    Nodo *nuevoNodo = crearNodo(dato, zise);
    l->tail->siguiente = nuevoNodo;
    l->tail = nuevoNodo
}

void insertarPorposicion(Lista* lista, void* dato, size_t size, int pos){
    if(esVacia(lista)){
        Nodo *nuevoNodo = crearNodo(dato, size);
        l->head = l->tail = nuevoNodo;
        return;
    }
    int total =0;
    for(Nodo *tmp = lista->head; tmp !=NULL; tmp->siguiente){
        total++;
    }
    if(pos==0){
        insertarInicio(lista, dato, size);
    }else if(pos == total){

    }else if(pos >=1 && pos <total){

    }else{
        print("La posiciion no es valida\n");
    }

}
// Eliminaciones
void eliminarInicio(Lista* lista){
    Nodo *tmp = l->head;
    l->head = l->head->siguiente
    tmp->siguiente = NULL;
    LiberarNodo(tmp);
}
void eliminarFinal(Lista* lista){
    Nodo *tmp = l->head
    for( ;tmp->siguiente !=l->tail; tmp = tmp->siguiente);

    l->tail = tmp;
    tmp = l->tail->siguiente;
    l->tail->siguiente = NULL;
    
    LiberarNodo(tmp);
}
void eliminarPorPosicion(Lista* lista, int pos){
    for(int i=0; i <p-1, i++){
        tmp = tmp->siguiente;
    }
}
void eliminarPorElemento(Lista* lista, void* dato, CompararFunc cmp);
void eliminarTodosIguales(lista* lista, void* dato, CompararFunc cmp);
// Búsquedas
void* buscarPorPosicion(Lista* lista, int pos);
int buscarPorElemento(Lista* lista, void* dato, CompararFunc cmp);

// Navegación
Nodo* primero(Lista* lista);
Nodo* ultimo(Lista* lista);
Nodo* siguiente(Nodo* actual);

// Modificar
void modificar(Lista* lista, int pos, void* dato, size_t size);

// Utilidad
void imprimirLista(Lista* lista, ImprimirFunc imprimir);
void vaciarLista(Lista* lista);
void borrarLista(Lista* lista);

#endif
