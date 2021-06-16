#include<iostream>
#include <algorithm>
#include<vector>

using namespace std;

void quickSort(vector<int> &v, int inicio, int final);
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
    
    quickSort(arr, 0, arr.size()-1);

    cout << endl;
    cout << "[ ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << "]" << endl;


    return 0;
}

void quickSort(vector<int> &v, int inicio, int final){
	if (inicio >= final){
		return;
	}
	
	int temp;
	int i = inicio;
	int j = final;
	int p = (inicio + final) / 2;
	int pivote = v[p];	
	
	while(true){
		while (v[i] <= pivote and i < final){
			i ++;
		}
		while (v[j] >= pivote and j > inicio){
			j --;
		}
		
		if (i < j){
			swap(v, j, i, temp);
/*			temp = v[i];
			v[i] = v[j];
			v[j] = temp;		*/	
		} else{
			break;
		}
	}
		
	if (p > i){
		swap(v, i, p, temp);
/*		temp = v[p];
		v[p] = v[i];
		v[i] = temp; */				
	} else if (p < j){
		swap(v, j, p, temp);
/*		temp = v[p];
		v[p] = v[j];
		v[j] = temp; */
	}
	
	if (inicio < j){
		quickSort(v, inicio, j);
	}
	if (i < final){
		quickSort(v, i, final);
	}
}

void swap(vector<int> &v, int valor1, int valor2, int temp){
    temp = v[valor2];
    v[valor2] = v[valor1];
    v[valor1] = temp;
}
