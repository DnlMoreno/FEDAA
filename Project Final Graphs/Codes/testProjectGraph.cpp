#include <iostream>
#include <fstream>
#include <string>
#include "libs/projectGraphMatrix.hpp"
#include "libs/ProjectGraphList.hpp"
/*
// Los usuarios se crean en base a esta estructura
struct Users{
    int id;
    int name;
    int followee; // Seguidos
	int follower; // Seguidores
	bool influencer; // True si el usuario es influencer
	int num_influencers; // Cantidad de influencers en el 

    // Inicializo las variables de la estructura
    Users(int id, int name, int followee, int follower, bool influencer, int num_influencers) 
		: id(id), name(name), followee(0), follower(0), influencer(false), num_influencers(0) 
	{	
	}
};
*/

// Cantidad de nodos
int cant_nodos = 11;

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
	LinkedGraph users_out(cant_nodos);
	LinkedGraph users_in(cant_nodos);

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

        // No se considera la primera fila
        if (follower == "follower") continue;

        // Se pasa el string a numero int
        id_follower = atoi(temp_follower.c_str());
		id_followee = atoi(temp_followee.c_str());
 
		Users user_p(id_follower, follower);
		Users user_q(id_followee, followee);

		//Se insertan los usuarios y se crean los enlances en el grafo
		users_out.insertar(user_p, user_q);

    }
    file.close();

	cout << "Out degree: " << endl;
	users_out.printListOut();

	cout << endl; 
	cout << "In degree: " << endl;
	users_out.printListIn();

	return 0;
}