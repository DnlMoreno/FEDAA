#ifndef ARBOLBINARIOBUSQUEDA_H
#define ARBOLBINARIOBUSQUEDA_H

#include <cstddef> // Para utilizar el dato NULL
#include <iostream>

using namespace std;

class Nodo{
public:
	long long info;
	Nodo* izq;
	Nodo* der;
	Nodo* padre;
	Nodo(Nodo* padre, long long dato); // Constructor
	~Nodo(); // Destructor
private:
	
};

class ArbolBinarioBusqueda{
public:
	/***** Constructor y destructor *****/
	ArbolBinarioBusqueda();
	~ArbolBinarioBusqueda();

	/***** Operaciones basicas *****/
	void insertar(long long dato); 
	Nodo* buscar(long long dato);	
	void eliminar(long long dato);

	/***** Visualización del arbol *****/
	void mostrarArbol(long long contador);

private:
	Nodo* raiz;

	void __insertar(Nodo*& nodo, long long dato, Nodo*& padre);
	Nodo* __buscar(Nodo* nodo, long long dato);

	//***** Metodos utilizados en la eliminación *****/ 
	void __eliminar(Nodo* nodo, long long dato);
	void __eliminarNodo(Nodo* nodo);
	Nodo* __buscarMin(Nodo* nodo);
	void __reemplazar(Nodo* nodo, Nodo* new_nodo);
	void __destruirNodo(Nodo* nodo);

	void __mostrarArbol(Nodo* nodo, int contador);
};

#endif