#include <iostream>
#include <fstream>
#include <string>
#include "libs/projectGraphList.hpp"

// Cantidad de nodos
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

    // Ranking top 10: Influenciables e influencers
    users.ranking();

    // Porcentaje de tendencias politicas de cada usuario
    users.tendenciaPolitica();

    // Componentes fuertemente conexas en grafo
    users.SCC(); 

	return 0;
}