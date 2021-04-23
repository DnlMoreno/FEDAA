#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void inputs_iniciales(int &puntos, int &instancias);
void inputs_secundarios(int puntos, vector<int> &size, vector<int> &dim_M1_M2, vector<int> &fila_M1, vector<int> &columnaM1_filaM2, vector<int> &columna_M2);
void casiOrdenados(int puntos, int instancias, vector<int> size);
void mitadOrdenados(int puntos, int instancias, vector<int> size);
void aleatorios(int puntos, int instancias, vector<int> size);
void ordenadosReversa(int puntos, int instancias, vector<int> size);
void valoresRepetidos(int puntos, int instancias, vector<int> size);
void matrizCuadrada(int puntos, int instancias, vector<int> dim_M1_M2);
void matrizRectangular(int puntos, int instancias, vector<int> fila_M1, vector<int> columnaM1_filaM2, vector<int> columna_M2);

int main(int argc, char const *argv[]){
	int puntos, instancias;
	inputs_iniciales(puntos, instancias);
	
	vector<int> size(puntos);
	vector<int> dim_M1_M2(puntos);
	vector<int> fila_M1(puntos);
	vector<int> columnaM1_filaM2(puntos);
	vector<int> columna_M2(puntos);
    inputs_secundarios(puntos, size, dim_M1_M2, fila_M1, columnaM1_filaM2, columna_M2);
    
    casiOrdenados(puntos, instancias, size);
    mitadOrdenados(puntos, instancias, size);
    aleatorios(puntos, instancias, size); 
    ordenadosReversa(puntos, instancias, size);
    valoresRepetidos(puntos, instancias, size);

    matrizCuadrada(puntos, instancias, dim_M1_M2);
    matrizRectangular(puntos, instancias, fila_M1, columnaM1_filaM2, columna_M2);
    return 0;
}

void inputs_iniciales(int &puntos, int &instancias){
	cout << "Ingrese el numero de puntos (tamanos de las entradas del vector) que desea en el eje x del grafico: ";
	cin >> puntos;
    cout << endl;

	cout << "Ingrese el numero de instancias (replicas o repeticiones) que correra por cada tamano del vector: ";
	cin >> instancias;
    cout << endl;	
}

void inputs_secundarios(int puntos, vector<int> &size, vector<int> &dim_M1_M2, vector<int> &fila_M1, vector<int> &columnaM1_filaM2, vector<int> &columna_M2){
    cout << "Ingrese " << puntos << " tamanos diferentes de vectores: " << endl;
    for(int i=0; i<puntos; i++){
    	cout << i + 1 <<".- ";
		cin >> size[i];
		cout << endl;
	}

	cout << "Ingrese " << puntos << " tamanos diferentes de la matriz cuadrada A y B: " << endl;
    for(int i=0; i<puntos; i++){
    	cout << i + 1 <<".- ";
		cin >> dim_M1_M2[i];
		cout << endl;
	}

    cout << "Ingrese " << puntos << " tamanos diferentes para la matriz rectangular A y B: " << endl;
    
    cout << "Nota: Considere que el numero de columnas para la matriz rectangular A, sera el mismo numero de filas para la matriz rectangular B" << endl;;
    for(int i=0; i<puntos; i++){
		cout << i + 1 <<".- " << "Fila matriz A: ";
		cin >> fila_M1[i];
		cout << endl;
		cout << i + 1 <<".- " << "Columna matriz A y Fila matriz B: ";
		cin >> columnaM1_filaM2[i];
		cout << endl;
	    cout << i + 1 <<".- " << "Columna matriz B: ";
		cin >> columna_M2[i];
	    cout << endl; 
	}
}

void casiOrdenados(int puntos, int instancias, vector<int> size){
    ofstream casi;
    casi.open("Entrada casiOrdenados.txt", ios::out);

    if(casi.fail()){
        cout << "No se pudo crear el archivo con los datos casi ordenados. Intentelo nuevamente por favor";
        exit(1);
    }

    casi << puntos << " ";
    casi << instancias << endl;

    for (int k=0; k<puntos; k++){
    	casi << size[k] << endl;
		for(int i=0; i<instancias; i++){

			for(int j=0; j<size[k]; j++){
		        if (((float) rand()/RAND_MAX) < 0.8){
		            casi << j << " ";
		        } else {
		            casi << rand() % (size[k]) << " ";
		        }
			}
		}
		casi << endl;
	}
    casi.close();
}

void mitadOrdenados(int puntos, int instancias, vector<int> size){

    ofstream mitad;
    mitad.open("Entrada mitadOrdenados.txt", ios::out);

    if(mitad.fail()){
        cout << "No se pudo crear el archivo con los datos mitad ordenados. Intentelo nuevamente por favor";
        exit(1);
    }

    mitad << puntos << " ";
    mitad << instancias << endl;

    for (int k=0; k<puntos; k++){
    	mitad << size[k] << endl;

		for(int i=0; i<instancias; i++){

			for(int j=0; j<size[k]; j++){
		        if (((float) rand()/RAND_MAX) < 0.5){
		            mitad << j << " ";
		        } else {
		            mitad << rand() % (size[k]) << " ";
		        }
			}
		}
		mitad << endl;
	}
    mitad.close();
}

void aleatorios(int puntos, int instancias, vector<int> size){

    ofstream random;
    random.open("Entrada aleatorios.txt", ios::out);

    if(random.fail()){
        cout << "No se pudo crear el archivo con los datos aleatorios. Intentelo nuevamente por favor";
        exit(1);
    }

    random << puntos << " ";
    random << instancias << endl;

    for (int k=0; k<puntos; k++){
    	random << size[k] << endl;

		for(int i=0; i<instancias; i++){

			for(int j=0; j<size[k]; j++){
		        random << rand() % size[k] << " ";
			}
		}
		random << endl;
	}

    random.close();
}

void ordenadosReversa(int puntos, int instancias, vector<int> size){
    ofstream reversa;
    reversa.open("Entrada ordenadosReversa.txt", ios::out);

    if(reversa.fail()){
        cout << "No se pudo crear el archivo con los datos ordenados en reversa. Intentelo nuevamente por favor";
        exit(1);
    }

    reversa << puntos << " ";
    reversa << instancias << endl;

    for (int k=0; k<puntos; k++){
    	reversa << size[k] << endl;

		for(int i=0; i<instancias; i++){

		    for(int j=0; j<size[k]; j++){
		        reversa << size[k] - 1 - j << " ";
		    }
		}
		reversa << endl;
	}
    reversa.close();
}

void valoresRepetidos(int puntos, int instancias, vector<int> size){
    int n;
    int div = 500;

    ofstream repetidos;
    repetidos.open("Entrada valoresRepetidos.txt", ios::out);

    if(repetidos.fail()){
        cout << "No se pudo crear el archivo con lista de datos repetidos. Intentelo nuevamente por favor";
        exit(1);
    }

    repetidos << puntos << " ";
    repetidos << instancias << endl;

    for (int k=0; k<puntos; k++){
    	n = size[k] / div;
    	repetidos << size[k] << endl;

		for(int j=0; j<instancias; j++){
			
			vector<int> aux(n);
    		vector<int> arr;

		    for(int key=0; key<n; key++){
		        aux[key] = rand() % size[k];
		    }

			for(int i=0; i<div; i++){
		        arr.insert(arr.end(),aux.begin(),aux.end());
		    }

			random_shuffle(arr.begin(), arr.end());

			for(int i=0; i<size[k]; i++){
				repetidos << arr[i] << " ";
			}
		}
		repetidos << endl;
	}
    repetidos.close();
}

void matrizCuadrada(int puntos, int instancias, vector<int> dim_M1_M2){
    ofstream matriz_cuad_A;
    ofstream matriz_cuad_B;
    matriz_cuad_A.open("matriz_cuad_A_caso1.txt", ios::out);
    matriz_cuad_B.open("matriz_cuad_B_caso1.txt", ios::out);

    if(matriz_cuad_A.fail()){
        cout << "No se pudo crear el archivo de las dos matriz cuadrada A. Intentelo nuevamente por favor";
        exit(1);
    }
    if(matriz_cuad_B.fail()){
        cout << "No se pudo crear el archivo de las dos matriz cuadrada B. Intentelo nuevamente por favor";
        exit(1);
    }

    matriz_cuad_A << puntos << " ";
    matriz_cuad_A << instancias << endl;
    matriz_cuad_B << puntos << " ";
    matriz_cuad_B << instancias << endl;

    for(int k=0; k<puntos; k++){
    	matriz_cuad_A << dim_M1_M2[k] << " " << dim_M1_M2[k] << endl;
    	matriz_cuad_B << dim_M1_M2[k] << " " << dim_M1_M2[k] << endl;

		for(int h=0; h<instancias; h++){

		    for (int i=0; i < dim_M1_M2[k]; i++){
		        for (int j=0; j < dim_M1_M2[k]; j++){
		            matriz_cuad_A << rand() % (200) << " ";
		            matriz_cuad_B << rand() % (200) << " ";
		        }
		    }
		}
	    matriz_cuad_A << endl;
	    matriz_cuad_B << endl;
	}
    matriz_cuad_A.close();
    matriz_cuad_B.close();
}

void matrizRectangular(int puntos, int instancias, vector<int> fila_M1, vector<int> columnaM1_filaM2, vector<int> columna_M2){    
    ofstream matriz_rect_A;
    matriz_rect_A.open("Entrada matriz_rect_A_caso4.txt", ios::out);

    if(matriz_rect_A.fail()){
        cout << "No se pudo crear el archivo de la matriz rectangular A. Intentelo nuevamente por favor";
        exit(1);
    }

    matriz_rect_A << puntos << " ";
    matriz_rect_A << instancias << endl;

    for(int k=0; k<puntos; k++){
		matriz_rect_A << fila_M1[k] << " " << columnaM1_filaM2[k] << endl;    	
	
		for(int h=0; h<instancias; h++){
		    for (int i=0; i < fila_M1[k]; i++){
		        for (int j=0; j < columnaM1_filaM2[k]; j++){
		            matriz_rect_A << rand() % (200) << " ";
		        }
		    }
			
		}
		matriz_rect_A << endl;
    }
    matriz_rect_A.close();
    
    
    ofstream matriz_rect_B;
    matriz_rect_B.open("Entrada matriz_rect_B_caso4.txt", ios::out);
    
    if(matriz_rect_B.fail()){
        cout << "No se pudo crear el archivo de la matriz rectangular B. Intentelo nuevamente por favor";
        exit(1);
    }

    matriz_rect_B << puntos << " ";
    matriz_rect_B << instancias << endl;

    for(int k=0; k<puntos; k++){
    	matriz_rect_B << columnaM1_filaM2[k] << " " << columna_M2[k] << endl;

		for(int h=0; h<instancias; h++){
		    for (int i=0; i < columnaM1_filaM2[k]; i++){
		        for (int j=0; j < columna_M2[k]; j++){
		            matriz_rect_B << rand() % (200) << " ";
		        }
		    }  
		}
		matriz_rect_B << endl;
    }
    matriz_rect_B.close();
}
