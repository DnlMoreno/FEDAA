#include <iostream>
#include <fstream>
#include <string>
#include "libs/projectGraphMatrix.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 2){
        cout << "ERROR!! USE " << argv[0] << " <FILENAME> donde:\n"
            <<"<FILENAME> nombre del archivo a leer \n";
        return -1;
    }
    char* filename = argv[1];	
    ifstream file;

    file.open(filename);
    if(!file.is_open()){
        cout << "ERROR!!! el archivo " << filename << " no se pudo abrir\n";
        return -1;
    }
	
    // Cantidad de nodos
	int cant_nodos = 11;
	
	MatrixGraph users_graph(cant_nodos);

    /*******************************************************/
    /*******    LECTURA DE LOS DATOS DEL ARCHIVO     *******/
    /*******************************************************/
	int id_follower, id_followee;
	string follower, followee, temp_follower, temp_followee;

    while(file.good()){
        // Lectura de archivos
        getline(file, followee, ';');
        getline(file, follower, ';');
		getline(file, temp_followee, ';');
        getline(file, temp_follower, '\n');

		cout << "FOLLOWEE1: "<< followee << endl;
		cout << "FOLLOWER1: "<< follower << endl;

        // No se considera la primera fila
        if (follower == "follower") continue;

        // Se pasa el string a numero int
        id_follower = atoi(temp_follower.c_str());
		id_followee = atoi(temp_followee.c_str());
        //cout << "Id_follower: " << id_follower << endl;
		//cout << "Id_followee: " << id_followee << endl;

		//users_graph.insertar(id_follower, id_followee);

		//Se insertar los usuarios y se crean los enlances en el grafo

		if(users_graph.insertar(id_follower, id_followee) == 1){
			cout << "Se inserto el par (" << id_follower << ", " << id_followee << ") al MatrixGraph" << endl;
		}else{
			cout << "No se pudo insertar el par ommggggggggggggggggggggggggHHHHHHHHHHHHHHHHHHHHHHHHH (" << id_follower << ", " << id_followee << ") al MatrixGraph" << endl;
		}
		cout << "FOLLOWEE2: "<< followee << endl;
		cout << "FOLLOWER2: "<< follower << endl;
    }
    file.close();

	users_graph.printMatrix();

/*	
	cout << "=========================" << endl;
	cout << "Matriz de adyacencia: " << endl;
	cout << "=========================" << endl;
	mg.printMatrix();
	
	cout << "=========================" << endl;
	cout << "Lista de adyacencia " << endl;
	cout << "=========================" << endl;
	lg.printList();
	
	cout << "=========================" << endl;
	cout << "Chequeo de enlaces: " << endl;
	cout << "=========================" << endl;
	cout << "Matriz de adyacencia: " << endl;
	cout << "=========================" << endl;
	
	for(int i = 0; i < nodos; i++){
		for(int j = 0; j < nodos; j++){
			if(mg.checkLink(i,j)){
				cout << "Encontré el par (" << i << ", " << j << ")" << endl;
			}
		}
	}
	
	cout << "=========================" << endl;
	cout << "Lista de adyacencia " << endl;
	cout << "=========================" << endl;
	
	for(int i = 0; i < nodos; i++){
		for(int j = 0; j < nodos; j++){
			if(lg.checkLink(i,j)){
				cout << "Encontré el par (" << i << ", " << j << ")" << endl;
			}
		}
	}
	
	cout << "=========================" << endl;
	cout << "Vecinos directos: " << endl;
	cout << "=========================" << endl;
	cout << "Matriz de adyacencia: " << endl;
	cout << "=========================" << endl;
	
	vector<int> v;
	
	for(int i = 0; i < nodos; i++){
		cout << "Vecino de " << i << ": ";
		v = *(mg.vecinosDirectos(i));
		for(int j = 0; j < v.size(); j++){
			cout << v[j] << " - ";
		}
		cout << endl;
	}
	
	cout << "=========================" << endl;
	cout << "Lista de adyacencia " << endl;
	cout << "=========================" << endl;
	
	for(int i = 0; i < nodos; i++){
		cout << "Vecino de " << i << ": ";
		v = *(lg.vecinosDirectos(i));
		for(int j = 0; j < v.size(); j++){
			cout << v[j] << " - ";
		}
		cout << endl;
	}
	
	cout << "=========================" << endl;
	cout << "Vecinos reversos: " << endl;
	cout << "=========================" << endl;
	cout << "Matriz de adyacencia: " << endl;
	cout << "=========================" << endl;
	
	for(int i = 0; i < nodos; i++){
		cout << "Reverso de " << i << ": ";
		v = *(mg.vecinosReversos(i));
		for(int j = 0; j < v.size(); j++){
			cout << v[j] << " - ";
		}
		cout << endl;
	}
	
	cout << "=========================" << endl;
	cout << "Lista de adyacencia " << endl;
	cout << "=========================" << endl;
	
	for(int i = 0; i < nodos; i++){
		cout << "Reverso de " << i << ": ";
		v = *(lg.vecinosReversos(i));
		for(int j = 0; j < v.size(); j++){
			cout << v[j] << " - ";
		}
		cout << endl;
	}
	
	
	cout << "=========================" << endl;
	cout << "BFS : (Breadth First Search)" << endl;
	cout << "=========================" << endl;
	cout << "=========================" << endl;
	cout << "Matriz de adyacencia: " << endl;
	cout << "=========================" << endl;
	mg.BFS();
	
	cout << "=========================" << endl;
	cout << "Lista de adyacencia " << endl;
	cout << "=========================" << endl;
	lg.BFS();
	
	cout << "=========================" << endl;
	cout << "DFS (Depth First Search) : " << endl;
	cout << "=========================" << endl;
	cout << "=========================" << endl;
	cout << "Matriz de adyacencia: " << endl;
	cout << "=========================" << endl;
	mg.DFS();
	
	cout << "=========================" << endl;
	cout << "Lista de adyacencia " << endl;
	cout << "=========================" << endl;
	lg.DFS();
*/
	return 0;
}