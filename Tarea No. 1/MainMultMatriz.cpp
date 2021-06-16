#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<fstream>

using namespace std;

// Funciones generales
void lecturaFile(ifstream &matriz_A, ifstream &matriz_B);
void generarMatriz(int** &matriz, int filas, int columnas, ifstream &matriz_file);
void generarMatrizVacia(int** &matriz, int filas, int columnas);
void eliminarMatriz(int** &matriz, int num_filas);

// Funcion para matrices iterativa
int** multMatIter(int** A, int** B, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2);

// Funciones para matrices iterativa optimizada
int** multMatrizIterOpt(int** A, int** B, int** &B_tp, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2);
int** transponerMatriz(int** matriz, int** &matriz_trans, int filas, int columnas);

// Funciones para Strassen
int** strassen(int** A, int** B, int** C, int n);
void sum(int **A, int **B, int** C, int n);
void subtract(int **A, int **B, int** C, int n);
void addZero(int n, int m, int N, int **&Matrix);
int dimentionSquare(int fila, int columna);
int** createMatrix(int n, int m);
int max(int num1, int num2);

int main(int argc, char *argv[]){

	int puntos, instancias, fila_M1, columnaM1_filaM2, columna_M2, N, M, MAX;
	ifstream matriz_A; 
	ifstream matriz_B;
	
	ofstream salida;
    salida.open("Salida matriz Caso 2.txt", ios::out);
    
    lecturaFile(matriz_A, matriz_B);

// Para que vaya recorriendo los dos archivos a la par, pero los puntos e instancias son iguales
	matriz_A >> puntos;
	matriz_A >> instancias;
	matriz_B >> puntos;
	matriz_B >> instancias;
	
	// Lectura de todos los tamaños e instancias del txt
    for (int k=0; k<puntos; k++){
    	cout << "Tamano M1   Tamano M2" << "\t" << "\t" << "tiempoIter" << "\t" << "tiempoIterOpt" << "\t" << "tiempoStrassen" << endl;	
    	salida << "Tamano M1   Tamano M2" << "\t" << "\t" << "tiempoIter" << "\t" << "tiempoIterOpt" << "\t" << "tiempoStrassen" << endl;	
    	matriz_A >> fila_M1;
    	matriz_A >> columnaM1_filaM2;
    	
		matriz_B >> columnaM1_filaM2;
		matriz_B >> columna_M2;
		
		double tiempoAcumIter = 0.0;  
		double tiempoAcumOpt = 0.0; 
		double tiempoAcumStrassen = 0.0; 	
	
		for(int h=0; h<instancias; h++){
			// Se obtiene el numero 2^n mas cercano al cual tendra que redimensionarse la matriz de strassen
			N = dimentionSquare(fila_M1, columnaM1_filaM2); 
			M = dimentionSquare(columnaM1_filaM2, columna_M2); 
			MAX = max(N, M);			
			
			int** A = new int*[fila_M1];
			int** B = new int*[columnaM1_filaM2];
			
			// Se obtiene la matriz del archivo
			generarMatriz(A, fila_M1, columnaM1_filaM2, matriz_A);
			generarMatriz(B, columnaM1_filaM2, columna_M2, matriz_B);
						
			int** C_iter = createMatrix(fila_M1, columna_M2);
			int** B_tp = createMatrix(columna_M2, columnaM1_filaM2);
			int** C_opt = createMatrix(fila_M1, columna_M2);		
			
			int** A_strassen = createMatrix(MAX, MAX);
			int** B_strassen = createMatrix(MAX, MAX);
			int** C_strassen = createMatrix(MAX, MAX);
			
			// Se trapasan los datos de la matriz A y B a las matrices A_strassen y B_strassen
			for(int i=0; i<fila_M1; i++){
				for(int j=0; j<columnaM1_filaM2; j++){
					A_strassen[i][j] = A[i][j];
				}
			}	
			for(int i = 0; i<columnaM1_filaM2; i++){
				for(int j=0; j <columna_M2; j++){
					B_strassen[i][j] = B[i][j];
				}
			}
			
			// Se le agregan los 0 a la matriz de strassen
			addZero(fila_M1, columnaM1_filaM2, fila_M1, A_strassen);
			addZero(columnaM1_filaM2, columna_M2, fila_M1, B_strassen);
			
			// Evaluacion de los algoritmos
			unsigned t0 = clock();
			C_iter = multMatIter(A, B, C_iter, fila_M1, columnaM1_filaM2, columna_M2);
			unsigned t1 = clock();
			C_opt = multMatrizIterOpt(A, B, B_tp, C_opt, fila_M1, columnaM1_filaM2, columna_M2);
			unsigned t2 = clock();
			C_strassen = strassen(A_strassen, B_strassen, C_strassen, MAX);
			unsigned t3 = clock();

			double tiempoIter = (double)(t1 - t0)/CLOCKS_PER_SEC;
			double tiempoOpt = (double)(t2 - t1)/CLOCKS_PER_SEC;
			double tiempoStrassen = (double)(t3 - t2)/CLOCKS_PER_SEC;
			
			tiempoAcumIter += tiempoIter;
			tiempoAcumOpt += tiempoOpt;
			tiempoAcumStrassen += tiempoStrassen;
			
			cout << fila_M1 << " x " << columnaM1_filaM2 << "  " << columnaM1_filaM2 << " x " << columna_M2 << "\t" << "\t" << tiempoIter << "\t" << "\t" << tiempoOpt << "\t" << "\t" << tiempoStrassen << "\t" << "\t" << " segs." << endl;	
			salida << fila_M1 << " x " << columnaM1_filaM2 << "  " << columnaM1_filaM2 << " x " << columna_M2 << "\t" << "\t" << tiempoIter << "\t" << "\t" << tiempoOpt << "\t" << "\t" << tiempoStrassen << "\t" << "\t" << " segs." << endl;
			
			// Liberacion de memoria
			eliminarMatriz(A, fila_M1);
			eliminarMatriz(B, columnaM1_filaM2);
			eliminarMatriz(B_tp, columna_M2);
			eliminarMatriz(C_iter, fila_M1);	
			eliminarMatriz(C_opt, fila_M1);	
			eliminarMatriz(A_strassen, MAX);
			eliminarMatriz(B_strassen, MAX);
			eliminarMatriz(C_strassen, MAX);	
		}
		cout << "-----------------------------------------------------------------------------------------"<< endl;
		salida << "-----------------------------------------------------------------------------------------"<< endl;
		cout << "Promedio:" << "\t" << "\t" << "\t" << tiempoAcumIter/instancias << "\t" << "\t" << tiempoAcumOpt/instancias << "\t" << "\t" << tiempoAcumStrassen/instancias << "\t" << "\t" << " segs." << endl;			
		salida << "Promedio:" << "\t" << "\t" << "\t" << tiempoAcumIter/instancias << "\t" << "\t" << tiempoAcumOpt/instancias << "\t" << "\t" << tiempoAcumStrassen/instancias << "\t" << "\t" << " segs." << endl;
		cout << endl;
		cout << endl;
		salida << endl;	
		salida << endl;		
    }
   	
	return 0;	
}

// Funciones generales
void lecturaFile(ifstream &matriz_A, ifstream &matriz_B){
	// Para probar con las otras distribuciones de datos se debe ir cambiando el txt de entrada
	matriz_A.open("C:/Users/gamor/Documents/GitHub/FEDAA/Informe No. 1/Generación de datasets/Entrada algoritmos de multplicacion de matrices/Entrada matriz_cuad_A_caso2.txt");
	matriz_B.open("C:/Users/gamor/Documents/GitHub/FEDAA/Informe No. 1/Generación de datasets/Entrada algoritmos de multplicacion de matrices/Entrada matriz_cuad_B_caso2.txt");
}

void generarMatriz(int** &matriz, int filas, int columnas, ifstream &matriz_file){
// Funcion que genera matriz para el algoritmo de multplicación iterativo y el iterativo optimizado

    for (int i=0; i<filas; i++){
	matriz[i] = new int[columnas];	    	
    for (int j=0; j<columnas; j++){
        matriz_file >> matriz[i][j];            
    	}
	}
}

void eliminarMatriz(int** &matriz, int num_filas){
	for(int e=0; e<num_filas; e++){
		delete [] matriz[e];
	}
	delete [] matriz;
}


// Funcion para matriz iterativa
int** multMatIter(int** A, int** B, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2){	
// Multiplicación de matrices de manera convencional fila x columna
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


// Funciones para matriz iterativa optimizada
int** multMatrizIterOpt(int** A, int** B, int** &B_tp, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2){
	
	// Se transpone la matriz para conservar la localidad de los datos
	B_tp = transponerMatriz(B, B_tp, columnaM1_filaM2, columna_M2);
		
	// La multplicacion de matrices se realiza fila a fila 
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


// Funciones para matriz de Strassen.
// El codigo de la matriz de strassen se apoyo del codigo encontrado en https://martin-thoma.com/strassen-algorithm-in-python-java-cpp/
int** strassen(int **A, int **B, int** C, int n){
	// Caso base
	if (n == 1){
		return multMatIter(A, B, C, n, n, n);
	}
	else{
		int newTam = n / 2;
		
		// Se crean las matrices
		// Observación: Una forma de optimizar el codigo seria no crear todas estas matrices, si no que solo algunas para realizar los calculos, 
		// de esta forma se estaria ahorrando tiempo y memoria en cada llamada recursiva.
		int **a11 = createMatrix(newTam,newTam);
		int **a12 = createMatrix(newTam,newTam);
		int **a21 = createMatrix(newTam,newTam);
		int **a22 = createMatrix(newTam,newTam);

		int **b11 = createMatrix(newTam,newTam);
		int **b12 = createMatrix(newTam,newTam);
		int **b21 = createMatrix(newTam,newTam);
		int **b22 = createMatrix(newTam,newTam);

		int **c11 = createMatrix(newTam,newTam);
		int **c12 = createMatrix(newTam,newTam);
		int **c21 = createMatrix(newTam,newTam);
		int **c22 = createMatrix(newTam,newTam);

		int **p1 = createMatrix(newTam,newTam);
		int **p2 = createMatrix(newTam,newTam);
		int **p3 = createMatrix(newTam,newTam);
		int **p4 = createMatrix(newTam,newTam);
		int **p5 = createMatrix(newTam,newTam);
		int **p6 = createMatrix(newTam,newTam);
		int **p7 = createMatrix(newTam,newTam);
		
		// Se crean las matrices resultantes en reemplazo de las matrices de la S1 hasta la S9 del pseudocodigo del informe, para no crear tantas matrices en cada llamado recursivo
		// De esta forma el codigo es un poco mas eficiente
		int **aResult = createMatrix(newTam,newTam);
		int **bResult = createMatrix(newTam,newTam);

		// Se dividen las matrices en 4 sub-matrices
		for (int i = 0; i < newTam; i++){
			for (int j = 0; j < newTam; j++){
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + newTam];
				a21[i][j] = A[i + newTam][j];
				a22[i][j] = A[i + newTam][j + newTam];
				
				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + newTam];
				b21[i][j] = B[i + newTam][j];
				b22[i][j] = B[i + newTam][j + newTam];
			}
		}
		
		sum(a11, a22, aResult, newTam);	 // a11 + a22
		sum(b11, b22, bResult, newTam);	 // b11 + b22
		strassen(aResult, bResult, p1, newTam); // p1 = (a11 + a22)*(b11 + b22)

		sum(a21, a22, aResult, newTam);		// a21 + a22
		strassen(aResult, b11, p2, newTam); // p2 = (a21 + a22)*(b11)

		subtract(b12, b22, bResult, newTam); //b12 - b22
		strassen(a11, bResult, p3, newTam); // p3 = (a11)*(b12 - b22)

		subtract(b21, b11, bResult, newTam); //b21 - b11
		strassen(a22, bResult, p4, newTam); // p4 = (a22)*(b21 - b11)

		sum(a11, a12, aResult, newTam);		// a11 + a12
		strassen(aResult, b22, p5, newTam); // p5 = (a11 + a12)*(b22)

		subtract(a21, a11, aResult, newTam); //a21 - a11
		sum(b11, b12, bResult, newTam);		 // b11 + b12
		strassen(aResult, bResult, p6, newTam); // p6= (a21 - a11)*(b11 + b12)

		subtract(a12, a22, aResult, newTam); // a12 - a22
		sum(b21, b22, bResult, newTam);		 //b21 + b22
		strassen(aResult, bResult, p7, newTam); // p7 = (a12 - a22)*(b21 + b22)

		// Se calcula c21, c12, c11 y c22
		sum(p3, p5, c12, newTam); // c12 = p3 + p5
		sum(p2, p4, c21, newTam); // c21 = p2 + p4

		sum(p1, p4, aResult, newTam); // p1 + p4
		sum(aResult, p7, bResult, newTam); // p1 + p4 + p7
		subtract(bResult, p5, c11, newTam); // c11 = p1 + p4 - p5 + p7

		sum(p1, p3, aResult, newTam); // p1 + p3
		sum(aResult, p6, bResult, newTam); // p1 + p3 + p6
		subtract(bResult, p2, c22, newTam); // c22 = pq + p3 - p2 + p6

		// Se agrupan los resultados obtenidos en una unica matriz
		for (int i = 0; i < newTam; i++){
			for (int j = 0; j < newTam; j++){
				C[i][j] = c11[i][j];
				C[i][j + newTam] = c12[i][j];
				C[i + newTam][j] = c21[i][j];
				C[i + newTam][j + newTam] = c22[i][j];
			}
		}
		
		// Se libera la memoria
		eliminarMatriz(a11, newTam);
		eliminarMatriz(a12, newTam);
		eliminarMatriz(a21, newTam);
		eliminarMatriz(a22, newTam);

		eliminarMatriz(b11, newTam);
		eliminarMatriz(b12, newTam);
		eliminarMatriz(b21, newTam);
		eliminarMatriz(b22, newTam);

		eliminarMatriz(c11, newTam);
		eliminarMatriz(c12, newTam);
		eliminarMatriz(c21, newTam);
		eliminarMatriz(c22, newTam);

		eliminarMatriz(p1, newTam);
		eliminarMatriz(p2, newTam);
		eliminarMatriz(p3, newTam);
		eliminarMatriz(p4, newTam);
		eliminarMatriz(p5, newTam);
		eliminarMatriz(p6, newTam);
		eliminarMatriz(p7, newTam);
		
		eliminarMatriz(aResult, newTam);
		eliminarMatriz(bResult, newTam);
		
		return C;
	}
}

void sum(int** A, int** B, int** C, int n){
	// Funcion que suma dos matrices
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

void subtract(int** A, int** B, int** C, int n){
	// Funcion que resta dos matrices
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

void addZero(int n, int m, int N, int **&Matrix){
	// Funcion que añade los 0 a la matriz A y B de strassen para obtener una matriz de 2^n rellenada con 0
	 for (int i = 0 ; i < N; i++){
		 for (int j = m; j < N; j++){
		 Matrix[i][j] = 0;
		 }
	 }
	 for (int i = n; i < N; i++){
		 for (int j = 0; j < m; j++){
		 Matrix[i][j] = 0;
		 }
	 }
}

int dimentionSquare(int fila, int columna){
	// Funcion que devuelve el valor de la fila o columna de la matriz en forma del numero mas cercano de 2^n
	
	double minimo = 999999;
	int vect[12] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
	//Matrices rectangulares max tamaño 4000
	int n = vect[0];
	int i = 0;
	int j = 0;
	int pos;
	
	// Verifica si la dimension ya viene en potencia de 2^n
	for(int k = 0; k<12; k++){
		if (vect[k] == fila and fila == columna){
			return fila;
		}
	}
	
	if (columna >= fila){
		while (columna > n){
			float absoluto = abs(columna - n);
			i = i + 1;
			n = vect[i];
			if (absoluto < minimo){
				minimo = absoluto;
				pos = n;
				}
			}
		}
	if (columna < fila){
		while (fila > n){
			float absoluto = abs(fila - n);
			i = i + 1;
			n = vect[i];
			if (absoluto < minimo){
				minimo = absoluto;
				pos = n;
				}
			}
		}
	return pos;
}

int** createMatrix(int n, int m){
	// Funcion que crea una matriz
	
    int** newMatrix = new int*[n];
    for (int i = 0; i < n; i++){
        newMatrix[i] = new int[m];
    }
    return newMatrix;
}

int max(int num1, int num2) {
	// Devuelve el maximo valor de dos numeros
	int result;
	if (num1 > num2){
		result = num1;
   		} 
	else {
   		result = num2;
		}
   return result;
}	
