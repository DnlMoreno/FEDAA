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
	this->tend_politica1 = 0.0; 
	this->tend_politica2 = 0.0;
	this->tend_politica3 = 0.0;
	this->tend_politica4 = 0.0;
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
	this->tend_politica1 = 0.0; 
	this->tend_politica2 = 0.0;
	this->tend_politica3 = 0.0;
	this->tend_politica4 = 0.0;
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
int num_tpoliticas = 3;


LinkedGraph::LinkedGraph(int nodos){
	this->nodos = nodos;

	lista_out = new vector<int>[nodos];
	lista_in = new vector<int>[nodos];

	users.resize(nodos);
}

LinkedGraph::~LinkedGraph(){
	delete [] lista_out;
}

bool LinkedGraph::insertar(Users p, Users q){
	if(p.id >= nodos || q.id >= nodos) return false; // no se inserto fuera de rango
	for(int i = 0; i < lista_out[p.id].size(); i++){
		if(lista_out[p.id][i] == q.id) return false; // arista ya insertada
	}

	//cout << "ID: (" << users[p.id].id << ") NAME: " << users[p.id].name << endl;
	
	// Se ingresan los usuarios a un vector que almacena a todos los usuarios
	users[p.id] = p;
	if (users[q.id].name == "JC") users[q.id] = q;

	//cout << "ID: (" << users[p.id].id << ") NAME: " << users[p.id].name << endl;
	
	// Se ingresan los usuarios a una lista de ady. que contiene los out-deegre y a otra que contiene los in-deegre
	lista_out[p.id].push_back(q.id);
	lista_in[q.id].push_back(p.id);

	//cout << "PARA LOS OUT-DEGREE " << p.id << ": " << p.name << endl;
	//cout << "PARA LOS IN-DEGREE " << q.id << ": " << q.name << endl;

	return true;
}

bool LinkedGraph::checkLink(Users p, Users q){
	if(p.id >= nodos || q.id >= nodos) return false; // fuera de rango
	for(int i = 0; i < lista_out[p.id].size(); i++){
		if(lista_out[p.id][i] == q.id) return true;
	}
	return false;
}

vector<int>* LinkedGraph::vecinosDirectos(int p){
	if(p >= nodos) return NULL; // fuera de rango
	return &(lista_out[p]);
}

void LinkedGraph::tendenciaPolitica(){
	for(int i = num_tpoliticas; i < users.size(); i++){
		__BFSmodificado(users[i].id);
	}
}

void LinkedGraph::__BFSmodificado(int s){
	// Si el vertice se encuentra en el diccionario, significa que fue visitado
	// Key = id del vertice
	// El vector guarda el padre, el orden y el numero de influencers que hay en el camino.
	unordered_map<int, vector<int>> datos;

	// Permite hacer comparaciones por nivel
	// Key = id del vertice
	// El vector guarda al padre e hijo.
	unordered_map<int, vector<pair<int, int>> > nivel;

	// Se encola y se marca el vertice de origen como visitado
	queue<int> cola;
	cola.push(s);
	datos[s] = vector<int> {-1, 0, 0}; // No se considera como influencer al vertice origen, aunque lo fuera

	// Los 4 vertices sumideros no han sido visitados
	vector<bool> v = {false,false,false,false};
	vector<bool> prueba = {false,false,false};
	int max = 999999; // Guarda el ultimo orden, del ultimo nodo sumidero encontrado
	bool flag = false;

	while(!cola.empty()){
		
		s = cola.front();

		// Condición de termino, en caso de haber encontrado los 4 vertices sumideros
		if (prueba[0] == true & prueba[1] == true & prueba[2] == true & max < datos.at(s)[1]) break;

		// Se imprime el primero en la cola y se desencola
		cout << s << " - ";
		cola.pop();
		
		// Se obtienen todos los vertices adyacentes de s
		vector<int> vecinos = *(vecinosDirectos(s));

		// Si no entra a este for significa que es un nodo sumidero.
		// Los nodos sumideros de la base de datos son: Cooperativa, Latercera, Soyvaldivia.cl, Elmostrador
		for(int i = 0; i < vecinos.size(); i++){
			if(datos.count(vecinos[i]) != 1){

				// Se encola el vertice
				cola.push(vecinos[i]);

				// Vertices se marcan como visitados y se le agregan los atributos
				if (users[vecinos[i]].influencer = true) datos[vecinos[i]] = vector<int> {s, datos.at(s)[1] + 1, datos.at(s)[2] + 1};
				else datos[vecinos[i]] = vector<int> {s, datos.at(s)[1] + 1, datos.at(s)[2]};

				// Se van guardando los vectices padres e hijos en su nivel correspondiente
				nivel[datos.at(s)[1] + 1].push_back(make_pair(s,vecinos[i]));

				// Permite controlar la salida del codigo
				if (vecinos[i] == 0) prueba[0] = true;
				else if (vecinos[i] == 1) prueba[1] = true;
				else if (vecinos[i] == 2) prueba[2] = true;
				//else if (vecinos[i] == 3) v[3] = true;

				// Se guarda el ultimo orden, del ultimo nodo sumidero encontrado
				if(prueba[0] == true & prueba[1] == true & prueba[2] == true & flag == false){
					max = datos.at(s)[1] + 1;
					flag = true;
				}
			}

			// Se considera el camino con mayor influencers en caso de que dos vertices con mismo orden lleguen al siguiente vertice
			else{
				// Se ingresa al nivel iterado
				for(auto& elem: nivel.at(datos.at(s)[1])){

					// Se busca al vertice que ya tenia padre
					if(elem.second == vecinos[i]){

						// Se ingresa al padre anterior y se compara el orden con el padre actual
						if (datos.at(elem.first)[1] == datos.at(s)[1]){

							// Se compara la cantidad de seguidores entre los padres del vertice iterado
							if (datos.at(elem.first)[2] < datos.at(s)[2]){

								// Como ingreso al if, el usuario debe ser influencer
								// Se actualizan los valores del padre hacia el vertice iterado
								if (users[vecinos[i]].influencer = true) datos[vecinos[i]] = vector<int> {s, datos.at(s)[1] + 1, datos.at(s)[2] + 1};
								else datos[vecinos[i]] = vector<int> {s, datos.at(s)[1] + 1, datos.at(s)[2]};
								elem.first = s;
							}
							break;
						}
						break;
					}
				}
			}
		}
	}
	//__porcentajeTendencias(datos);
	cout << endl;
}

void LinkedGraph::printListOut(){
	for(int i = 0; i < nodos; i++){
		cout << users[i].name << ": ";
		for(int j = 0; j < lista_out[i].size(); j++){
			cout << lista_out[i][j] << " - ";
		}
		cout << endl;
	}
}

void LinkedGraph::printListIn(){
	for(int i = 0; i < nodos; i++){
		cout << users[i].name << ": ";
		for(int j = 0; j < lista_in[i].size(); j++){
			cout << lista_in[i][j] << " - ";
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