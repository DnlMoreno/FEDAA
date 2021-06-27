#include "arbolBinarioBusqueda.hpp"

/*********************************/
/*******    CLASE NODO     *******/
/*********************************/

// Nodo inicializado
Nodo::Nodo(Nodo* padre, long long dato){
    this->info = dato; 
	izq = NULL;
	der = NULL;
    this->padre = padre;
}

Nodo::~Nodo(){
	delete izq;
	delete der;
}


/*****************************************************/
/*******    CLASE ARBOL BINARIO DE BUSQUEDA    *******/
/*****************************************************/

ArbolBinarioBusqueda::ArbolBinarioBusqueda(){
	raiz = NULL;
}

ArbolBinarioBusqueda::~ArbolBinarioBusqueda(){
	delete raiz;
}

int cont = 0;

/*************************************************/
/*******    Operaciones esenciales ABB     *******/
/*************************************************/

void ArbolBinarioBusqueda::insertar(long long dato){
    //cout << "raiz: " << raiz << endl;
	__insertar(raiz, dato, raiz);
}

Nodo* ArbolBinarioBusqueda::buscar(long long dato){
	return __buscar(raiz, dato);
}

void ArbolBinarioBusqueda::eliminar(long long dato){
    return __eliminar(raiz, dato);
}

void ArbolBinarioBusqueda::mostrarArbol(long long contador){
    return __mostrarArbol(raiz, contador);
}

/*******************************************/
/*******    Metodos internos ABB     *******/
/*******************************************/

void ArbolBinarioBusqueda::__insertar(Nodo*& nodo, const long long dato, Nodo*& padre){
	// Caso base
	if(nodo == NULL){
        //cout << "Caso base - Se insertar el nodo: " << dato << endl;
		nodo = new Nodo(padre, dato); // Se inserta el dato
	}
    // Caso recursivo
    else{
        if(dato < nodo->info){
            __insertar(nodo->izq, dato, nodo);
        }
        else{
            __insertar(nodo->der, dato, nodo);
        }
    }	
}

Nodo* ArbolBinarioBusqueda::__buscar(Nodo* nodo, long long dato){
	// Caso base
	if(nodo == NULL){	// No existe el dato
        //cout << "Dato no existe" << endl;
		return NULL;
	}
	// Casos recursivos
	else if(dato < nodo->info){
        //cout << "Izquierda" << endl;
		return __buscar(nodo->izq, dato);
	}
    else if(dato > nodo->info){
        //cout << "Derecha" << endl;
        return __buscar(nodo->der, dato);
    }	
    // El dato se encontro
    else{
        //cout << "El dato es: " <<  nodo->info << endl;
        //cout << "Su padre es: " <<  nodo->padre->info << endl;
        return nodo; 
    }
}

/**** Metodos utilizados en la eliminación de un elemento ****/
void ArbolBinarioBusqueda::__eliminar(Nodo* nodo, long long dato){
    // ELimina un nodo del arbol
	// Caso base
	if(nodo == NULL){	// No existe el dato
        cout << "Dato no existe" << endl;
		return;
	}
	// Casos recursivos
	else if(dato < nodo->info){ // Busca por la izquierda
        cout << "Izquierda" << endl;
		__eliminar(nodo->izq, dato);
	}
    else if(dato > nodo->info){ // Busca por la derecha
        cout << "Derecha" << endl;
        __eliminar(nodo->der, dato);
    }	
    // Nodo con 1 hijo, o nodo es hoja
    else{
        __eliminarNodo(nodo);
    }
    cout << "El dato es: " <<  nodo->info << endl;
}

void ArbolBinarioBusqueda::__eliminarNodo(Nodo* nodo){
    // Funcion que elimina el nodo encontrado
    // Nodo tiene 2 hijos
    if(nodo->izq && nodo->der){
        Nodo* temp = __buscarMin(nodo->der); // Se busca el nodo menor
        nodo->info = temp->info;
        __eliminarNodo(temp); // Se elimina temp
    }
    // Nodo tiene 1 hijo izquierdo
    else if(nodo->izq){
        __reemplazar(nodo,nodo->izq);
        __destruirNodo(nodo);
    }
    // Nodo tiene 1 hijo derecho
    else if(nodo->der){
        __reemplazar(nodo,nodo->der);
        __destruirNodo(nodo);
    }
    // Nodo no tiene hijos
    else{
        __reemplazar(nodo, NULL);
        __destruirNodo(nodo);
    }
}

Nodo* ArbolBinarioBusqueda::__buscarMin(Nodo* nodo){
    // Busca el valor minimo

    // El arbol esta vacio
	if(nodo == NULL){	
        cout << "Dato no existe" << endl;
		return NULL;
	}
    // Nodo no tiene hijo izquierdo
    if (nodo->izq == NULL){
        return nodo;
    }
    // Se busca la parte mas izquierda posible
    else{
        return __buscarMin(nodo->izq);
    }
}

void ArbolBinarioBusqueda::__reemplazar(Nodo* nodo, Nodo* new_nodo){
    //Función que permite reemplazar dos nodos
    //Al padre del nodo que se va a eliminar se le asgina el nuevo hijo
    if(nodo->padre){
        // En el caso de que tenga un hijo izquierdo
        if(nodo->info == nodo->padre->izq->info){
            nodo->padre->izq = new_nodo;
        }
        // En el caso de que tenga un hijo derecho
        else if(nodo->info == nodo->padre->der->info){
            nodo->padre->der = new_nodo;
        }
    }
    //Al hijo se le asigna el nuevo padre
    if(new_nodo){
        new_nodo->padre = nodo->padre;
    }
}

void ArbolBinarioBusqueda::__destruirNodo(Nodo* nodo){
    //Funcion que destruye un nodo
    nodo->izq = NULL;
    nodo->der = NULL;

    delete nodo;
}

/**** Metodo que permite visualizar el arbol ****/
void ArbolBinarioBusqueda::__mostrarArbol(Nodo* nodo, int contador){
	// Caso base
	if(nodo == NULL){	// No existe el dato
		return;
	}
	// Casos recursivos
	else{
		__mostrarArbol(nodo->der, contador+1);
        for(int i = 0; i < contador; i++){
            cout << "   ";
        }
        cout << nodo->info << endl;
        __mostrarArbol(nodo->izq, contador+1);
	}
}
