#include "ProjectGraphList.hpp"

/************************************/
/*******    CLASE USUARIOS    *******/
/************************************/

// Usuarios inicializados
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

/*********************************************************/
/*******    CLASE GRAFO CON LISTA DE ADYACENCIA    *******/
/*********************************************************/

LinkedGraph::LinkedGraph(int nodos){
	this->nodos = nodos;

	lista_out = new vector<Users>[nodos];
	lista_in = new vector<Users>[nodos];

	users.reserve(nodos);
}

LinkedGraph::~LinkedGraph(){
	delete [] lista_out;
}

bool LinkedGraph::insertar(Users p, Users q){
	if(p.id >= nodos || q.id >= nodos) return false; // no se inserto fuera de rango
	for(int i = 0; i < lista_out[p.id].size(); i++){
		if(lista_out[p.id][i].id == q.id) return false; // arista ya insertada
	}

	// Se ingresan los usuarios a un vector que almacena a todos los usuarios
	users[p.id] = p;
	users[q.id] = q;

	// Se ingresan los usuarios a una lista de ady. que contiene los out-deegre y a otra que contiene los in-deegre
	lista_out[p.id].push_back(q);
	lista_in[q.id].push_back(p);

	//cout << "PARA LOS OUT-DEGREE " << p.id << ": " << p.name << endl;
	//cout << "PARA LOS IN-DEGREE " << q.id << ": " << q.name << endl;

	return true;
}

bool LinkedGraph::checkLink(Users p, Users q){
	if(p.id >= nodos || q.id >= nodos) return false; // fuera de rango
	for(int i = 0; i < lista_out[p.id].size(); i++){
		if(lista_out[p.id][i].id == q.id) return true;
	}
	return false;
}

vector<Users>* LinkedGraph::vecinosDirectos(Users p){
	if(p.id >= nodos) return NULL; // fuera de rango
	return &(lista_out[p.id]);
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

void LinkedGraph::printListOut(){
	for(int i = 0; i < nodos; i++){
		cout << i << ".- " << users[i].name << ": ";
		for(int j = 0; j < lista_out[i].size(); j++){
			cout << lista_out[i][j].name << " - ";
		}
		cout << endl;
	}
}

void LinkedGraph::printListIn(){
	for(int i = 0; i < nodos; i++){
		cout << i << ".- " << users[i].name << ": ";
		for(int j = 0; j < lista_in[i].size(); j++){
			cout << lista_in[i][j].name << " - ";
		}
		cout << endl;
	}
}