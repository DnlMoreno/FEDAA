#include<iostream>
#include<ctime>
#include<algorithm>
#include<vector>
#include<conio.h>

using namespace std;

void insertionSort(vector<int> &v, int n);

int main(){
    int n = 20;
    vector<int> arr(n);

    cout << "[";
    for(int i=0; i<n; i++){
        arr[i] = rand() % 30;
        cout << arr[i] << " ";
    }
    cout << "]";

    insertionSort(arr, n);

    cout << "[";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << "]";

    return 0;
}

void insertionSort(vector<int> &v, int n){
    for(int i=1; i<n; i++){
        int aux = v[i];
        int j = i - 1;

        while(aux < v[j] && j >= 0){
            v[j+1] = v[j];
            j--;         
        }
        v[j+1] = aux;
    }        
}
