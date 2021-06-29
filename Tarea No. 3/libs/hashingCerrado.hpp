#include <string>
#include <iostream>
#include <cmath>

#define DISP -1
#define ELIM -2

#ifndef HASH_HPP_CLOSED
#define HASH_HPP_CLOSED

using namespace std;

class HashingClosed{
private:
	long long* table; // Array de long long
	int capacidad; 
	int cantidad;
	float A = (sqrt(5) - 1) / 2;
    int __iniSize(int size);
	int __divFunction(long long k);
	int __mulFunction(long long k);
	int __doubleHashing(long long k,  int i);
	void __agrandar();

public:
	/***** Constructor y destructor *****/
	HashingClosed(int size);
	~HashingClosed();
	int getCantidad();
	int getCapacidad();

	/***** Operaciones basicas *****/
	int buscar(long long k);	// retorna posicion
	void eliminar(long long k);
	void insertar(long long k);	// Numeros > 0
};

#endif