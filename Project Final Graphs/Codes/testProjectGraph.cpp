#include <iostream>
#include <fstream>
#include <string>
#include "libs/projectGraph.hpp"

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
	int cant_nodos = 41858;
	
	MatrixGraph users_graph(cant_nodos);

    /*******************************************************/
    /*******    LECTURA DE LOS DATOS DEL ARCHIVO     *******/
    /*******************************************************/
	string university, user_id, user_name, number_tweets, friends_count, followers_count, created_at;
    long long id_key, valor_name;

    while(file.good()){
        // Lectura de archivos
        getline(file, university, ';');
        getline(file, user_id, ';');
        getline(file, user_name, ';');
        getline(file, number_tweets, ';');
        getline(file, friends_count, ';');
        getline(file, followers_count, ';');
        getline(file, created_at, '\n');

        // No se considera la primera fila
        if (university == "university") continue;

        // Se pasa el string a numero long long
        id_key = stoll(user_id, nullptr, 10);
        //cout << "Id_key: " << id_key << endl;

        valor_name = asciiNameRadix(user_name);
        //cout << "user_name: " << user_name << "valor: " << valor_name << endl;

        // Se guardan las claves para la inserción y se obtiene el rango maximo de valores para la busqueda
        vector_elem_id.push_back(id_key);
        myset_id.insert(id_key);
        if(maximo_id < id_key) maximo_id = id_key;
        if(minimo_id > id_key) minimo_id = id_key;

        vector_elem_name.push_back(valor_name);
        myset_name.insert(valor_name);
        if(maximo_name < valor_name) maximo_name = valor_name;
        if(minimo_name > valor_name) minimo_name = valor_name;
    }

    file.close();
	
	cout << "=========================" << endl;
	cout << "Inserciones: " << endl;
	cout << "=========================" << endl;
	
	while(input >> p >> q){
		if(mg.insertar(p, q)){
			cout << "Inserté el par (" << p << ", " << q << ") al MatrixGraph" << endl;
		}else{
			cout << "No pude insertar el par (" << p << ", " << q << ") al MatrixGraph" << endl;
		}
		
		if(lg.insertar(p, q)){
			cout << "Inserté el par (" << p << ", " << q << ") al LinkedGraph" << endl;
		}else{
			cout << "No pude insertar el par (" << p << ", " << q << ") al LinkedGraph" << endl;
		}
	}
	
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
	
	return 0;
}