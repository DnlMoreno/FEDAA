#include "hashingAbierto.hpp"

/***********************************************/
/*******    Constructor y destructor     *******/
/***********************************************/

HashingOpen::HashingOpen(int size){
    int tam = __iniSize(size);
	capacidad = tam;
    table = new list<long long>[capacidad];
}

HashingOpen::~HashingOpen(){
	delete [] table;
}

int HashingOpen::getCantidad(){
	return cantidad;
}

int HashingOpen::getCapacidad(){
	return capacidad;
}

/********************************************************/
/*******    Operaciones esenciales Tabla Hash     *******/
/********************************************************/

bool HashingOpen::buscar(long long k){
/* Busqueda de un valor
    Parameters:
        k: Clave que se quiere buscar en la tabla hash

    Returns:
        int: Devuelve la casilla en donde se encuentra el valor buscado
        Si no se encuentra el elemento, se levanta un aviso
                                                        */
    
    // Se obtiene el indice de la clave
    int casilla = __divFunction(k);

    // Recorre la lista enlazada
    list<long long> :: iterator it;
    for(it = table[casilla].begin(); it != table[casilla].end(); it++){
        if (*it == casilla) return true;
    }
    return false;
}

void HashingOpen::eliminar(long long k){
/* Eliminación de un elemento de la tabla
    Returns:
        Devuelve una tabla hash con el elemento eliminado de la lista enlazada
                                                            */

    // Se obtiene el indice de la clave
    int casilla = __divFunction(k);

    // Recorre la lista enlazada
    list<long long> :: iterator it;
    for(it = table[casilla].begin(); it != table[casilla].end(); it++){
        if (*it == casilla) break;
    }
    
    // Si la clave esta en la tabla, se elimina
    if (it != table[casilla].end()){ 
        table[casilla].erase(it); 
    }
}

void HashingOpen::insertar(long long k){
/* Inserción de valores
    Parameters:
        k: Clave que se quiere insertar en la tabla hash

    Returns:
        Se inserta el valor en la lista enlazada correspondiente a la casilla de la tabla hash
                                                                */

    
    long long casilla = __divFunction(k);
    table[casilla].push_front(k);

	cantidad++;
}

/*****************************************/
/*******    Metodos de control     *******/
/*****************************************/

int HashingOpen::__iniSize(int size){
/* Tamanio inicial para la Tabla Hash
    Parameters:
        size: Tamaño de los datos que se quieren guardar

    Returns:
        int: Devuelve el numero de casillas iniciales para la tabla Hash
                                                                        */
    int valor = 1.3 * size;
    bool primo = true;
    int i = 0;

    // Comprueba si el valor es un numero primo
    for(int i = 2; i<valor && primo == true; i++){
        if (valor % i == 0) primo = false;
    }

    // Acerca al numero primo mas cercano
    while (primo == false){
        valor++;
        bool flag = false;
        for(int i = 2; i<valor && flag == false; i++){
            if (valor % i == 0) flag = true; // no es primo
        }
        if (flag == false) primo = true; 
    }
    return valor;
}


/*************************************/
/*******    Funciones hash     *******/
/*************************************/

int HashingOpen::__divFunction(long long k){
/* Método de la división
    Parameters:
        k: Clave a la cual se aplicara la función hash

    Returns:
        int: Numero hash
                        */

  return k%capacidad;
}

int HashingOpen::__mulFunction(long long k) {
/* Método de la multiplicación
    Parameters:
        k: Clave a la cual se aplicara la función hash
        
    Returns:
        int: Numero hash
                        */

  double a = (double)k*A;
  a -= (long long)a; // Esta línea implementa la operación módulo 1 (%1)

  return capacidad*a;
}
