#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<fstream>

using namespace std;

int** multMatIter(int**A, int** B, int** C, int fila_M1, int columnaM1_filaM2, int columna_M2);
void sum(int **A, int **B, int** &C, int n);
void subtract(int **A, int **B, int** &C, int n);
void generateMatrix(int fila, int columna, int fila_M1, ifstream &matrix, int **&Matrix);
int dimentionSquare(int fila, int columna);
void strassen(int** A, int** B, int** &C, int n);
void CreateMatrix(int n, int **Matrix);
void eliminarMatriz(int **matriz, int num_filas);

int main(int argc, char const *argv[]){
	int puntos, instancias, fila_M1, columnaM1_filaM2, columna_M2;
	ifstream matriz_A;
	ifstream matriz_B;
	
	matriz_A.open("C:/Users/gamor/Documents/GitHub/Fundamentos-Estructuras-de-Datos-y-Algoritmos/Informe n°1/Generación base de datos/Entradas algoritmos de multplicación de matrices/Entrada matriz_rect_A_caso4.txt");
	matriz_B.open("C:/Users/gamor/Documents/GitHub/Fundamentos-Estructuras-de-Datos-y-Algoritmos/Informe n°1/Generación base de datos/Entradas algoritmos de multplicación de matrices/Entrada matriz_rect_B_caso4.txt");

	matriz_A >> puntos;
	matriz_A >> instancias;
	
	matriz_B >> puntos;
	matriz_B >> instancias;
	
    for (int k=0; k<puntos; k++){
    	cout << "n  x  m    m  x  r" << "\t" << "\t" << "tiempo" << endl;	
    	matriz_A >> fila_M1;
    	matriz_A >> columnaM1_filaM2;
    	
		matriz_B >> columnaM1_filaM2;
		matriz_B >> columna_M2;
		
		double tiempoAcum = 0.0;
		int filaM1 = fila_M1;
		int columnaM2 = columna_M2;
		int columnaM1filaM2 = columnaM1_filaM2;
		int n;
		
		for(int h=0; h<instancias; h++){
			n = dimentionSquare(fila_M1, columnaM1_filaM2); 
			int **A = new int *[n];
			int **B = new int *[n];
			int **C = new int *[n];
			
			generateMatrix(filaM1, columnaM1filaM2, n, matriz_A, A);
			generateMatrix(columnaM1filaM2, columnaM2, n, matriz_B, B);
		
			CreateMatrix(n, C);
			unsigned t0 = clock();
			strassen(A, B, C, n);
			
			unsigned t1 = clock();
			double tiempo = (double)(t1 - t0)/CLOCKS_PER_SEC;
			
			cout << filaM1 << " x " << columnaM1filaM2 << "  " << columnaM1filaM2 << " x " << columnaM2 << "\t" << "\t" << tiempo << " segs.";
			
			for(int e=0; e<fila_M1; e++){
				delete [] A[e];
			}
			delete [] A;
			
			for(int e=0; e<columnaM1_filaM2; e++){
				delete[] B[e];
			}
			delete [] B; 
			
			for(int e=0; e<fila_M1; e++){
				delete [] C[e];
			}
			delete[] C;
			cout << endl;
		}
		
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
			//cout << C[i][j] << " ";
		}
		//cout << endl;
	}	
	return C;
}

void sum(int** A, int** B, int** &C, int n){
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

void subtract(int** A, int** B, int** &C, int n){
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

void generateMatrix(int fila, int columna, int fila_M1, ifstream &matrix, int** &Matrix){
	//cout << "fila: " << fila << " - columna: " << columna << endl;
	for (int k = 0; k < fila_M1; k++){
		Matrix[k] = new int[fila_M1];
	}
	for (int i = 0; i < fila; i++)
	{
		for (int j = 0; j < columna; j++)
		{
			matrix >> Matrix[i][j];
		}
	}
	for (int i = fila + 1; i < fila_M1; i++)
	{
		for (int j = columna + 1; i < fila_M1; i++)
		{ //n o n+1
			Matrix[i][j] = 0;
		}
	}
}

int dimentionSquare(int fila, int columna){
	double minimo = 999999;
	int vect[12] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
	//Matrices rectangulares max tamaÃ±o 4000
	int n = vect[0];
	int i = 0;
	int j = 0;
	int pos;

	if (fila == columna){
		return fila;
	}
	while (fila != columna){
		if (columna > fila){
			while (columna > n)
			{
				float absoluto = abs(columna - n);
				i = i + 1;
				n = vect[i];
				if (absoluto < minimo)
				{
					minimo = absoluto;
					pos = n;
				}
			}
			fila = pos;
			columna = pos;

		}
		if (columna < fila)
		{

			while (fila > n)
			{
				float absoluto = abs(fila - n);
				i = i + 1;
				n = vect[i];
				if (absoluto < minimo)
				{
					minimo = absoluto;
					pos = n;
				}
			}
			fila = pos;
			columna = pos;
		}
	}
	return fila;
}

void strassen(int **A, int **B, int** &C, int n){
	if (n == 1){
		C[0][0] += A[0][0] * B[0][0];
	}
	else{
		int newTam = n / 2; //fila = columna = n
		
		//Create matrices
		int **a11 = new int *[newTam];
		int **a12 = new int *[newTam];
		int **a21 = new int *[newTam];
		int **a22 = new int *[newTam];
		CreateMatrix(newTam, a11);
		CreateMatrix(newTam, a12);
		CreateMatrix(newTam, a21);
		CreateMatrix(newTam, a22);

		int **b11 = new int *[newTam];
		int **b12 = new int *[newTam];
		int **b21 = new int *[newTam];
		int **b22 = new int *[newTam];
		CreateMatrix(newTam, b11);
		CreateMatrix(newTam, b12);
		CreateMatrix(newTam, b21);
		CreateMatrix(newTam, b22);

		int **c11 = new int *[newTam];
		int **c12 = new int *[newTam];
		int **c21 = new int *[newTam];
		int **c22 = new int *[newTam];
		CreateMatrix(newTam, c11);
		CreateMatrix(newTam, c12);
		CreateMatrix(newTam, c21);
		CreateMatrix(newTam, c22);

		int **p1 = new int *[newTam];
		int **p2 = new int *[newTam];
		int **p3 = new int *[newTam];
		int **p4 = new int *[newTam];
		int **p5 = new int *[newTam];
		int **p6 = new int *[newTam];
		int **p7 = new int *[newTam];
		int **aResult = new int *[newTam];
		int **bResult = new int *[newTam];
		CreateMatrix(newTam, p1);
		CreateMatrix(newTam, p2);
		CreateMatrix(newTam, p3);
		CreateMatrix(newTam, p4);
		CreateMatrix(newTam, p5);
		CreateMatrix(newTam, p6);
		CreateMatrix(newTam, p7);
		CreateMatrix(newTam, aResult);
		CreateMatrix(newTam, bResult);

		//Dividing the matrices in 4 sub matrices
		for (int i = 0; i < newTam; i++)
		{
			for (int j = 0; j < newTam; j++)
			{
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

		sum(a21, a22, aResult, newTam);				// a21 + a22
		strassen(aResult, b11, p2, newTam); // p2 = (a21 + a22)*(b11)

		subtract(b12, b22, bResult, newTam);		//b12 - b22
		strassen(a11, bResult, p3, newTam); // p3 = (a11)*(b12 - b22)

		subtract(b21, b11, bResult, newTam);		//b21 - b11
		strassen(a22, bResult, p4, newTam); // p4 = (a22)*(b21 - b11)

		sum(a11, a12, aResult, newTam);				// a11 + a12
		strassen(aResult, b22, p5, newTam); // p5 = (a11 + a12)*(b22)

		subtract(a21, a11, aResult, newTam); //a21 - a11
		sum(b11, b12, bResult, newTam);		 // b11 + b12
		strassen(aResult, bResult, p6, newTam); // p6= (a21 - a11)*(b11 + b12)

		subtract(a12, a22, aResult, newTam); // a12 - a22
		sum(b21, b22, bResult, newTam);		 //b21 + b22
		strassen(aResult, bResult, p7, newTam); // p7 = (a12 - a22)*(b21 + b22)

		//Calculating c21, c12, c11 and c22
		sum(p3, p5, c12, newTam); // c12 = p3 + p5
		sum(p2, p4, c21, newTam); // c21 = p2 + p4

		sum(p1, p4, aResult, newTam); // p1 + p4
		sum(aResult, p7, bResult, newTam); // p1 + p4 + p7
		subtract(bResult, p5, c11, newTam); // c11 = p1 + p4 - p5 + p7

		sum(p1, p3, aResult, newTam); // p1 + p3
		sum(aResult, p6, bResult, newTam); // p1 + p3 + p6
		subtract(bResult, p2, c22, newTam); // c22 = pq + p3 - p2 + p6

		//Groupinh the results obtanined in single matrix
		for (int i = 0; i < newTam; i++){
			for (int j = 0; j < newTam; j++){
				C[i][j] = c11[i][j];
				C[i][j + newTam] = c12[i][j];
				C[i + newTam][j] = c21[i][j];
				C[i + newTam][j + newTam] = c22[i][j];
			}
		}
		
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
	}
}

void CreateMatrix(int n, int** Matrix){
	for (int i = 0; i < n; i++){
		Matrix[i] = new int[n];
	}
}

void eliminarMatriz(int **matriz, int num_filas){
	for (int e = 0; e < num_filas; e++)
	{
		delete[] matriz[e];
	}
	delete[] matriz;
}
