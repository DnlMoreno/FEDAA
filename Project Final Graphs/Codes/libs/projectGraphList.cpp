#include <fstream>
#include "projectGraphList.hpp"
#define NIL -1

/************************************/
/*******    CLASE USUARIOS    *******/
/************************************/

// Usuarios seguidores inicializados (contiene a todos los usuarios excepto a los nodos sumideros)
Users::Users(int id, string name, int follower_count, int followee_count){
    this->id = id; 
	this->name = name; 
	this->follower_count = follower_count;
	this->followee_count = followee_count;

	// Información obtenida despues
    this->out_degree = NIL; // Seguidos en la red
	this->in_degree = NIL; // Seguidores en la red
	this->influencer = false; // True si el usuario es influencer

	// Tendencia politica de cada usuario obtenida del BFS
	this->tend_politica1 = 0.0; 
	this->tend_politica2 = 0.0;
	this->tend_politica3 = 0.0;
	this->tend_politica4 = 0.0;
}

// Usuarios seguidos inicializados (creado porque los follower_count y friend_count estan respecto a la columna follower)
// Columna follower contiene a todos los usuarios, excepto a los nodos sumideros
Users::Users(int id, string name){
    this->id = id; 
	this->name = name; 
	this->follower_count = NIL;
	this->followee_count = NIL;

	// Información obtenida despues
    this->out_degree = NIL; // Seguidos en la red
	this->in_degree = NIL; // Seguidores en la red
	this->influencer = false; // True si el usuario es influencer

	// Tendencia politica de cada usuario obtenida del BFS
	this->tend_politica1 = 0.0; 
	this->tend_politica2 = 0.0;
	this->tend_politica3 = 0.0;
	this->tend_politica4 = 0.0;
}

// Constructor por defecto (sirve para inicializar el vector)
Users::Users(){
    this->id = -1; 
	this->name = "JC"; 
	this->follower_count = NIL;
	this->followee_count = NIL;

	// Información obtenida despues
    this->out_degree = NIL; // Seguidos en la red
	this->in_degree = NIL; // Seguidores en la red
	this->influencer = false; // True si el usuario es influencer

	// Tendencia politica de cada usuario obtenida del BFS
	this->tend_politica1 = 0.0; 
	this->tend_politica2 = 0.0;
	this->tend_politica3 = 0.0;
	this->tend_politica4 = 0.0;
}

Users::~Users(){
}

/*********************************************************/
/*******    CLASE GRAFO CON LISTA DE ADYACENCIA    *******/
/*********************************************************/
int top_ranking = 10;
int users_influencers = 403; // 403 usuarios son los usuarios con 50 o mas seguidores
int num_tpoliticas = 4; // cantidad de tendencias politicas analizadas

// Porcentajes utilizados en la formula de tendencias
float porcentaje_dist = 0.9;
float porcentaje_inf = 0.1;

// Se utilizan para que estos vertices no aparezcan como influencers
string T1 = "Cooperativa";
string T2 = "soyvaldiviacl";
string T3 = "latercera";
string T4 = "elmostrador";

LinkedGraph::LinkedGraph(int nodos){
	this->nodos = nodos;

	lista_out = new vector<int>[nodos];
	lista_in = new vector<int>[nodos];

	users.resize(nodos);
}

LinkedGraph::~LinkedGraph(){
	delete [] lista_out;
	delete [] lista_in;
}

bool LinkedGraph::insertar(Users p, Users q){
	if(p.id >= nodos || q.id >= nodos) return false; // Fuera de rango
	for(int i = 0; i < lista_out[p.id].size(); i++){
		if(lista_out[p.id][i] == q.id) return false; // Arista ya insertada
	}
	
	// Se ingresan los usuarios a un vector que almacena a todos los usuarios
	users[p.id] = p;
	if (users[q.id].name == "JC") users[q.id] = q; // Para los 4 vertices sumideros

	// Se ingresan los usuarios a una lista de ady. que contiene los out-deegre y a otra que contiene los in-deegre
	lista_out[p.id].push_back(q.id);
	lista_in[q.id].push_back(p.id);

	return true;
}

vector<int>* LinkedGraph::vecinosDirectos(int p){
	if(p >= nodos) return NULL; // Fuera de rango
	return &(lista_out[p]);
}

void LinkedGraph::ranking(){
	// Se obtienen los out degree
	for(int i = 0; i < nodos; i++){
		if(users[i].name != T1 & users[i].name != T2 & users[i].name != T3 & users[i].name != T4){
			users[i].out_degree = lista_out[i].size();
		}
	}
	// Se obtienen los in degree
	for(int i = 0; i < nodos; i++){
		if(users[i].name != T1 & users[i].name != T2 & users[i].name != T3 & users[i].name != T4){
			users[i].in_degree = lista_in[i].size();
		}
	}

	// Se rellenan las priority queue. Una para los influencers y la otra para los influenciables
	__ranking();
}

void LinkedGraph::tendenciaPolitica(){
	// Se guardan el porcentaje de tendencias
	ofstream file;
	file.open("Tendencias_politicas_usuarios.csv", ios::out);

	file << "Usuario" << ";" << "Coorporativa" << ";" << "soyvaldiviacl" << ";" << "latercera" << ";" << "elmostrador" << endl;
	// Se recorre por cada usuario el BFSmodificado
	for(int i = num_tpoliticas; i < users.size(); i++){
		__BFSmodificado(users[i].id, file);
	}

	file.close();
}

/*
La siguiente estructura fue extraída del siguiente sitio:
https://www.programmersought.com/article/86034163763/
*/
// Esta estructura permite encontrar las componentes fuertemente conexas mediante el algoritmo de Tarjan
// metodo interno (__SCCUtil) sacado de la misma fuente.
void LinkedGraph::SCC(){ 
	// Se inicializan las estructuras a utilizar (explicadas en __SCCUtil)
    int *disc = new int[nodos]; 
    int *low = new int[nodos]; 
    bool *stackMember = new bool[nodos]; 
    stack<int> stk; 
  	int time = 0;
  	
	// Relleno de estructuras
    for (int i = 0; i < nodos; i++){ 
        disc[i] = NIL; 
        low[i] = NIL; 
        stackMember[i] = false; 
    } 

	ofstream file;
	file.open("Componentes_fuertemente_conexas.csv", ios::out);

	//file << "COMPONENTES_FUERTEMENTE_CONEXAS" << endl;

	// Se visitan todos los nodos que no han sido visitados, comenzando del nodo 0.
    for (int i = 0; i < nodos; i++){
        if (disc[i] == NIL){ 		//disc también actúa como una matriz visitada, marcando si ha sido visitado 
            __SCCUtil(i, disc, low,time, stackMember,stk, file); 
        }
    }
	file.close();

	// Liberación de memoria
	delete [] disc;
	delete [] low;
	delete [] stackMember;
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

void LinkedGraph::recorrerUsers(){
	cout << endl;
	for (unsigned i=0; i<users.size(); i++){
    	cout << users[i].name << ": Out_degree ("<< users[i].out_degree << ") and In_degree (" << users[i].in_degree << ") " ;
		cout << "follower_count (" << users[i].follower_count << ") and followee_count (" << users[i].followee_count << ") " << "influencer: " << users[i].influencer ;
		cout << " Cooperativa: " << users[i].tend_politica1 << " - soyvaldiviacl: " << users[i].tend_politica2 << " - latercera: " << users[i].tend_politica3 << endl;
	}
}

/****************** METODOS INTERNOS *****************/

void LinkedGraph::__ranking(){
	// Se guardan los top 10
	ofstream file;
	file.open("Top_10_influyentes_e_influenciables.txt", ios::out);
	file << "************** RANKING TOP 10 **************" << endl;

	// Se rellenan las priority queue
	for(unsigned i=0; i<users.size(); i++){
		Influencers.push(users[i]);
		Influenciables.push(users[i]);
	}

	file << "Influenciables" << endl;
	for(unsigned i=0; i<top_ranking; i++){
        // Se crea una variable aux que contenga el primer valor que hay en la cola de prioridad y se elimina el valor de la cola de prioridad
        Users aux = Influenciables.top(); 
        Influenciables.pop();

        // Impresion de salida
		file << i << " - Usuario: " << aux.name << "; Seguidos: "<< aux.out_degree << endl; 
	}

	file << "\nInfluyentes" << endl;
	for(unsigned i=0; i<users_influencers; i++){
        // Se crea una variable aux que contenga el primer valor que hay en la cola de prioridad y se elimina el valor de la cola de prioridad
        Users aux = Influencers.top(); 
        Influencers.pop();

		// Actualización de atributos de usuarios influencers (Servira para utilizarlo en la evaluación de las tendencias politicas)
		users[aux.id].influencer = true;

		// Impresion de salida top 10
		if(i < top_ranking) file << i << " - Usuario: " << aux.name << "; Seguidores: "<< aux.in_degree << endl; 
	}
	file.close();
}

void LinkedGraph::__BFSmodificado(int s, ofstream &file){
	// Se guarda el id del usuario analizado
	int id_usuario = s;

	// Si el vertice se encuentra en el diccionario, significa que fue visitado
	// Key = id del vertice
	// El vector guarda el padre, el orden y el numero de influencers que hay en el camino.
	unordered_map<int, vector<int>> datos;

	// Permite hacer comparaciones por nivel
	// Key = id del vertice
	// El vector guarda al padre e hijo
	unordered_map<int, vector<pair<int, int>> > nivel;

	// Se encola y se marca el vertice de origen como visitado
	queue<int> cola;
	cola.push(s);
	datos[s] = vector<int> {-1, 0, 0}; // No se considera como influencer al vertice origen, aunque lo fuera

	// Los 4 vertices sumideros no han sido visitados
	vector<bool> sumideros = {false,false,false,false};
	int max = 999999; // Guarda el ultimo orden, del ultimo nodo sumidero encontrado
	bool flag = false;

	while(!cola.empty()){
		
		// Se encola el vertice analizado
		s = cola.front();

		// Condición de termino, en caso de haber encontrado los 4 vertices sumideros
		if (sumideros[0] == true & sumideros[1] == true & sumideros[2] == true & sumideros[3] == true & max < datos.at(s)[1]) break;

		// Vertice se desencola
		cola.pop();
		//cout << s << " - ";
		
		// Se obtienen todos los vertices adyacentes de s
		vector<int> vecinos = *(vecinosDirectos(s));

		// Si no entra a este for significa que es un nodo sumidero.
		// Los nodos sumideros de la base de datos son: Cooperativa, Latercera, Soyvaldivia.cl, Elmostrador
		for(int i = 0; i < vecinos.size(); i++){
			if(datos.count(vecinos[i]) != 1){

				// Se encola el vertice
				cola.push(vecinos[i]);

				// Vertices se marcan como visitados y se le agregan los atributos
				if (users[vecinos[i]].influencer == true) datos[vecinos[i]] = vector<int> {s, datos.at(s)[1] + 1, datos.at(s)[2] + 1};
				else datos[vecinos[i]] = vector<int> {s, datos.at(s)[1] + 1, datos.at(s)[2]};

				// Se van guardando los vectices padres e hijos en su nivel correspondiente
				nivel[datos.at(s)[1] + 1].push_back(make_pair(s,vecinos[i]));

				// Permite controlar la salida del codigo
				if (vecinos[i] == 0) sumideros[0] = true;
				else if (vecinos[i] == 1) sumideros[1] = true;
				else if (vecinos[i] == 2) sumideros[2] = true;
				else if (vecinos[i] == 3) sumideros[3] = true;

				// Se guarda el ultimo orden, del ultimo nodo sumidero encontrado
				if(sumideros[0] == true & sumideros[1] == true & sumideros[2] == true & sumideros[3] == true & flag == false){
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
								if (users[vecinos[i]].influencer == true) datos[vecinos[i]] = vector<int> {s, datos.at(s)[1] + 1, datos.at(s)[2] + 1};
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
	__porcentajeTendencias(datos, id_usuario, sumideros, file);
}

void LinkedGraph::__porcentajeTendencias(unordered_map<int, vector<int>> &datos, int id_usuario, vector<bool> &sumideros, ofstream &file){

	float dist_total = 0; // La suma de todas las distancias hacia las diferentes tendencias politicas
	float inf_total = 0; // Suma de todos los influyentes hacias las diferentes tendencias politicas
	float sumatoria_tendencias; // Suma del porcentaje de tendencia no normalizado aun

	// Se suman todas las distancias e influyentes que hubieron en el camino hacia cada vertice sumidero
	for(int i = 0; i < num_tpoliticas; i++){
		if(sumideros[i] == true) dist_total += datos.at(i)[1];
		if(sumideros[i] == true) inf_total += datos.at(i)[2];
	}

	/******** Formula para calcular las tendencias politicas de los usuarios ********/
	//Cooperativa
	if(sumideros[0] == true){
		// Caso base T = 1
		if(sumideros[1] == false & sumideros[2] == false & sumideros[3] == false) users[id_usuario].tend_politica1 = 1.0;
		// Formula T > 1 y Inf_total != 0
		else if(inf_total != 0) users[id_usuario].tend_politica1 = (1 - (datos.at(0)[1]/dist_total)) * porcentaje_dist + (datos.at(0)[2]/inf_total) * porcentaje_inf;
		// Formula T > 1 y Inf_total == 0
		else users[id_usuario].tend_politica1 = (1 - (datos.at(0)[1]/dist_total)) * porcentaje_dist;
	}
	else users[id_usuario].tend_politica1 = 0.0;

	//soyvaldiviacl
	if(sumideros[1] == true){
		// Caso base T = 1
		if(sumideros[0] == false & sumideros[2] == false & sumideros[3] == false) users[id_usuario].tend_politica2 = 1.0;
		// Formula T > 1 y Inf_total != 0
		else if (inf_total != 0) users[id_usuario].tend_politica2 = (1 - (datos.at(1)[1])/dist_total) * porcentaje_dist + (datos.at(1)[2]/inf_total) * porcentaje_inf;
		// Formula T > 1 y Inf_total == 0
		else users[id_usuario].tend_politica2 = (1 - (datos.at(1)[1]/dist_total)) * porcentaje_dist;
	}
	else users[id_usuario].tend_politica2 = 0.0;

	//latercera
	if(sumideros[2] == true){
		// Caso base T = 1
		if (sumideros[0] == false & sumideros[1] == false & sumideros[3] == false) users[id_usuario].tend_politica3 = 1.0;
		// Formula T > 1 y Inf_total != 0
		else if (inf_total != 0) users[id_usuario].tend_politica3 = (1 - (datos.at(2)[1])/dist_total) * porcentaje_dist + (datos.at(2)[2]/inf_total) * porcentaje_inf;
		// Formula T > 1 y Inf_total == 0
		else users[id_usuario].tend_politica3 = (1 - (datos.at(2)[1]/dist_total)) * porcentaje_dist;
	}
	else users[id_usuario].tend_politica3 = 0.0;

	//elmostrador
	if(sumideros[3] == true){
		// Caso base T = 1
		if (sumideros[0] == false & sumideros[1] == false & sumideros[2] == false) users[id_usuario].tend_politica4 = 1.0;
		// Formula T > 1 y Inf_total != 0
		else if (inf_total != 0) users[id_usuario].tend_politica4 = (1 - (datos.at(3)[1])/dist_total) * porcentaje_dist + (datos.at(3)[2]/inf_total) * porcentaje_inf;
		// Formula T > 1 y Inf_total == 0
		else users[id_usuario].tend_politica4 = (1 - (datos.at(3)[1]/dist_total)) * porcentaje_dist;
	}
	else users[id_usuario].tend_politica4 = 0.0;

	/******** Ecuacion Tij ********/
	sumatoria_tendencias = users[id_usuario].tend_politica1 + users[id_usuario].tend_politica2 + users[id_usuario].tend_politica3 + users[id_usuario].tend_politica4;

	// Se actualizan las tendencias
	if(sumideros[0] == true) users[id_usuario].tend_politica1 = users[id_usuario].tend_politica1 / sumatoria_tendencias;
	if(sumideros[1] == true) users[id_usuario].tend_politica2 = users[id_usuario].tend_politica2 / sumatoria_tendencias;
	if(sumideros[2] == true) users[id_usuario].tend_politica3 = users[id_usuario].tend_politica3 / sumatoria_tendencias;
	if(sumideros[3] == true) users[id_usuario].tend_politica4 = users[id_usuario].tend_politica4 / sumatoria_tendencias;

	file << users[id_usuario].name << ";" << users[id_usuario].tend_politica1 << ";" << users[id_usuario].tend_politica2 << ";"  << users[id_usuario].tend_politica3 << ";"  << users[id_usuario].tend_politica4 << endl;
}

void LinkedGraph::__SCCUtil(int u, int disc[], int low[], int &time, bool stackMember[], stack<int>&stk, ofstream &file){
	// Disc almacena el orden de los vertices en el primer recorrido en profundidad
	// low almacena el orden mas pequeño de los antecesores que el nodo u pueda alcanzar
	disc[u] = low[u] = ++time;	  
	stk.push(u); // Guarda el nodo actual y sus antecesores hasta que se encuentra una componente fuertemente conexa 
	stackMember[u] = true;	// Guarda los nodos apilados
	
	// Se obtienen todos los vertices adyacentes de u
	vector<int> vecinos = *(vecinosDirectos(u));
    int v;

	for(int i = 0; i < vecinos.size(); i++){
		v = vecinos[i];
		if(disc[v] == -1){
			// Recursion hasta encontrar la componente fuertemente conexa
			__SCCUtil(v,disc,low,time,stackMember,stk, file);
			low[u] = min(low[u], low[v]); // Se guarda el de orden minimo
		}
		else if(stackMember[v] == true){		// v es el antecesor de u
			low[u] = min(low[u], disc[v]);		
		}
	}

	int w = 0;
	// Se encontro una componente fuertemente conexa
	if(low[u] == disc[u]){
			// u es la raíz del subárbol DFS donde se encuentra la componente fuertemente conexa
		while(stk.top() != u){	// Se obtiene sacan los elemetos hasta u, no toda la pila 
			w = (int) stk.top();
			file << users[w].name << ";";
			stackMember[w] = false; 
			stk.pop();
		}
		// Se desapila el ultimo valor (u)
		w = (int) stk.top();
		file << users[w].name << endl;
		stackMember[w] = false; 
		stk.pop();
	}
}	


