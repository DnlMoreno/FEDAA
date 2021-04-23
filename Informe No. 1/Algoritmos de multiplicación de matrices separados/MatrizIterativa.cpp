#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<fstream>

using namespace std;

int** multMatIter(int** A, int** B, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2);

int main(int argc, char const *argv[]){

	int puntos, instancias, fila_M1, columnaM1_filaM2, columna_M2;
	ifstream matriz_A; 
	ifstream matriz_B;
	
	matriz_A.open("C:/Users/gamor/Documents/GitHub/Fundamentos-Estructuras-de-Datos-y-Algoritmos/Informe n°1/Generación base de datos/Entradas algoritmos de multplicación de matrices/matriz_cuad_A_caso1.txt");
	matriz_B.open("C:/Users/gamor/Documents/GitHub/Fundamentos-Estructuras-de-Datos-y-Algoritmos/Informe n°1/Generación base de datos/Entradas algoritmos de multplicación de matrices/matriz_cuad_B_caso1.txt");

	matriz_A >> puntos;
	matriz_A >> instancias;
	
	matriz_B >> puntos;
	matriz_B >> instancias;
	
    for (int k=0; k<puntos; k++){
    	cout << "n  x  m    m  x  r" << "\t" << "\t" << "tiempoBB" << endl;	
    	matriz_A >> fila_M1;
    	matriz_A >> columnaM1_filaM2;
    	
		matriz_B >> columnaM1_filaM2;
		matriz_B >> columna_M2;
		
		double tiempoAcum = 0.0;  	
	
		for(int h=0; h<instancias; h++){
			int** A = new int*[fila_M1];
			int** B = new int*[columnaM1_filaM2];
			int** C = new int*[fila_M1]; 
			
		    for (int i=0; i<fila_M1; i++){
		    	A[i] = new int[columnaM1_filaM2];	    	
		        for (int j=0; j<columnaM1_filaM2; j++){
		            matriz_A >> A[i][j];         
		        }
		    }
			
			for(int i=0; i<columnaM1_filaM2; i++){
				B[i] = new int[columna_M2];
				for(int j=0; j<columna_M2; j++){
					matriz_B >> B[i][j];
				}	
			}   
			
			for(int i=0; i<fila_M1; i++){
				C[i] = new int[columna_M2];			
			}	
			
			unsigned t0 = clock();
			C = multMatIter(A, B, C, fila_M1, columnaM1_filaM2, columna_M2);
			unsigned t1 = clock();
			double tiempo = (double)(t1 - t0)/CLOCKS_PER_SEC;
			
			cout << fila_M1 << " x " << columnaM1_filaM2 << "  " << columnaM1_filaM2 << " x " << columna_M2 << "\t" << "\t" << tiempo << " segs.";	
			
			for(int e=0; e<fila_M1; e++){
				delete [] A[e];
			}
			delete [] A;
			
			for(int e=0; e<columnaM1_filaM2; e++){
				delete [] B[e];
			}
			delete [] B; 
			
			for(int e=0; e<fila_M1; e++){
				delete [] C[e];
			}
			delete [] C;
			
			cout << endl;
		}
		cout << endl;
	}
    return 0;
}

int** multMatIter(int** A, int** B, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2){	
	for(int i=0; i<fila_M1; i++){
		for(int j=0; j<columna_M2; j++){
			C[i][j] = 0;
			for(int k=0; k<columnaM1_filaM2; k++){
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}	
	return C;
}

