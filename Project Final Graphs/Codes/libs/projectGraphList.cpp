#include "ProjectGraphList.hpp"

/*********************************/
/*******    CLASE NODO     *******/
/*********************************/

// Nodo inicializado
Users::Users(int id, string name){
    this->id = id; 
	this->name = name; 
    this->out_degree = 0; // Seguidos
	this->in_degree = 0; // Seguidores
	this->influencer = false; // True si el usuario es influencer
	this->num_influencers = 0; // Cantidad de influencers en el 
}

Users::~Users(){
}


/*****************************************************/
/*******    CLASE ARBOL BINARIO DE BUSQUEDA    *******/
/*****************************************************/

LinkedGraph::LinkedGraph(int nodos){
	this->nodos = nodos;
	lista = new vector<Users>[nodos];
}

LinkedGraph::~LinkedGraph(){
	delete [] lista;
}

bool LinkedGraph::insertar(Users p, Users q){
	if(p.id >= nodos || q.id >= nodos) return false; // no se inserto fuera de rango
	for(int i = 0; i < lista[p.id].size(); i++){
		if(lista[p.id][i].id == q.id) return false; // arista ya insertada
	}
	lista[p.id].push_back(q);
	return true;
}

bool LinkedGraph::checkLink(Users p, Users q){
	if(p.id >= nodos || q.id >= nodos) return false; // fuera de rango
	for(int i = 0; i < lista[p.id].size(); i++){
		if(lista[p.id][i].id == q.id) return true;
	}
	return false;
}

vector<Users>* LinkedGraph::vecinosDirectos(Users p){
	if(p.id >= nodos) return NULL; // fuera de rango
	return &(lista[p.id]);
}

void LinkedGraph::BFS(Users origen){
	bool visitados[nodos];
	bool encolados[nodos];
	for(int i = 0; i < nodos; i++){
		visitados[i] = false;
		encolados[i] = false;
	}
	queue<Users> cola;
	cola.push(origen);
	encolados[0] = true;
	
	while(!cola.empty()){
		Users nodo = cola.front();
		cola.pop();
		cout << nodo.id << " - ";
		visitados[nodo.id] = true;
		encolados[nodo.id] = false;
		vector<Users> vecinos = *(vecinosDirectos(nodo));
		for(int i = 0; i < vecinos.size(); i++){
			if(!visitados[vecinos[i].id] && !encolados[vecinos[i].id]){
				cola.push(vecinos[i]);
				encolados[vecinos[i].id] = true;
			}
		}
	}
	cout << endl;
}

void LinkedGraph::printList(){
	for(int i = 0; i < nodos; i++){
		cout << i << ": ";
		for(int j = 0; j < lista[i].size(); j++){
			cout << lista[i][j].name << " - ";
		}
		cout << endl;
	}
}
