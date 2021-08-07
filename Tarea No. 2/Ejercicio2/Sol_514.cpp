#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int coaches, aux, temp;
    cin >> coaches;

    while(coaches != 0){
        queue<int> input, permutation, comparador, output;
        stack<int> station;

        for(int i=1; i<=coaches; i++){
            cin >> aux;
            //cout << aux << " ";
            if (aux == 0) break;

            input.push(i); //Tren de la direccion A

            permutation.push(aux); //Archivo de entrada
            comparador.push(aux);
        }
        //cout << endl;

        while(output.size() != coaches && aux != 0){
            if (input.size() != 0 && input.front() == comparador.front()){
                output.push(input.front()); //Tren direccion B
                comparador.pop();
                input.pop();
            }
            else{
                while(input.size() != 0 && input.front() != comparador.front()){
                    station.push(input.front());
                    input.pop();
                }
            }

            if (input.size() == 0){
                while(!station.empty()){
                    output.push(station.top());
                    station.pop();
                }
            }
        }

        if (aux != 0){
            temp = 0;
            for(int i=0; i<coaches; i++){
                if (output.front() != permutation.front()){
                    cout << "No" << endl;
                    break;
                }
                else{
                    temp++;
                    output.pop();
                    permutation.pop();
                    if(temp == coaches) cout << "Yes" << endl;
                }
            }
        }

        else{
            cin >> coaches;
            if (coaches != 0) cout << endl;
        }
    }

    return 0;
}
