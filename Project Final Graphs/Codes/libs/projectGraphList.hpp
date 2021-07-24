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
	float tend_politica1; 
	float tend_politica2;
	float tend_politica3;
	float tend_politica4;

	Users(int id, string name, int follower_count, int followee_count); // Constructor
	Users(int id, string name);
	Users();
	~Users(); // Destructor
private:
	
};

class CompareOut{
public:
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

class CompareIn{
public:
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
	LinkedGraph(int nodos);
	~LinkedGraph();
	bool insertar(Users p, Users q);
	bool checkLink(Users p, Users q);
	vector<int>* vecinosDirectos(int p);
	void BFS(int origen);
	
	void printListOut();
	void printListIn();
	void ranking();

	void recorrerUsers();
private:
	vector<int>* lista_out;
	vector<int>* lista_in;

	int nodos;
	vector<Users> users;
	//vector<Users> heapify;
	priority_queue<Users, vector<Users>, CompareIn> Influencers;
	priority_queue<Users, vector<Users>, CompareOut> Influenciables;

	void __ranking();
};


/*
class Compare{
public:
    bool operator() (Users const& p1, Users const& p2){
	if (p1.out_degree > p2.out_degree) return false; 
	else if (p1.out_degree < p2.out_degree) return true;
	else{ 
		if (p1.followee_count > p2.followee_count) return false;
		else if (p1.followee_count < p2.followee_count) return true;
		}
	}
};
*/

#endif