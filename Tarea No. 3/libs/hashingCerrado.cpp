#include "hashingCerrado.hpp"

/***********************************************/
/*******    Constructor y destructor     *******/
/***********************************************/

HashingClosed::HashingClosed(int size){
    int tam = __iniSize(size);
	capacidad = tam;
	cantidad = 0;
	table = new long long[capacidad];
	for(int i = 0; i < capacidad; i++) table[i] = DISP; // Se rellenan los valores de la tabla hash con -1 (vacio)
}

HashingClosed::~HashingClosed(){
	delete [] table;
}

int HashingClosed::getCantidad(){
	return cantidad;
}

/********************************************************/
/*******    Operaciones esenciales Tabla Hash     *******/
/********************************************************/

int HashingClosed::buscar(long long k){
/* Busqueda de un valor
    Parameters:
        k: Clave que se quiere buscar en la tabla hash

    Returns:
        int: Devuelve la casilla en donde se encuentra el valor buscado
        Si no se encuentra el elemento, se levanta un aviso
                                                        */
	int pos;	
	pos = __doubleHashing(k, 0);
	int i = 1;

    // Se busca el elemento en la primera posible casilla
    if (table[pos] == k){
        //cout << "El elemento " << k << " fue encontrado en el indice: " << pos << endl;
        return pos;
    }

    // Se busca el elemento en todas las posibles posiciones que pudo haber quedado en la tabla
    // Si una de las celdas que se busca esta vacia, significa que el elemento no esta en la tabla
	while(table[pos] != DISP){        
		pos = __doubleHashing(k+i, i); 
        i++;
        if (table[pos] == k){
            //cout << "El elemento " << k << " fue encontrado en el indice: " << pos << endl;
            return pos;
        }
	}
    //cout << "El elemento no se encuentra en la tabla" << endl; 
	return DISP;
}

void HashingClosed::eliminar(long long k){
/* Eliminación de un elemento de la tabla
    Returns:
        Devuelve una tabla hash con el elemento eliminado, es decir, con esa la casilla vacia,
        Si no se encuentra el elemento, se levanta un aviso
                                                            */
	int pos;	
    bool flag = false;
	pos = __doubleHashing(k, 0);
	int i = 1;

    // Se busca el elemento en la primera posible casilla
    if (table[pos] == k){
        cout << "El elemento " << table[pos] << " fue ELIMINADO del indice: " << pos << endl;
        table[pos] = DISP;
        cout << "Nueva casilla: " << table[pos] << endl;
        flag = true;
    }

    // Se busca el elemento en todas las posibles posiciones que pudo haber quedado en la tabla
    // Si una de las celdas que se busca esta vacia, significa que el elemento no esta en la tabla
	while(table[pos] != DISP){        
		pos = __doubleHashing(k+i, i); 
        i++;
        if (table[pos] == k){
            cout << "El elemento " << table[pos] << " fue ELIMINADO del indice: " << pos << endl;
            table[pos] = ELIM;
            cout << "Nueva casilla: " << table[pos] << endl;
            flag = true;
            break;
        }
	}
    if (flag == false) cout << "El elemento no se encuentra en la tabla" << endl; 
}

void HashingClosed::insertar(long long k){
/* Inserción de valores
    Parameters:
        k: Clave que se quiere insertar en la tabla hash

    Returns:
        Se inserta el valor en una casilla vacia de la tabla hash
                                                                */

    // Control del factor de carga, si esta muy lleno se agranda la tabla
	if((float)cantidad/(float)capacidad > 0.7){	
		//cout << "La tablita se esta agrandando" << endl;
        __agrandar();
	}

	int pos;	
	pos = __doubleHashing(k, 0);
	int i = 1;

    // Mientras la posicion este ocupada se ira sondeando la tabla
	while(table[pos] != DISP & table[pos] != ELIM){
        //cout << "Posicion" << i << ": " << pos << endl;
        //cout << "Ocurrio una colision en el indice " << pos << " con el elemento: " << k; 
		pos = __doubleHashing(k+i, i);
        //cout << " --- el elemento " << k << " se cambio a " << pos << endl; 
		i++;
	}
    //cout << "El indice es " << pos << " para el elemento: " << k << endl; 
	table[pos] = k;
	cantidad++;
}

/*****************************************/
/*******    Metodos de control     *******/
/*****************************************/

int HashingClosed::__iniSize(int size){
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

void HashingClosed::__agrandar(){
/* Agrandar la Tabla Hash
    Returns:
        Devuelve una tabla hash con el (doble de tamaño) * 1,3 acercado al primo mayor mas cercano junto con los valores reacomodados
                                                                                */

	long long aux[capacidad]; // array con capacidad actual
    int temp = capacidad;

	// Copia todo la tabla en un array aux
	for(int i = 0; i < capacidad; i++) aux[i] = table[i];
	
	capacidad *= 2; // Se duplica la capacidad
    capacidad = __iniSize(capacidad); // Nueva capacidad

	// Vacia y duplica tabla
	table = new long long[capacidad];
	for(int i = 0; i < capacidad; i++){
		table[i] = DISP;
	}
	
	cantidad = 0;

    //cout << "Temporal: " << temp << endl;

	// Se reacomodan los elementos
	for(int i = 0; i < temp; i++){
		if(aux[i] != DISP){
			insertar(aux[i]);
		}
	}	
}

/*************************************/
/*******    Funciones hash     *******/
/*************************************/

int HashingClosed::__divFunction(long long k) {
/* Método de la división
    Parameters:
        k: Clave a la cual se aplicara la función hash

    Returns:
        int: Numero hash
                        */

  return k%capacidad;
}

int HashingClosed::__mulFunction(long long k) {
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

/**************************************/
/*******    Hashing cerrado     *******/
/**************************************/

int HashingClosed::__doubleHashing(long long k,  int i) {
/* Manejo de colisión con hashing cerrado utilizando double hashing
    Parameters:
        k: Clave a la cual se aplicara la función hash
        i: Número del intento
        
    Returns:
        int: Numero hash
                         */

    return (__divFunction(k) + i*(__divFunction(k)+1)) % capacidad;
}

