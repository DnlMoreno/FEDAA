#include <bits/stdc++.h>

using namespace std;

void recorrido(queue<int>, int&);

int main(){

    ios_base::sync_with_stdio(0); cin.tie(0);
    int cases, n, tpo_ferry, m, tpo_llegada, tiempo, cont;
    string arrive, line;
    queue<int> left, right, ferry;

    getline(cin,line);
    stringstream ff (line);
    ff >> cases;

    cout << cases << endl;

    for(int i = 0; i<cases; i++){
        getline(cin,line);
        stringstream ss(line);
        ss >> n;
        ss >> tpo_ferry;
        ss >> m;

        cout << n << " " << tpo_llegada << " " << m << endl;

        cont = 0;
        while(cont < m){
            getline(cin,line);
            stringstream tt(line);
            tt >> tpo_llegada;
            tt >> arrive;

            if

            if(arrive == "left"){
                // Para el lado izquierdo
                for(int k=0; k<n; k++){
                    left.push(tpo_llegada);
                    cont ++;
                }
            }

            // Tiempo real
            recorrido(left, tiempo);

            // Para el lado derecho
            for(int k=0; k<n; k++){
                right.push(tpo_llegada);
                cont ++;
            }

            cout << tpo_llegada << " " << arrive << endl;
        }

        cout << "left contains: ";
        while (!left.empty()){
            cout << ' ' << left.front();
            left.pop();
        }
        cout << '\n';

        cout << "right contains: ";
        while (!right.empty()){
            cout << ' ' << right.front();
            right.pop();
        }
        cout << '\n';

        while()
    }

    return 0;
}

void recorrido(queue<int>, int&){


}
