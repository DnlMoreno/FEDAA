#include "ProjectGraphList.hpp"

/************************************/
/*******    CLASE USUARIOS    *******/
/************************************/

// Usuarios seguidores inicializados
Users::Users(int id, string name, int follower_count, int followee_count){
    this->id = id; 
	this->name = name; 
	this->follower_count = follower_count;
	this->followee_count = followee_count;

	// Información obtenida despues
    this->out_degree = -1; // Seguidos en la red
	this->in_degree = -1; // Seguidores en la red
	this->influencer = false; // True si el usuario es influencer

	// Tendencia politica de cada usuario obtenida del BFS
	this->tend_politica1 = 0; 
	this->tend_politica2 = 0;
	this->tend_politica3 = 0;
	this->tend_politica4 = 0;
}

// Usuarios seguidos inicializados
Users::Users(int id, string name){
    this->id = id; 
	this->name = name; 
	this->follower_count = -1;
	this->followee_count = -1;

	// Información obtenida despues
    this->out_degree = -1; // Seguidos en la red
	this->in_degree = -1; // Seguidores en la red
	this->influencer = false; // True si el usuario es influencer

	// Tendencia politica de cada usuario obtenida del BFS
	this->tend_politica1 = 0; 
	this->tend_politica2 = 0;
	this->tend_politica3 = 0;
	this->tend_politica4 = 0;
}

// Constructor por defecto
Users::Users(){
    this->id = -1; 
	this->name = "JC"; 
}

Users::~Users(){
}

/*********************************************************/
/*******    CLASE GRAFO CON LISTA DE ADYACENCIA    *******/
/*********************************************************/
int top_ranking = 5;


LinkedGraph::LinkedGraph(int nodos){
	this->nodos = nodos;

	lista_out = new vector<Users>[nodos];
	lista_in = new vector<Users>[nodos];

	users.resize(nodos);
}

LinkedGraph::~LinkedGraph(){
	delete [] lista_out;
}

bool LinkedGraph::insertar(Users p, Users q){
	if(p.id >= nodos || q.id >= nodos) return false; // no se inserto fuera de rango
	for(int i = 0; i < lista_out[p.id].size(); i++){
		if(lista_out[p.id][i].id == q.id) return false; // arista ya insertada
	}

	//cout << "ID: (" << users[p.id].id << ") NAME: " << users[p.id].name << endl;
	
	// Se ingresan los usuarios a un vector que almacena a todos los usuarios
	users[p.id] = p;
	if (users[q.id].name == "JC") users[q.id] = q;

	//cout << "ID: (" << users[p.id].id << ") NAME: " << users[p.id].name << endl;
	
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
	int num_influencers[nodos];
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
		cout << users[i].name << ": ";
		for(int j = 0; j < lista_out[i].size(); j++){
			cout << lista_out[i][j].name << " - ";
		}
		cout << endl;
	}
}

void LinkedGraph::printListIn(){
	for(int i = 0; i < nodos; i++){
		cout << users[i].name << ": ";
		for(int j = 0; j < lista_in[i].size(); j++){
			cout << lista_in[i][j].name << " - ";
		}
		cout << endl;
	}
}

string T1 = "Elmostrador";
string T2 = "Latercera";
string T3 = "Cooperativa";

void LinkedGraph::ranking(){
	// Obitene los out degree
	for(int i = 0; i < nodos; i++){
		if(users[i].name != T1 & users[i].name != T2 & users[i].name != T3){
			users[i].out_degree = lista_out[i].size();
		}
	}
	// Obitene los in degree
	for(int i = 0; i < nodos; i++){
		if(users[i].name != T1 & users[i].name != T2 & users[i].name != T3){
			users[i].in_degree = lista_in[i].size();
		}
	}

	// Se crean dos heap, uno para los influencers y el otro para los influenciables
	__ranking();
}


void LinkedGraph::__ranking(){
/*
	for(unsigned i=0; i<users.size(); i++){
		heapify[i] = users[i];
	}
*/
	for(unsigned i=0; i<users.size(); i++){
		Influencers.push(users[i]);
		Influenciables.push(users[i]);
	}

	cout << "Influenciables" << endl;
	for(unsigned i=0; i<top_ranking; i++){
        // Se crea una variable aux que contenga el primer valor que hay en la cola de prioridad y se elimina el valor de la cola de prioridad
        Users aux = Influenciables.top(); 
        Influenciables.pop();

        // Impresion de salida
		cout << aux.name << "("<< aux.out_degree << ") --- " ; 
	}

	cout << endl;
	cout << "Influencers" << endl;
	for(unsigned i=0; i<top_ranking; i++){
        // Se crea una variable aux que contenga el primer valor que hay en la cola de prioridad y se elimina el valor de la cola de prioridad
        Users aux = Influencers.top(); 
        Influencers.pop();

        // Impresion de salida
		cout << aux.name << "("<< aux.in_degree << ") --- " ; 
	}
/*
	cout << "Influenciables" << endl;
	make_heap(heapify.begin(), heapify.end(), CompareOut());
	for(unsigned i=0; i<top_ranking; i++){
		auto top = heapify.back();
		heapify.pop_back();
		cout << top.name << "("<< top.out_degree << ") --- " ; 
	}
	cout << endl;
	cout << "Influencers" << endl;
	make_heap(heapify.begin(), heapify.end(), CompareIn());
	for(unsigned i=0; i<top_ranking; i++){
		auto top = heapify.back();
		heapify.pop_back();
		cout << top.name << "("<< top.in_degree << ") --- " ; 
	}
	*/
}


void LinkedGraph::recorrerUsers(){
	cout << endl;
	for (unsigned i=0; i<users.size(); i++){
    	cout << users[i].name << ": Out_degree ("<< users[i].out_degree << ") and In_degree (" << users[i].in_degree << ")" ;
		cout << "follower_count (" << users[i].follower_count << ") and followee_count (" << users[i].followee_count << ")" << endl;
	}
}

/*
// Estructuras de comparacion para la cola de prioridad
// En primer lugar, se prioriza el mayor out_degree y en caso de empate, se prioriza el mayor num. de seguidos de la red real
bool Compare::comparatorOut(Users const& p1, Users const& p2){
	if (p1.out_degree > p2.out_degree) return false; 
	else if (p1.out_degree < p2.out_degree) return true;
	else{ 
		if (p1.followee_count > p2.followee_count) return false;
		else if (p1.followee_count < p2.followee_count) return true;
	}
}


// En primer lugar, se prioriza el mayor in_degree y en caso de empate, se prioriza el mayor num. de seguidores de la red real
bool Compare::comparatorIn(Users const& p1, Users const& p2){
	if (p1.in_degree > p2.in_degree) return false;
	else if (p1.in_degree < p2.in_degree) return true;
	else{ 
		if (p1.follower_count > p2.follower_count) return false;
		else if (p1.follower_count < p2.follower_count) return true;
	}
}*/