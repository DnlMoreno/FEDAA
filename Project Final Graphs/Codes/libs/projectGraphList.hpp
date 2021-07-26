#ifndef LINKEDGRAPH_H
#define LINKEDGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <queue>
#include <unordered_map> 

using namespace std;

class Users{
public:
	Users(int id, string name, int follower_count, int followee_count); // Constructor que inicializa los usuarios seguidores 
	Users(int id, string name); // Constructor que inicializa los usuarios que son seguidos
	Users(); // Constructor por default
	~Users(); // Destructor

	// Información de la bbdd
    int id;
    string name;
	int follower_count;
	int followee_count;	

	// Información obtenida despues
    int out_degree; // Seguidos
	int in_degree; // Seguidores
	bool influencer; // True si el usuario es influencer

	// Tendencia politica de cada usuario obtenida del BFS
	float tend_politica1; // Cooperativa
	float tend_politica2; // soyvaldiviacl
	float tend_politica3; // latercera
	float tend_politica4; // elmostrador

private:
	
};

// Comparador que sirve para obtener los influenciables de una cola de prioridad
class CompareOut{
public:
	// Se prioriza el mayor out_degree y en caso de empate, se prioriza el mayor num. de seguidos de la red real
    bool operator()(Users const& p1, Users const& p2) const{
		if (p1.out_degree > p2.out_degree) return false; 
		else if (p1.out_degree < p2.out_degree) return true;
		else{ 
			if (p1.followee_count > p2.followee_count) return false;
			else if (p1.followee_count <= p2.followee_count) return true;
		}
	}
private:

};

// Comparador que sirve para obtener los influencers de una cola de prioridad
class CompareIn{
public:
	// Se prioriza el mayor in_degree y en caso de empate, se prioriza el mayor num. de seguidores de la red real
    bool operator()(Users const& p1, Users const& p2) const{
		if (p1.in_degree > p2.in_degree) return false;
		else if (p1.in_degree < p2.in_degree) return true;
		else{ 
			if (p1.follower_count > p2.follower_count) return false;
			else if (p1.follower_count <= p2.follower_count) return true;
		}
	}
private:

};

class LinkedGraph{
public:
	// Constructor y destructor
	LinkedGraph(int nodos);
	~LinkedGraph();

	// Metodos esenciales
	bool insertar(Users p, Users q);
	vector<int>* vecinosDirectos(int p);
	void ranking(); // Obtiene el top 10 de influyentes e influenciables
	void tendenciaPolitica(); // Obtiene la tendencia politica de cada usuario, pero primero se deben sacar los influyentes e influenciables
	void SCC(); // Obtiene las componentes fuertemente conexas

	void printListOut();
	void printListIn();
	void recorrerUsers();
private:
	int nodos;
	vector<int>* lista_out; // Lista que contiene los out_degree de cada vertice
	vector<int>* lista_in; // Lista que contiene los in_degree de cada vertice
	vector<Users> users; // Vector que tiene a los usuarios ordenados por indice

	// Ordena a los infuencer e influenciables
	priority_queue<Users, vector<Users>, CompareIn> Influencers;
	priority_queue<Users, vector<Users>, CompareOut> Influenciables;

	// Metodos internos
	void __ranking();
	void __BFSmodificado(int origen, ofstream &file);
	void __porcentajeTendencias(unordered_map<int, vector<int>> &datos, int id_usuario, vector<bool> &prueba, ofstream &file);
    void __SCCUtil(int u, int disc[], int low[], int &time, bool stackMember[], stack<int>&stk, ofstream &file);
};

#endif