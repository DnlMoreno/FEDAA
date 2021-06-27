#include <string>
#include <list>
#include <iostream>
#include <cmath>
#include <algorithm>

#define DISP -1

#ifndef HASH_HPP_OPEN
#define HASH_HPP_OPEN

using namespace std;

class HashingOpen{
private:
	list<long long> *table;
	int capacidad; 
	int cantidad;
	float A = (sqrt(5) - 1) / 2;
    int __iniSize(int size);
	int __divFunction(long long k);
	int __mulFunction(long long k);
	void __agrandar();

public:
	HashingOpen(int size);
	~HashingOpen();
	int getCantidad();
	bool buscar(long long k);
	void eliminar(long long k);
    void insertar(long long k);
};

#endif