#include "projectGraph.hpp"

MatrixGraph::MatrixGraph(int nodos){
	this->nodos = nodos;
	matrix = new int*[nodos];
	for(int i = 0; i < nodos; i++){
		matrix[i] = new int[nodos];
		for(int j = 0; j < nodos; j++){
			matrix[i][j] = 0;
		}
	}
}

MatrixGraph::~MatrixGraph(){
	for(int i = 0; i < nodos; i++){
		delete [] matrix[i];
	}
	delete [] matrix;
}

int MatrixGraph::insertar(int p, int q){
	if(p >= nodos || q >= nodos) return 0; // no se inserto fuera de rango
	if(matrix[p][q]) return 0; // arista ya insertada
	matrix[p][q] = 1;
	return 1;
}

bool MatrixGraph::checkLink(int p, int q){
	if(p >= nodos || q >= nodos) return false; // fuera de rango
	if(matrix[p][q]) return true;	// SE encuentra el enlace
	return false;	// No se encuentra el enlace
}

vector<int> * MatrixGraph::vecinosDirectos(int p){
	if(p >= nodos) return NULL; // fuera de rango
	vector<int> * output = new vector<int>();
	for(int q = 0; q < nodos; q++){
		if(matrix[p][q]) output->push_back(q);
	}
	return output;
}

vector<int> * MatrixGraph::vecinosReversos(int q){
	if(q >= nodos) return NULL; // fuera de rango
	vector<int> * output = new vector<int>();
	for(int p = 0; p < nodos; p++){
		if(matrix[p][q]) output->push_back(p);
	}
	return output;
}

void MatrixGraph::BFS(){
	bool visitados[nodos];
	bool encolados[nodos];
	for(int i = 0; i < nodos; i++){
		visitados[i] = false;
		encolados[i] = false;
	}
	queue<int> cola;
	cola.push(0);
	encolados[0] = true;
	
	while(!cola.empty()){
		int nodo = cola.front();
		cola.pop();
		cout << nodo << " - ";
		visitados[nodo] = true;
		encolados[nodo] = false;
		vector<int> vecinos = *(vecinosDirectos(nodo));
		for(int i = 0; i < vecinos.size(); i++){
			if(!visitados[vecinos[i]] && !encolados[vecinos[i]]){
				cola.push(vecinos[i]);
				encolados[vecinos[i]] = true;
			}
		}
	}
	cout << endl;
}

void MatrixGraph::DFS(){
	bool * visitados = new bool[nodos];
	for(int i = 0; i < nodos; i++){
		visitados[i] = false;
	}
	DFS_recursivo(0, visitados);
	cout << endl;
}

void MatrixGraph::DFS_recursivo(int nodo, bool * visitados){
	cout << nodo << " - ";
	visitados[nodo] = true;
	vector<int> vecinos = *(vecinosDirectos(nodo));
	for(int i = 0; i < vecinos.size(); i++){
		if(!visitados[vecinos[i]]){
			DFS_recursivo(vecinos[i], visitados);
		}
	}
}

void MatrixGraph::printMatrix(){
	for(int i = 0; i < nodos; i++){
		for(int j = 0; j < nodos; j++){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
