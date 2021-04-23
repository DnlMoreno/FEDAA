#include<iostream>
#include <algorithm>
#include<vector>

using namespace std;

void mergeSort(vector<int> &v, int pto_i, int pto_f);
void merge(vector<int> &v, int pto_i, int pto_f, int pto_medio);
void swap(vector<int> &v, int pto_i, int pto_f, int temp);

int main(){
    int n = 500;
    vector<int> arr(n);

    cout << endl;
    cout << "[ ";
    for(int i=0; i<n; i++){
        arr[i] = rand() % 2000;
        cout << arr[i] << " ";
    }
    cout << "]" << endl;

    int pto_i = 0;
    int pto_f = arr.size() -1;
    
    mergeSort(arr, pto_i, pto_f);
    
    cout << endl;
    cout << "[ ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << "]" << endl;

    return 0;
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

void swap(vector<int> &v, int valor1, int valor2, int temp){
    temp = v[valor2];
    v[valor2] = v[valor1];
    v[valor1] = temp;
}





