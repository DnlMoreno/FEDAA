#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<fstream>

using namespace std;

int** transponerMatriz(int** matriz, int** &matriz_trans, int filas, int columnas);
int** multMatrizIterOpt(int** A, int** B, int** &B_tp, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2);
void eliminarMatriz(int** &matriz, int num_filas);

int main(int argc, char *argv[]){

	int puntos, instancias, fila_M1, columnaM1_filaM2, columna_M2;
	ifstream matriz_A; 
	ifstream matriz_B;
	
	matriz_A.open("C:/Users/gamor/Documents/GitHub/Fundamentos-Estructuras-de-Datos-y-Algoritmos/Informe n°1/Generación base de datos/matriz_rect_A_caso4.txt");
	matriz_B.open("C:/Users/gamor/Documents/GitHub/Fundamentos-Estructuras-de-Datos-y-Algoritmos/Informe n°1/Generación base de datos/matriz_rect_B_caso4.txt");

	matriz_A >> puntos;
	matriz_A >> instancias;
	
	matriz_B >> puntos;
	matriz_B >> instancias;
	
    for (int k=0; k<puntos; k++){
    	cout << "Tamano M1   Tamano M2" << "\t" << "\t" << "tiempoIter" << endl;	
    	matriz_A >> fila_M1;
    	matriz_A >> columnaM1_filaM2;
    	
		matriz_B >> columnaM1_filaM2;
		matriz_B >> columna_M2;
		
		double tiempoAcum = 0.0;  	
	
		for(int h=0; h<instancias; h++){
			int** A = new int*[fila_M1];
			int** B = new int*[columnaM1_filaM2];
			int** C = new int*[fila_M1]; 
			int** B_tp = new int*[columna_M2];
			
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

			for(int i=0; i<columna_M2; i++){
				B_tp[i] = new int[columnaM1_filaM2];			
			}	
			
			for(int i=0; i<fila_M1; i++){
				C[i] = new int[columna_M2];			
			}	
			
			unsigned t0 = clock();
			C = multMatrizIterOpt(A, B, B_tp, C, fila_M1, columnaM1_filaM2, columna_M2);			
			unsigned t1 = clock();
			double tiempo = (double)(t1 - t0)/CLOCKS_PER_SEC;
			
			cout << fila_M1 << " x " << columnaM1_filaM2 << "  " << columnaM1_filaM2 << " x " << columna_M2 << "\t" << "\t" << tiempo << " segs." << endl;	
			
			eliminarMatriz(A, fila_M1);
			eliminarMatriz(B, columnaM1_filaM2);
			eliminarMatriz(B_tp, columna_M2);
			eliminarMatriz(C, fila_M1);	
		}
		cout << endl;	
    }
   	
	return 0;	
}

int** multMatrizIterOpt(int** A, int** B, int** &B_tp, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2){
	
	B_tp = transponerMatriz(B, B_tp, columnaM1_filaM2, columna_M2);
		
	for(int i=0; i<fila_M1; i++){
		for(int j=0; j<columna_M2; j++){
			C[i][j] = 0;
			for(int k=0; k<columnaM1_filaM2; k++){
				C[i][j] += A[i][k] * B_tp[j][k];
			}
		}
	}	
	return C;
}

int** transponerMatriz(int** matriz, int** &matriz_trans, int filas, int columnas){
	
	for(int i=0; i<filas; i++){
		for(int j=0; j<columnas; j++){
			matriz_trans[j][i] = matriz[i][j];
		}
	}	
	return matriz_trans;
}

void eliminarMatriz(int** &matriz, int num_filas){
	for(int e=0; e<num_filas; e++){
		delete [] matriz[e];
	}
	delete [] matriz;
}



	
