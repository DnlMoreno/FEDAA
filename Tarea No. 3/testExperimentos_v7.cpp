#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include "libs/hashingAbierto.hpp"
#include "libs/hashingCerrado.hpp"
#include "libs/arbolBinarioBusqueda.hpp"

using namespace std;

void evaluationInsertArbol(ArbolBinarioBusqueda &arbol, double &tiempo, int contador, long long key, double** tpoArbol, int tElem[], int i);
void evaluationInsertHashingClosed(HashingClosed &hash, double &tiempo, int contador, long long key, double** tpoHash, int tElem[], int i);
void evaluationInsertHashingOpen(HashingOpen &hash, double &tiempo, int contador, long long key, double** tpoHash, int tElem[], int i);
void evaluationInsertUnorderedSetSTL(unordered_set<long long> &unSet, double &tiempo, int contador, long long key, double** tpoUnSet, int tElem[], int i);
void evaluationInsertSetSTL(set<long long> &set, double &tiempo, int contador, long long key, double** tpoSet, int tElem[], int i);
void impresionInsert(int tElem[], double** tpoArbol_id, double** tpoHashCerrado_id, double** tpoHashAbierto_id, double** tpoUnorderedSet_id, double** tpoSet_id, double** tpoArbol_name, double** tpoHashCerrado_name, double** tpoHashAbierto_name, double** tpoUnorderedSet_name, double** tpoSet_name);

void evaluationSearchArbol(ArbolBinarioBusqueda &arbol, long long elemento, double tpoArbol[], int i);
void evaluationSearchHashingClosed(HashingClosed &hash, long long elemento, double tpoHash[], int i);
void evaluationSearchHashingOpen(HashingOpen &hash, long long elemento, double tpoHash[], int i);
void evaluationSearchUnorderedSet(unordered_set<long long> &unSet, long long elemento, double tpoUnSet[], int i);
void evaluationSearchSet(set<long long> &set, long long elemento, double tpoSet[], int i);

long long asciiName(string name_user);
double** createMatrix(int n, int m);
void eliminarMatriz(double** &matriz, int num_filas);

auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();
int replicas = 10;

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

    // Cantidad de datos en la data
	int cantidad = 26101;
	long long maximo_id = 0;
	long long minimo_id = 999999999999999999;

	long long maximo_name = 0;
	long long minimo_name = 999999999999999999;

    // Guardan los elementos para la evaluacion experimental de buscar
	vector<long long> vector_elem_id;
    vector<long long> vector_elem_name;

    // Guardan los elementos que no existen
	vector<long long> vector_others_v1_id;
	vector<long long> vector_others_v2_id;
	vector<long long> vector_others_v1_name;
	vector<long long> vector_others_v2_name;

    // Guarda los elementos para consultas sobre los datos que se encuentran. Permite crear los vectores con claves que no existen
	unordered_set<long long> myset_id;
    unordered_set<long long> myset_name;

    // Intervalo de tiempo entre cada tamanio e instancia
    double **tpoArbol_id = createMatrix(9,replicas);
    double **tpoArbol_name = createMatrix(9,replicas);
    double **tpoHashCerrado_id = createMatrix(9,replicas);
    double **tpoHashCerrado_name = createMatrix(9,replicas);
    double **tpoHashAbierto_id = createMatrix(9,replicas);
    double **tpoHashAbierto_name = createMatrix(9,replicas);
    double **tpoUnorderedSet_id = createMatrix(9,replicas);
    double **tpoUnorderedSet_name = createMatrix(9,replicas);
    double **tpoSet_id = createMatrix(9,replicas);
    double **tpoSet_name = createMatrix(9,replicas);

	int tElem[] = {100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600}; // Tamanios de evaluacion

    // Estructuras de datos
 	ArbolBinarioBusqueda arbol_id;
	ArbolBinarioBusqueda arbol_name;
	HashingClosed hashCerrado_id(cantidad);
	HashingClosed hashCerrado_name(cantidad);
	HashingOpen hashAbierto_id(cantidad);
	HashingOpen hashAbierto_name(cantidad);
    unordered_set<long long> unSet_id;
    unordered_set<long long> unSet_name;
    set<long long> set_id;   
    set<long long> set_name; 

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

        valor_name = asciiName(user_name);
        //cout << "user_name: " << user_name << endl;

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

    /****************************************************************/
    /*******    EVALUACIÓN EXPERIMENTAL DE INSERCIÓN TDAs     *******/
    /****************************************************************/

    // Se realizan 30 replicas
    for(int i = 0; i < replicas; i++){
        //cout << "LA PUTA: " << i << endl;
        // Contadores de tiempos globales de inserción
        double time_arbol_id = 0.0;
        double time_arbol_name = 0.0;
        double time_hcerrado_id = 0.0;
        double time_hcerrado_name = 0.0;
        double time_habierto_id = 0.0;
        double time_habierto_name = 0.0;
        double time_unset_id = 0.0;
        double time_unset_name = 0.0;
        double time_set_id = 0.0;
        double time_set_name = 0.0;

        for(int j=0; j<vector_elem_id.size()-1; j++){
            /****************** ARBOL ******************/
            // Inserción de la la clave "user_id"
            evaluationInsertArbol(arbol_id, time_arbol_id, j, vector_elem_id[j], tpoArbol_id, tElem, i);

            // Inserción de la la clave "user_name"
            evaluationInsertArbol(arbol_name, time_arbol_name, j, vector_elem_name[j], tpoArbol_name, tElem, i);
            
            /****************** TABLA HASH CON HASHING CERRADO ******************/
            // Inserción de la la clave "user_id"
            evaluationInsertHashingClosed(hashCerrado_id, time_hcerrado_id, j, vector_elem_id[j], tpoHashCerrado_id, tElem, i);

            // Inserción de la la clave "user_name"
            evaluationInsertHashingClosed(hashCerrado_name, time_hcerrado_name, j, vector_elem_name[j], tpoHashCerrado_name, tElem, i);

            /****************** TABLA HASH CON HASHING ABIERTO ******************/
            // Inserción de la la clave "user_id"
            evaluationInsertHashingOpen(hashAbierto_id, time_habierto_id, j, vector_elem_id[j], tpoHashAbierto_id, tElem, i);

            // Inserción de la la clave "user_name
            evaluationInsertHashingOpen(hashAbierto_name, time_habierto_name, j, vector_elem_name[j], tpoHashAbierto_name, tElem, i);

            /****************** UNORDERED_SET STL ******************/
            // Inserción de la la clave "user_id"
            evaluationInsertUnorderedSetSTL(unSet_id, time_unset_id, j, vector_elem_id[j], tpoUnorderedSet_id, tElem, i);

            // Inserción de la la clave "user_name
            evaluationInsertUnorderedSetSTL(unSet_name, time_unset_name, j, vector_elem_name[j], tpoUnorderedSet_name, tElem, i);

            /****************** SET STL ******************/
            // Inserción de la la clave "user_id"
            evaluationInsertSetSTL(set_id, time_set_id, j, vector_elem_id[j], tpoSet_id, tElem, i);

            // Inserción de la la clave "user_name
            evaluationInsertSetSTL(set_name, time_set_name, j, vector_elem_name[j], tpoSet_name, tElem, i);
        }
    }

    // Impresiones de los tiempos de inserción de cada estructura
    impresionInsert(tElem, tpoArbol_id, tpoHashCerrado_id, tpoHashAbierto_id, tpoUnorderedSet_id, tpoSet_id, tpoArbol_name, tpoHashCerrado_name, tpoHashAbierto_name, tpoUnorderedSet_name, tpoSet_name);

    // Eliminación de la matrices de tiempo
    eliminarMatriz(tpoArbol_id, 9);
    eliminarMatriz(tpoHashCerrado_id, 9);
    eliminarMatriz(tpoHashAbierto_id, 9);
    eliminarMatriz(tpoUnorderedSet_id, 9);
    eliminarMatriz(tpoSet_id, 9);

    eliminarMatriz(tpoArbol_name, 9);
    eliminarMatriz(tpoHashCerrado_name, 9);
    eliminarMatriz(tpoHashAbierto_name, 9);
    eliminarMatriz(tpoUnorderedSet_name, 9);
    eliminarMatriz(tpoSet_name, 9);

	/***********************************************************************************/
	/*******    SE CREA VECTOR CON ELEMENTOS QUE NO SE ENCUENTRAN EN LA DATA     *******/
	/***********************************************************************************/
    
    /***************** Vectores con claves "User_Id" ******************/
	long long temp;
	while(vector_elem_id.size() != vector_others_v1_id.size()){
		temp = vector_elem_id[(long long)rand() % cantidad] + (long long)rand();
		if(myset_id.count(temp)==0){
			vector_others_v1_id.push_back(temp);
		}
	}

	while(vector_elem_id.size() != vector_others_v2_id.size()){
		temp = minimo_id + (long long)rand() % maximo_id;
		if(myset_id.count(temp)==0){
			vector_others_v2_id.push_back(temp);
		}
	}

    /***************** Vectores con claves "User_Name" ******************/

	while(vector_elem_name.size() != vector_others_v1_name.size()){
		temp = vector_elem_name[(long long)rand() % cantidad] + (long long)rand();
		if(myset_name.count(temp)==0){
			vector_others_v1_name.push_back(temp);
		}
	}

	while(vector_elem_name.size() != vector_others_v2_name.size()){
		temp = minimo_name + (long long)rand() % maximo_name;
		if(myset_name.count(temp)==0){
			vector_others_v2_name.push_back(temp);
		}
	}

    /***************************************************************/
    /*******    EVALUACIÓN EXPERIMENTAL DE BUSQUEDA TDAs     *******/
    /***************************************************************/
    //int n = 1000; // Promedio de busquedas
    
    int n[] = {1000, 2000, 5000, 10000, 15000, 20000, 26000}; // Promedio de busquedas

	srand(time(NULL));
	long long elemento; // Elemento a buscar

	// Busqueda de valores
    for(int i = 0; i < 7; i++){
        // Tiempos de busquedas 
        double tpoArbol_idExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoArbol_nameExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoArbol_idNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoArbol_nameNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoArbol_idNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoArbol_nameNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

        double tpoHashCer_idExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoHashCer_nameExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoHashCer_idNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoHashCer_nameNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoHashCer_idNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoHashCer_nameNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

        double tpoHashAbie_idExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoHashAbie_nameExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoHashAbie_idNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoHashAbie_nameNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoHashAbie_idNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoHashAbie_nameNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

        double tpoUnSet_idExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoUnSet_nameExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoUnSet_idNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoUnSet_nameNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoUnSet_idNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoUnSet_nameNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

        double tpoSet_idExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoSet_nameExistente[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoSet_idNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoSet_nameNoExistente_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        double tpoSet_idNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tpoSet_nameNoExistente_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

        for(int k = 0; k < n[i]; k++){
            /*************************************************/
            /*******    BUSQUEDA CON CLAVE USER_ID     *******/
            /*************************************************/

            /********** BUSQUEDA VALORES EXISTENTES PARA CADA TDA ************/
            elemento = vector_elem_id[(long long)rand() % cantidad];

            // Busqueda Arbol
            evaluationSearchArbol(arbol_id, elemento, tpoArbol_idExistente, i);

            // Busqueda Hashing Cerrado
            evaluationSearchHashingClosed(hashCerrado_id, elemento, tpoHashCer_idExistente, i); 

            // Busqueda Hashing Abierto
            evaluationSearchHashingOpen(hashAbierto_id, elemento, tpoHashAbie_idExistente, i); 
        
            // Busqueda Unordered_set
            evaluationSearchUnorderedSet(unSet_id, elemento, tpoUnSet_idExistente, i); 

            // Busqueda Set
            evaluationSearchSet(set_id, elemento, tpoSet_idExistente, i); 


            /********** BUSQUEDA VALORES ALTOS NO EXISTENTES EN LA DATA CON NUMEROS SIMILARES AL RANGO DE VALORES EXISTENTES ************/
            elemento = vector_others_v1_id[(long long)rand() % cantidad];
            
            // Busqueda Arbol 
            evaluationSearchArbol(arbol_id, elemento, tpoArbol_idNoExistente_v1, i);

            // Busqueda Hashing Cerrado 
            evaluationSearchHashingClosed(hashCerrado_id, elemento, tpoHashCer_idNoExistente_v1, i);    

            // Busqueda Hashing Abierto 
            evaluationSearchHashingOpen(hashAbierto_id, elemento, tpoHashAbie_idNoExistente_v1, i); 
        
            // Busqueda Unordered_set
            evaluationSearchUnorderedSet(unSet_id, elemento, tpoUnSet_idNoExistente_v1, i);

            // Busqueda Set
            evaluationSearchSet(set_id, elemento, tpoSet_idNoExistente_v1, i);


            /********** BUSQUEDA VALORES PEQUEÑOS NO EXISTENTES EN LA DATA **********/
            elemento = vector_others_v2_id[(long long)rand() % cantidad];
            
            // Busqueda Arbol
            evaluationSearchArbol(arbol_id, elemento, tpoArbol_idNoExistente_v2, i);

            // Busqueda Hashing Cerrado
            evaluationSearchHashingClosed(hashCerrado_id, elemento, tpoHashCer_idNoExistente_v2, i);

            // Busqueda Hashing Abierto
            evaluationSearchHashingOpen(hashAbierto_id, elemento, tpoHashAbie_idNoExistente_v2, i); 
        
            // Busqueda Unordered_set
            evaluationSearchUnorderedSet(unSet_id, elemento, tpoUnSet_idNoExistente_v2, i);

            // Busqueda Set
            evaluationSearchSet(set_id, elemento, tpoSet_idNoExistente_v2, i);


            /***************************************************/
            /*******    BUSQUEDA CON CLAVE USER_NAME     *******/
            /***************************************************/

            /********** BUSQUEDA DE VALORES EXISTENTES PARA CADA TDA ************/
            elemento = vector_elem_name[(long long)rand() % cantidad];

            // Busqueda Arbol
            evaluationSearchArbol(arbol_name, elemento, tpoArbol_nameExistente, i);

            // Busqueda Hashing Cerrado
            evaluationSearchHashingClosed(hashCerrado_name, elemento, tpoHashCer_nameExistente, i);

            // Busqueda Hashing Abierto
            evaluationSearchHashingOpen(hashAbierto_name, elemento, tpoHashAbie_nameExistente, i); 

            // Busqueda Unordered_set
            evaluationSearchUnorderedSet(unSet_name, elemento, tpoUnSet_nameExistente, i);

            // Busqueda Set
            evaluationSearchSet(set_name, elemento, tpoSet_nameExistente, i);


            /********** BUSQUEDA DE VALORES ALTOS NO EXISTENTES EN LA DATA CON NUMEROS SIMILARES AL RANGO DE VALORES EXISTENTES ************/
            elemento = vector_others_v1_name[(long long)rand() % cantidad];
            
            // Busqueda Arbol
            evaluationSearchArbol(arbol_name, elemento, tpoHashCer_nameNoExistente_v1, i);

            // Busqueda Hashing Cerrado
            evaluationSearchHashingClosed(hashCerrado_name, elemento, tpoHashCer_nameExistente, i);

            // Busqueda Hashing Abierto
            evaluationSearchHashingOpen(hashAbierto_name, elemento, tpoHashAbie_nameNoExistente_v1, i); 

            // Busqueda Unordered_set
            evaluationSearchUnorderedSet(unSet_name, elemento, tpoUnSet_nameNoExistente_v1, i);
    
            // Busqueda Set
            evaluationSearchSet(set_name, elemento, tpoSet_nameNoExistente_v1, i);


            /********** BUSQUEDA DE VALORES PEQUEÑOS NO EXISTENTES EN LA DATA **********/
            elemento = vector_others_v2_name[(long long)rand() % cantidad];
            
            // Busqueda Arbol
            evaluationSearchArbol(arbol_name, elemento, tpoArbol_nameNoExistente_v2, i);

            // Busqueda Hashing Cerrado
            evaluationSearchHashingClosed(hashCerrado_name, elemento, tpoHashCer_nameNoExistente_v2, i);

            // Busqueda Hashing Abierto
            evaluationSearchHashingOpen(hashAbierto_name, elemento, tpoHashAbie_nameNoExistente_v2, i); 

            // Busqueda Unordered_set
            evaluationSearchUnorderedSet(unSet_name, elemento, tpoUnSet_nameNoExistente_v2, i);
    
            // Busqueda Set
            evaluationSearchSet(set_name, elemento, tpoSet_nameNoExistente_v2, i);
            
        }

        // Tiempo considerando el promedio de busquedas
        tpoArbol_idExistente[i] /= n[i];
        tpoArbol_idNoExistente_v1[i] /= n[i];
        tpoArbol_idNoExistente_v2[i] /= n[i];

        tpoHashCer_idExistente[i] /= n[i];
        tpoHashCer_idNoExistente_v1[i] /= n[i];
        tpoHashCer_idNoExistente_v2[i] /= n[i];

        tpoHashAbie_idExistente[i] /= n[i];
        tpoHashAbie_idNoExistente_v1[i] /= n[i];
        tpoHashAbie_idNoExistente_v2[i] /= n[i];

        tpoUnSet_idExistente[i] /= n[i];
        tpoUnSet_idNoExistente_v1[i] /= n[i];
        tpoUnSet_idNoExistente_v2[i] /= n[i];

        tpoSet_idExistente[i] /= n[i];
        tpoSet_idNoExistente_v1[i] /= n[i];
        tpoSet_idNoExistente_v2[i] /= n[i];

        tpoArbol_nameExistente[i] /= n[i];
        tpoArbol_nameNoExistente_v1[i] /= n[i];
        tpoArbol_nameNoExistente_v2[i] /= n[i];

        tpoHashCer_nameExistente[i] /= n[i];
        tpoHashCer_nameNoExistente_v1[i] /= n[i];
        tpoHashCer_nameNoExistente_v2[i] /= n[i];

        tpoHashAbie_nameExistente[i] /= n[i];
        tpoHashAbie_nameNoExistente_v1[i] /= n[i];
        tpoHashAbie_nameNoExistente_v2[i] /= n[i];

        tpoUnSet_nameExistente[i] /= n[i];
        tpoUnSet_nameNoExistente_v1[i] /= n[i];
        tpoUnSet_nameNoExistente_v2[i] /= n[i];

        tpoSet_nameExistente[i] /= n[i];
        tpoSet_nameNoExistente_v1[i] /= n[i];
        tpoSet_nameNoExistente_v2[i] /= n[i];
        
        cout << "CANTIDAD DE BUSQUEDAS: " << n[i] << endl;
        cout << "********************* EVALUACION EXPERIMENTAL BUSQUEDAS CON CLAVE USER_ID *********************" << endl;
        cout << "Tipo \t \t \t \tArbol[ns] \tHashCerrado[ns] \tHashAbierto[ns] \tUnordered_set[ns] \tSet[ns]" << endl;
        cout << "Existente \t \t \t" << tpoArbol_idExistente[i] << "\t \t" << tpoHashCer_idExistente[i] << "\t \t \t" << tpoHashAbie_idExistente[i] << "\t \t \t" << tpoUnSet_idExistente[i] << "\t \t \t" << tpoUnSet_idExistente[i] << endl;
        cout << "No existente grandes \t \t" << tpoArbol_idNoExistente_v1[i] << "\t \t" << tpoHashCer_idNoExistente_v1[i] << "\t \t \t" << tpoHashAbie_idNoExistente_v1[i] << "\t \t \t" << tpoUnSet_idNoExistente_v1[i] << "\t \t \t" << tpoSet_idNoExistente_v1[i] << endl;
        cout << "No existente pequenios \t \t" << tpoArbol_idNoExistente_v2[i] << "\t \t" << tpoHashCer_idNoExistente_v2[i] << "\t \t \t" << tpoHashAbie_idNoExistente_v2[i] << "\t \t \t" << tpoUnSet_idNoExistente_v2[i] << "\t \t \t" << tpoSet_idNoExistente_v2[i] << endl;

        cout << "********************* EVALUACION EXPERIMENTAL BUSQUEDAS CON CLAVE USER_NAME *********************" << endl;
        cout << "Tipo \t \t \t \tArbol[ns] \tHashCerrado[ns] \tHashAbierto[ns] \tUnordered_set[ns] \tSet[ns]" << endl;
        cout << "Existente \t \t \t" << tpoArbol_nameExistente[i] << "\t \t" << tpoHashCer_nameExistente[i] << "\t \t \t" << tpoHashAbie_nameExistente[i] << "\t \t \t" << tpoUnSet_nameExistente[i] << "\t \t \t" << tpoUnSet_nameExistente[i] << endl;
        cout << "No existente grandes \t \t" << tpoArbol_nameNoExistente_v1[i] << "\t \t" << tpoHashCer_nameNoExistente_v1[i] << "\t \t \t" << tpoHashAbie_nameNoExistente_v1[i] << "\t \t \t" << tpoUnSet_nameNoExistente_v1[i] << "\t \t \t" << tpoSet_nameNoExistente_v1[i] << endl;
        cout << "No existente pequenios \t \t" << tpoArbol_nameNoExistente_v2[i] << "\t \t" << tpoHashCer_nameNoExistente_v2[i] << "\t \t \t" << tpoHashAbie_nameNoExistente_v2[i] << "\t \t \t" << tpoUnSet_nameNoExistente_v2[i] << "\t \t \t" << tpoSet_nameNoExistente_v2[i] << endl;

    }

	return 0;
}

/***********************************************************************/
/*******    Funciones Evaluacion Experimental Inserción TDAs     *******/
/***********************************************************************/

void evaluationInsertArbol(ArbolBinarioBusqueda &arbol, double &tiempo, int contador, long long key, double** tpoArbol, int tElem[], int i){
	start = chrono::high_resolution_clock::now();
	arbol.insertar(key);
	finish = chrono::high_resolution_clock::now();
	tiempo += chrono::duration_cast<chrono::microseconds> (finish - start).count();
	//cout << "ARBOL: " << contador << endl;
    if(contador == tElem[0]-1){	// insertar 50°
		tpoArbol[0][i] = tiempo;
	}else if(contador == tElem[1]-1){	// insertar 100°
		tpoArbol[1][i] = tiempo;
	}else if(contador == tElem[2]-1){	// insertar 500°
		tpoArbol[2][i] = tiempo;
	}else if(contador == tElem[3]-1){	// insertar 1000°
		tpoArbol[3][i] = tiempo;
	}else if(contador == tElem[4]-1){	// insertar 5000°
		tpoArbol[4][i] = tiempo;
	}else if(contador == tElem[5]-1){	// insertar 10000°
		tpoArbol[5][i] = tiempo;
	}else if(contador == tElem[6]-1){
		tpoArbol[6][i] = tiempo;
	}else if(contador == tElem[7]-1){
		tpoArbol[7][i] = tiempo;
	}else if(contador == tElem[8]-1){
		tpoArbol[8][i] = tiempo;
	}  
}

void evaluationInsertHashingClosed(HashingClosed &hash, double &tiempo, int contador, long long key, double** tpoHash, int tElem[], int i){
	start = chrono::high_resolution_clock::now();
	hash.insertar(key);
	finish = chrono::high_resolution_clock::now();
	tiempo += chrono::duration_cast<chrono::microseconds> (finish - start).count();
	//cout << "CERRADO: " << contador << endl;
    if(contador == tElem[0]-1){	// insertar 50°
		tpoHash[0][i] = tiempo;
	}else if(contador == tElem[1]-1){	// insertar 100°
		tpoHash[1][i] = tiempo;
	}else if(contador == tElem[2]-1){	// insertar 500°
		tpoHash[2][i] = tiempo;
	}else if(contador == tElem[3]-1){	// insertar 1000°
		tpoHash[3][i] = tiempo;
	}else if(contador == tElem[4]-1){	// insertar 5000°
		tpoHash[4][i] = tiempo;
	}else if(contador == tElem[5]-1){	// insertar 10000°
		tpoHash[5][i] = tiempo;
	}else if(contador == tElem[6]-1){
		tpoHash[6][i] = tiempo;
	}else if(contador == tElem[7]-1){
		tpoHash[7][i] = tiempo;
	}else if(contador == tElem[8]-1){
		tpoHash[8][i] = tiempo;
	}  
}

void evaluationInsertHashingOpen(HashingOpen &hash, double &tiempo, int contador, long long key, double** tpoHash, int tElem[], int i){
	start = chrono::high_resolution_clock::now();
	hash.insertar(key);
	finish = chrono::high_resolution_clock::now();
	tiempo += chrono::duration_cast<chrono::microseconds> (finish - start).count();
	//cout << "ABIERTO: " << contador << endl;
    if(contador == tElem[0]-1){	// insertar 50°
		tpoHash[0][i] = tiempo;
	}else if(contador == tElem[1]-1){	// insertar 100°
		tpoHash[1][i] = tiempo;
	}else if(contador == tElem[2]-1){	// insertar 500°
		tpoHash[2][i] = tiempo;
	}else if(contador == tElem[3]-1){	// insertar 1000°
		tpoHash[3][i] = tiempo;
	}else if(contador == tElem[4]-1){	// insertar 5000°
		tpoHash[4][i] = tiempo;
	}else if(contador == tElem[5]-1){	// insertar 10000°
		tpoHash[5][i] = tiempo;
	}else if(contador == tElem[6]-1){
		tpoHash[6][i] = tiempo;
	}else if(contador == tElem[7]-1){
		tpoHash[7][i] = tiempo;
	}else if(contador == tElem[8]-1){
		tpoHash[8][i] = tiempo;
	}  
}

void evaluationInsertUnorderedSetSTL(unordered_set<long long> &unSet, double &tiempo, int contador, long long key, double** tpoUnSet, int tElem[], int i){
	start = chrono::high_resolution_clock::now();
	unSet.insert(key);
	finish = chrono::high_resolution_clock::now();
	tiempo += chrono::duration_cast<chrono::microseconds> (finish - start).count();
	//cout << "UNORDERED_SET: " << contador << endl;
    if(contador == tElem[0]-1){	// insertar 50°
		tpoUnSet[0][i] = tiempo;
	}else if(contador == tElem[1]-1){	// insertar 100°
		tpoUnSet[1][i] = tiempo;
	}else if(contador == tElem[2]-1){	// insertar 500°
		tpoUnSet[2][i] = tiempo;
	}else if(contador == tElem[3]-1){	// insertar 1000°
		tpoUnSet[3][i] = tiempo;
	}else if(contador == tElem[4]-1){	// insertar 5000°
		tpoUnSet[4][i] = tiempo;
	}else if(contador == tElem[5]-1){	// insertar 10000°
		tpoUnSet[5][i] = tiempo;
	}else if(contador == tElem[6]-1){
		tpoUnSet[6][i] = tiempo;
	}else if(contador == tElem[7]-1){
		tpoUnSet[7][i] = tiempo;
	}else if(contador == tElem[8]-1){
		tpoUnSet[8][i] = tiempo;
	}  
}

void evaluationInsertSetSTL(set<long long> &set, double &tiempo, int contador, long long key, double** tpoSet, int tElem[], int i){
	start = chrono::high_resolution_clock::now();
	set.insert(key);
	finish = chrono::high_resolution_clock::now();
	tiempo += chrono::duration_cast<chrono::microseconds> (finish - start).count();
	//cout << "SET: " << contador << endl;
    if(contador == tElem[0]-1){	// insertar 50°
		tpoSet[0][i] = tiempo;
	}else if(contador == tElem[1]-1){	// insertar 100°
		tpoSet[1][i] = tiempo;
	}else if(contador == tElem[2]-1){	// insertar 500°
		tpoSet[2][i] = tiempo;
	}else if(contador == tElem[3]-1){	// insertar 1000°
		tpoSet[3][i] = tiempo;
	}else if(contador == tElem[4]-1){	// insertar 5000°
		tpoSet[4][i] = tiempo;
	}else if(contador == tElem[5]-1){	// insertar 10000°
		tpoSet[5][i] = tiempo;
	}else if(contador == tElem[6]-1){
		tpoSet[6][i] = tiempo;
	}else if(contador == tElem[7]-1){
		tpoSet[7][i] = tiempo;
	}else if(contador == tElem[8]-1){
		tpoSet[8][i] = tiempo;
	}  
}

void impresionInsert(int tElem[], double** tpoArbol_id, double** tpoHashCerrado_id, double** tpoHashAbierto_id, double** tpoUnorderedSet_id, double** tpoSet_id, double** tpoArbol_name, double** tpoHashCerrado_name, double** tpoHashAbierto_name, double** tpoUnorderedSet_name, double** tpoSet_name){
	double temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10;

    double tiempoArbol_id[9];
    double tiempoHashCerrado_id[9];
    double tiempoHashAbierto_id[9];
    double tiempoUnorderedSet_id[9];
    double tiempoSet_id[9];

	double tiempoArbol_name[9];
    double tiempoHashCerrado_name[9];
    double tiempoHashAbierto_name[9];
    double tiempoUnorderedSet_name[9];
    double tiempoSet_name[9];
    
    for(int i = 0; i<9; i++){
        for(int j = 0; j<replicas; j++){
            temp1 += tpoArbol_id[i][j];
            temp2 += tpoHashCerrado_id[i][j];
            temp3 += tpoHashAbierto_id[i][j];
            temp4 += tpoUnorderedSet_id[i][j];
            temp5 += tpoSet_id[i][j];

            temp6 += tpoArbol_name[i][j];
            temp7 += tpoHashCerrado_name[i][j];
            temp8 += tpoHashAbierto_name[i][j];
            temp9 += tpoUnorderedSet_name[i][j];
            temp10 += tpoSet_name[i][j];
        }

        tiempoArbol_id[i] = temp1/replicas;
        tiempoHashCerrado_id[i] = temp2/replicas;
        tiempoHashAbierto_id[i] = temp3/replicas;
        tiempoUnorderedSet_id[i] = temp4/replicas;
        tiempoSet_id[i] = temp5/replicas;

        tiempoArbol_name[i] = temp6/replicas;
        tiempoHashCerrado_name[i] = temp7/replicas;
        tiempoHashAbierto_name[i] = temp8/replicas;
        tiempoUnorderedSet_name[i] = temp9/replicas;
        tiempoSet_name[i] = temp10/replicas;
    }

	cout << "********************* EVALUACION EXPERIMENTAL INSERCIONES CON CLAVE USER_ID *********************" << endl;

	cout << "Insertados \tArbol[ns] \tHashingCerrado[ns] \tHashingAbierto[ns] \tUnordered_set[ns] \tSet"<< endl;
	for(int i = 0; i < 9; i++){
		cout << tElem[i] << "\t \t" << tiempoArbol_id[i] << "\t \t" << tiempoHashCerrado_id[i] << "\t \t \t \t" << tiempoHashAbierto_id[i] << "\t \t \t" << tiempoUnorderedSet_id[i] << "\t \t \t" << tiempoSet_id[i] << endl;
	}
    cout << endl;

	cout << "********************* EVALUACION EXPERIMENTAL INSERCIONES CON CLAVE USER_NAME *********************" << endl;

	cout << "Insertados \tArbol[ns] \tHashingCerrado[ns] \tHashingAbierto[ns] \tUnordered_set[ns] \tSet"<< endl;
	for(int i = 0; i < 9; i++){
		cout << tElem[i] << "\t \t" << tiempoArbol_name[i] << "\t \t" << tiempoHashCerrado_name[i] << "\t \t \t \t" << tiempoHashAbierto_name[i] << "\t \t \t" << tiempoUnorderedSet_name[i] << "\t \t \t" << tiempoSet_name[i] << endl;
	}
    cout << endl;
}


/***********************************************************************/
/*******    Funciones Evaluacion Experimental Busquedas TDAs     *******/
/***********************************************************************/

void evaluationSearchArbol(ArbolBinarioBusqueda &arbol, long long elemento, double tpoArbol[], int i){
    start = chrono::high_resolution_clock::now();
	arbol.buscar(elemento);
	finish = chrono::high_resolution_clock::now();
    tpoArbol[i] += chrono::duration_cast<chrono::microseconds> (finish - start).count();
}

void evaluationSearchHashingClosed(HashingClosed &hash, long long elemento, double tpoHash[], int i){
    start = chrono::high_resolution_clock::now();unsigned t0 = clock();
	hash.buscar(elemento);
	finish = chrono::high_resolution_clock::now();
    tpoHash[i] += chrono::duration_cast<chrono::microseconds> (finish - start).count();
}

void evaluationSearchHashingOpen(HashingOpen &hash, long long elemento, double tpoHash[], int i){
    start = chrono::high_resolution_clock::now();
	hash.buscar(elemento);
	finish = chrono::high_resolution_clock::now();
    tpoHash[i] += chrono::duration_cast<chrono::microseconds> (finish - start).count();
}

void evaluationSearchUnorderedSet(unordered_set<long long> &unSet, long long elemento, double tpoUnSet[], int i){
    start = chrono::high_resolution_clock::now();
	unSet.find(elemento);
	finish = chrono::high_resolution_clock::now();
    tpoUnSet[i] += chrono::duration_cast<chrono::microseconds> (finish - start).count();
}

void evaluationSearchSet(set<long long> &set, long long elemento, double tpoSet[], int i){
    start = chrono::high_resolution_clock::now();
	set.find(elemento);
	finish = chrono::high_resolution_clock::now();
    tpoSet[i] += chrono::duration_cast<chrono::microseconds> (finish - start).count();
}


/**************************************/
/*******    Funcion externa     *******/
/**************************************/

long long asciiName(string name_user){
/* Manejo de claves con letras
    Parameters:
        name_user: Clave con nombre unico que quiere ingresar a la Tabla
        
    Returns:
        int: Devuelve el nombre transformado en un numero 
                                                    */

    long long valorAscii, valorName, radix;
    
    // Mutlplicación de cada caracter ASCII por el indice +1 del elemento
    for(int i = 5; i>=0 ; i--){ // Se consideran solo los 6 primeros digitos
        if (name_user.size() >= i){ 
            valorAscii = name_user[i];
            radix = pow(128, i);
            valorName += valorAscii * radix;
        }
    }
    return valorName;
}

double** createMatrix(int n, int m){
	// Funcion que crea una matriz
    double** newMatrix = new double*[n];
    for (int i = 0; i < n; i++){
        newMatrix[i] = new double[m];
    }
    return newMatrix;
}

void eliminarMatriz(double** &matriz, int num_filas){
    // Funcion que elimina una matriz
    for(int e=0; e<num_filas; e++){
        delete [] matriz[e];
	}
	delete [] matriz;
}