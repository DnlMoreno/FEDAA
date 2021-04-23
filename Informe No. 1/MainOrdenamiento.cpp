#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void lecturaFile(ifstream &file);
void bubbleSort(vector<int> &v, int n);
void swapBs(vector<int> &v, int j, int temp);
void mergeSort(vector<int> &v, int pto_i, int pto_f);
void merge(vector<int> &v, int pto_i, int pto_f, int pto_medio);
void quickSort(vector<int> &v, int inicio, int final);
void swap(vector<int> &v, int pto_i, int pto_f, int temp);

int main(int argc, char const *argv[]){

	int puntos, instancias, n;
	ifstream file;
	
	ofstream salida;
    salida.open("Salida datos valoresRepetidos.txt", ios::out);
	
	lecturaFile(file);
	
	file >> puntos;
	file >> instancias;
	
    for (int k=0; k<puntos; k++){
    	cout << "Tamano" << "\t" << "\t" << "tiempoBs" << "\t" << "tiempoMs" << "\t"  << "tiempoQs" << "\t" << "tiempoStl" << endl;	
    	salida << "Tamano" << "\t" << "\t" << "tiempoBs" << "\t" << "tiempoMs" << "\t"  << "tiempoQs" << "\t" << "tiempoStl" << endl;	
    	file >> n;
		double tiempoAcumBs = 0.0;
		double tiempoAcumMs = 0.0;
		double tiempoAcumQs = 0.0; 
		double tiempoAcumStl = 0.0;   
			
		for(int i=0; i<instancias; i++){
			vector<int> arrBubble(n);
			vector<int> arrMerge(n);
			vector<int> arrQuick(n);
			vector<int> arrStl(n);
			
			for(int j=0; j<n; j++){
				file >> arrBubble[j];
				arrMerge[j] = arrBubble[j];
				arrQuick[j] = arrBubble[j];
				arrStl[j] = arrBubble[j];
			}
			
			unsigned t0 = clock();
			bubbleSort(arrBubble, n);
			unsigned t1 = clock();
			mergeSort(arrMerge, 0, arrMerge.size()-1);
			unsigned t2 = clock();
			quickSort(arrQuick, 0, arrQuick.size()-1);
			unsigned t3 = clock();
			sort(arrStl.begin(), arrStl.end());
			unsigned t4 = clock();
			double tiempoBubble = (double)(t1 - t0)/CLOCKS_PER_SEC;
			double tiempoMerge = (double)(t2 - t1)/CLOCKS_PER_SEC;
			double tiempoQuick = (double)(t3 - t2)/CLOCKS_PER_SEC;
			double tiempoStl = (double)(t4 - t3)/CLOCKS_PER_SEC;
			tiempoAcumBs += tiempoBubble;
			tiempoAcumMs += tiempoMerge;
			tiempoAcumQs += tiempoQuick;
			tiempoAcumStl += tiempoStl;
			cout << n << "\t" << "\t" << tiempoBubble << "\t" << "\t" << tiempoMerge << "\t" << "\t" << tiempoQuick << "\t" << "\t" << tiempoStl << "\t" << "\t" << " segs." << endl;
			salida << n << "\t" << "\t" << tiempoBubble << "\t" << "\t" << tiempoMerge << "\t" << "\t" << tiempoQuick << "\t" << "\t" << tiempoStl << "\t" << "\t" << " segs." << endl;
		}
		cout << "-----------------------------------------------------------------------------------------"<< endl;
		salida << "-----------------------------------------------------------------------------------------"<< endl;
		cout << "Promedio:" << "\t" << tiempoAcumBs/instancias << "\t" << "\t" << tiempoAcumMs/instancias << "\t" << "\t" << tiempoAcumQs/instancias << "\t" << "\t" << tiempoAcumStl/instancias << "\t" << "\t" << " segs." << endl;			
		salida << "Promedio:" << "\t" << tiempoAcumBs/instancias << "\t" << "\t" << tiempoAcumMs/instancias << "\t" << "\t" << tiempoAcumQs/instancias << "\t" << "\t" << tiempoAcumStl/instancias << "\t" << "\t" << " segs." << endl;
		cout << endl;
		cout << endl;
		salida << endl;	
		salida << endl;	
	}
	return 0;
}

void lecturaFile(ifstream &file){
	// Para probar con las otras distribuciones de datos se debe ir cambiando el txt de entrada
	file.open("C:/Users/gamor/Documents/GitHub/Fundamentos-Estructuras-de-Datos-y-Algoritmos/Informe n°1/Generación base de datos/Entradas algoritmos de ordenamiento/Entrada datos valoresRepetidos.txt");
}

void bubbleSort(vector<int> &v, int n){
    int temp;
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            if(v[j] > v[j+1]){
                swapBs(v, j, temp);
            }
        }
    }
}

void swapBs(vector<int> &v, int j, int temp){
	// Función que hace el intercambio de valores en el algoritmo de BubbleSort
    temp = v[j];
    v[j] = v[j+1];
    v[j+1] = temp;
}

void mergeSort(vector<int> &v, int pto_i, int pto_f){
	int pto_medio, temp;
	
	// Casos bases para la recursividad
    if (pto_i >= pto_f){
    	return;
    }
    
    if ((pto_i + 1) == pto_f){
    	if (v[pto_i] > v[pto_f]){
        	swap(v, pto_i, pto_f, temp);
    	}
        return;
    }

    pto_medio = (pto_i + pto_f) / 2;

    // Recursividad, ordena la parte izquierda y derecha del vector
    mergeSort(v, pto_i, pto_medio);
    mergeSort(v, pto_medio + 1, pto_f);

    // Mezcla el vector derecho e izquierdo para obtener un vector ordenado
    merge(v, pto_i, pto_f, pto_medio);
}

void merge(vector<int> &v, int pto_i, int pto_f, int pto_medio){
	int i, j, k, tam_i, tam_f;
	
	// Tamaño de los vectores
	tam_i = pto_medio - pto_i + 1;
	tam_f = pto_f - pto_medio;
	
	// Vectores auxiliares 
	int aux_i[tam_i];
	int aux_f[tam_f];
	
	// Copia los valores en los vectores auxiliares
	for(int i=0; i<tam_i; i++){
		aux_i[i] = v[pto_i + i];
	}
	for(int j=0; j<tam_f; j++){
		aux_f[j] = v[pto_medio + 1 + j];
	}
	
	i = 0;
	j = 0;
	k = pto_i;
	
	// Realiza la comparacion de los valores de los vectores
    while (i < tam_i && j < tam_f) {
        if (aux_i[i] <= aux_f[j]) {
            v[k] = aux_i[i];
            i++;
        }
        else {
            v[k] = aux_f[j];
            j++;
        }
        k++;
    }
 
    // Copia los datos sobrantes del vector izquierdo
    while (i < tam_i) {
        v[k] = aux_i[i];
        i++;
        k++;
    }
 
    // Copia los datos sobrantes del vector derecho
    while (j < tam_f) {
        v[k] = aux_f[j];
        j++;
        k++;
    }
}	

void quickSort(vector<int> &v, int inicio, int final){
	// Caso en el que se entrega el vector ya ordenado, o se ingresa mal el valor menor del vector
	if (inicio >= final){
		return;
	}
	
	int temp;
	int i = inicio;
	int j = final;
	int p = (inicio + final) / 2;
	int pivote = v[p];	
	
	// Se va evaluando el pivote con los elementos del lado derecho e izquierdo, para ir cambiando estos entre si
	while(true){
		while (v[i] <= pivote and i < final){
			i ++;
		}
		while (v[j] >= pivote and j > inicio){
			j --;
		}
		
		if (i < j){
			swap(v, j, i, temp);
		} else{
			break;
		}
	}
	
	// Se ubica el pivote de manera que queden los menores del pivote a la izquierda y los mayores a la derecha
	if (p > i){
		swap(v, i, p, temp);			
	} else if (p < j){
		swap(v, j, p, temp);
	}
	
	// Recursividad del Quick Sort, se ordena el subvector izquierdo y derecho
	if (inicio < j){
		quickSort(v, inicio, j);
	}
	if (i < final){
		quickSort(v, i, final);
	}
}

void swap(vector<int> &v, int valor1, int valor2, int temp){
	// Función que hace el intercambio de valores en el algoritmo de MergeSort y QuickSort
    temp = v[valor2];
    v[valor2] = v[valor1];
    v[valor1] = temp;
}

