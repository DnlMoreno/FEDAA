#ifndef LINKEDGRAPH_H
#define LINKEDGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Users{
public:
    int id;
    string name;
    int out_degree; // Seguidos
	int in_degree; // Seguidores
	bool influencer; // True si el usuario es influencer
	int num_influencers; // Cantidad de influencers en el 

	Users(int id, string name); // Constructor
	~Users(); // Destructor
private:
	
};

class LinkedGraph{
public:
	LinkedGraph(int nodos);
	~LinkedGraph();
	bool insertar(Users p, Users q);
	bool checkLink(Users p, Users q);
	vector<Users>* vecinosDirectos(Users p);
	void BFS(Users origen);
	
	void printListOut();
	void printListIn();
private:
	vector<Users>* lista_out;
	vector<Users>* lista_in;

	int nodos;
	vector<Users> users;
};

#endif