#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class MatrixGraph{
public:
	MatrixGraph(int nodos);
	~MatrixGraph();
	bool insertar(int p, int q);
	bool checkLink(int p, int q);
	vector<int> * vecinosDirectos(int p);
	vector<int> * vecinosReversos(int q);
	void BFS();
	void DFS();
	
	void printMatrix();
private:
	bool ** matrix;
	int nodos;
	void DFS_recursivo(int nodo, bool * visitados);
};

#endif