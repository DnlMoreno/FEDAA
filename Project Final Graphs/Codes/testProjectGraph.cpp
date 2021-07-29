#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "libs/projectGraphList.hpp"

// Para medir el tiempo
auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();

int cant_nodos = 41858;

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
		
	// Lista de adyacencia out-degree e in-degree
	LinkedGraph users(cant_nodos);

    /*******************************************************/
    /*******    LECTURA DE LOS DATOS DEL ARCHIVO     *******/
    /*******************************************************/
	int id_follower, id_followee, followee_count, follower_count;
	string follower, followee, temp_follower, temp_followee, aux_follower, aux_followee;

    while(file.good()){
        // Lectura de archivos
        getline(file, followee, ';');
        getline(file, follower, ';');
		getline(file, temp_followee, ';');
        getline(file, temp_follower, ';');
        getline(file, aux_followee, ';');
        getline(file, aux_follower, '\n');

        // No se considera la primera fila
        if (follower == "follower") continue;

        // Se pasa el string a numero int
        id_follower = atoi(temp_follower.c_str());
		id_followee = atoi(temp_followee.c_str());
        follower_count = atoi(aux_follower.c_str());
        followee_count = atoi(aux_followee.c_str());
 
        // Seguidor y seguido
		Users user_p(id_follower, follower, follower_count, followee_count);
		Users user_q(id_followee, followee);

		//Se insertan los usuarios y se crean los enlances en el grafo
		users.insertar(user_p, user_q);

    }
    file.close();

    // Tamaño estructura general
    cout << "Tamanio Grafo: " << sizeof(users) + 2*(sizeof(vector<int>) * users.getCantidad()) + sizeof(vector<Users>) * users.getCantidad() << " bytes" << endl;

    // Tamaño estructuras auxiliares ranking top 10
    cout << "Tamanio Priority queue: " << sizeof(priority_queue<Users, vector<Users>, CompareIn>) * users.getCantidad() << " bytes" << endl;

    // Tamaño estructuras auxiliares tendencia politica
    cout << "Tamanio BFSmodificado: " << (sizeof(unordered_map<int, vector<int>>) + sizeof(unordered_map<int, vector<pair<int, int>> >) + sizeof(queue<int>)) * users.getCantidad() << " bytes" << endl;

    // Tamaño estructuras auxiliares componentes fuertemente conexa
    cout << "Tamanio SCC: " << 2*(sizeof(int*) + sizeof(int) * users.getCantidad()) + sizeof(bool*) + sizeof(bool) * users.getCantidad() + sizeof(stack<int>) * users.getCantidad() << " bytes" << endl;
 
    // Ranking top 10: Influenciables e influencers
    int tiempo_ranking; 
	start = chrono::high_resolution_clock::now();
    users.ranking();
	finish = chrono::high_resolution_clock::now();
	tiempo_ranking = chrono::duration_cast<chrono::microseconds> (finish - start).count();

    cout << "\nTiempo top 10 ranking: " << tiempo_ranking << " microseg" << endl;

    // Porcentaje de tendencias politicas de cada usuario
    int tiempo_tendencias; 
	start = chrono::high_resolution_clock::now();
    users.tendenciaPolitica();
	finish = chrono::high_resolution_clock::now();
	tiempo_tendencias = chrono::duration_cast<chrono::microseconds> (finish - start).count();

    cout << "\nTiempo tendencias politicas: " << tiempo_tendencias << " microseg" <<  endl;

    // Componentes fuertemente conexas en grafo
    int tiempo_scc; 
	start = chrono::high_resolution_clock::now();
    users.SCC(); 
	finish = chrono::high_resolution_clock::now();
	tiempo_scc = chrono::duration_cast<chrono::microseconds> (finish - start).count();

    cout << "\nTiempo componentes fuertemente conexas: " << tiempo_scc << " microseg" << endl;

    /*********** Calcula un tiempo promedio de las operaciones (30 replicas) **************/

/*
    int tiempo_ranking_ac = 0, tiempo_tendencias_ac = 0, tiempo_scc_ac = 0; 
    int tpo_prom_ranking, tpo_prom_tendencias, tpo_prom_scc;
    for (int i = 0; i<30; i++){ 

        // Ranking top 10: Influenciables e influencers
        start = chrono::high_resolution_clock::now();
        users.ranking();
        finish = chrono::high_resolution_clock::now();
        tiempo_ranking_ac += chrono::duration_cast<chrono::microseconds> (finish - start).count();      

        // Porcentaje de tendencias politicas de cada usuario
        start = chrono::high_resolution_clock::now();
        users.tendenciaPolitica();
        finish = chrono::high_resolution_clock::now();
        tiempo_tendencias_ac += chrono::duration_cast<chrono::microseconds> (finish - start).count();

        // Componentes fuertemente conexas en grafo
        start = chrono::high_resolution_clock::now();
        users.SCC(); 
        finish = chrono::high_resolution_clock::now();
        tiempo_scc_ac += chrono::duration_cast<chrono::microseconds> (finish - start).count();        
    }
    
    tpo_prom_ranking = tiempo_ranking_ac/30;
    tpo_prom_tendencias = tiempo_tendencias_ac/30;
    tpo_prom_scc = tiempo_scc_ac/30;

    cout << "\nTiempo promedio top 10 ranking: " << tpo_prom_ranking << " microseg" << endl;
    cout << "\nTiempo promedio tendencias politicas: " << tpo_prom_tendencias << " microseg" <<  endl;
    cout << "\nTiempo promedio componentes fuertemente conexas: " << tpo_prom_scc << " microseg" << endl;
*/

	return 0;
}