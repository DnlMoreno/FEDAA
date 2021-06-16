#include<iostream>
#include<ctime>
#include<algorithm>
#include<vector>
#include<conio.h>

using namespace std;

void selectionSort(vector<int> &v, int n);
//void swap(vector<int> &v, int i, int j, int n);

int main(){
    int n = 20;
    vector<int> arr(n);

    cout << endl;
    cout << "Comienzo Algoritmo" << endl;
    cout << "[ ";

    for(int i=0; i<n; i++){
        arr[i] = rand() % 30;
        cout << arr[i] << " ";
    }
    cout << "]" << endl;

    selectionSort(arr, n);
    
    cout << "[ ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << "]" << endl;

    return 0;
}

/* void selectionSort(vector<int> &v, int n){
    int aux;
    for(int i=0; i<n-1; i++){
        aux = v[i];
        for(int j=i+1; j<n; j++){
            if (aux > v[j]){
                aux = v[j];
            }
            v[j] = v[i];
            v[i] = aux;
        }
    }
} */

void selectionSort(vector<int> &v, int n){
    int min_index;
    for(int i=0; i<n-1; i++){
        min_index = i;
        for(int j=i+1; j<n; j++){
            if (v[min_index] > v[j]){
                min_index = j;
            }
        }
        int temp = v[min_index];
        v[min_index] = v[i];
        v[i] = temp;
    }
}


/* void swap(vector<int> &v, int i, int j, int n){
        v[i] = aux;
} */