#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<fstream>

using namespace std;

int** transponerMatriz(int** matriz, int filas, int columnas);
int** multMatrizIterOpt(int** A, int** &B, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2);

int main() {
    int fila_M1 = 15;
    int columnaM1_filaM2 = 35;
    int columna_M2 = 15;

    for(int h=0; h<10; h++){
        int** A = new int*[fila_M1];
        int** B = new int*[columnaM1_filaM2];
        int** C = new int*[fila_M1];
        
        cout << " ------------------ MATRIZ A -------------------" << endl;
        
        for(int i = 0; i<fila_M1; i++){
            A[i] = new int[columnaM1_filaM2];
            for(int j=0; j<columnaM1_filaM2; j++){
                A[i][j] = rand() % 50;
                cout << A[i][j] << " ";
            }    
            cout << endl;
        }
            
        cout << " ------------------ MATRIZ B -------------------" << endl;
        
        for(int i = 0; i<columnaM1_filaM2; i++){
            B[i] = new int[columna_M2];
            for(int j=0; j<columna_M2; j++){
                B[i][j] = rand() % 50;
                cout << B[i][j] << " ";
            }    
            cout << endl;
        }
        
        for(int i=0; i<fila_M1; i++){
            C[i] = new int[columna_M2];
        }        
        cout << endl;
        
		unsigned t0 = clock();
		C = multMatrizIterOpt(A, B, C, fila_M1, columnaM1_filaM2, columna_M2);			
		unsigned t1 = clock();
		double tiempo = (double)(t1 - t0)/CLOCKS_PER_SEC;
		
		for(int i=0; i<columna_M2; i++){
			for(int j=0; j<columnaM1_filaM2; j++){
				cout << B[i][j] << " ";
			}
			cout << endl;
		}
		
		cout << " ------------------------------------------------------------------- "<< endl;
		
		for(int i=0; i<columnaM1_filaM2; i++){
			for(int j=0; j<columna_M2; j++){
				cout << B[i][j] << " ";
			}
			cout << endl;
		}
		
		cout << fila_M1 << " x " << columnaM1_filaM2 << "  " << columnaM1_filaM2 << " x " << columna_M2 << "\t" << "\t" << tiempo << " segs." << endl;	         
              
        for(int e=0; e<fila_M1; e++){
            delete [] A[e];
        }
        delete [] A;
        
        for(int e=0; e<columna_M2; e++){
            delete [] B[e];
        }
        delete [] B; 
        
        for(int e=0; e<fila_M1; e++){
            delete [] C[e];
        }
        delete [] C;
        
        cout << endl;   
    }
    return 0;
}

int** multMatrizIterOpt(int** A, int** &B, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2){
    
    B = transponerMatriz(B, columnaM1_filaM2, columna_M2);
        
    for(int i=0; i<fila_M1; i++){
        for(int j=0; j<columna_M2; j++){
            C[i][j] = 0;
            for(int k=0; k<columnaM1_filaM2; k++){
                C[i][j] += A[i][k] * B[j][k];
            }
        }
    }    
    return C;
}

int** transponerMatriz(int** matriz, int filas, int columnas){
    int** matriz_trans = new int*[columnas];
    
    for(int i=0; i<filas; i++){
        matriz_trans[i] = new int[filas];
    }    
    
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            matriz_trans[j][i] = matriz[i][j];
        }
    }
    return matriz_trans;
}
