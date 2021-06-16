#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<fstream>

using namespace std;

void bubbleSort(vector<int> &v, int n);
void swapBs(vector<int> &v, int j, int temp);

int main(int argc, char const *argv[]){
    int n = 500;
    vector<int> arr(n);

    cout << endl;
    cout << "[ ";
    for(int i=0; i<n; i++){
        arr[i] = rand() % 2000;
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
    
    bubbleSort(arr, n);
    
    cout << endl;
    cout << "[ ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << "]" << endl;

	return 0;
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
    temp = v[j];
    v[j] = v[j+1];
    v[j+1] = temp;
}


