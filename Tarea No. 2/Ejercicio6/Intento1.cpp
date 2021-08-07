#include <bits/stdc++.h>

using namespace std;

int main(){

    ios_base::sync_with_stdio(0); cin.tie(0);
    int cases, n, tpo_ferry, m, tpo_llegada, tiempo, coches_subidos;
    string arrive, line;
    bool interruptor = false; // False significa que el ferry esta en el lado izquierdo
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

        cout << n << " " << tpo_ferry << " " << m << endl;

        for(int j = 0; j<m; j++){
            getline(cin,line);
            stringstream tt(line);
            tt >> tpo_llegada;
            tt >> arrive;

            // Para el lado izquierdo y derecho
            if(arrive == "left"){
                left.push(tpo_llegada);
            }
            else{
                right.push(tpo_llegada);
            }

            cout << tpo_ferry << " " << arrive << endl;
        }

        while(!left.empty() && !right.empty()){

            // El ferry esta en el lado izquierdo
            if (interruptor == false){
                if (tiempo >= left.front()){
                    if(left.size() != 0 && right.size() != 0){
                        if(right.front() < left.front()){ // En el caso de que tome autos en el lado derecho estando en el lado izquierdo
                            coches_subidos = 0;
                            for(int k = 0; k<n; k++){
                                if(tiempo >= right.front()){
                                    right.pop();
                                    coches_subidos ++;
                                }
                            }
                            tiempo += tpo_ferry;
                            for(int c = 0; c<coches_subidos; c++){
                                cout << tiempo << " " << endl;
                            }
                            // Sigue en el lado izquierdo
                        } // En el caso de que tome autos en el lado izquierdo estando ahi
                        else{
                            coches_subidos = 0;
                            tiempo += tpo_ferry;
                            for(int k = 0; k<n; k++){
                                if(tiempo >= left.front()){
                                    left.pop();
                                    coches_subidos ++;
                                }
                            }
                            tiempo += tpo_ferry;
                            for(int c = 0; c<coches_subidos; c++){
                                cout << tiempo << " " << endl;
                            interruptor = true; // EL ferry se encuentra en el lado derecho
                            }
                        }

                    }
                    else if(left.size() != 0 && right.size() == 0){
                        tiempo += tpo_ferry + left.front(); // Para llegar a la derecha
                    }
                    else if(left.size() == 0 && right.size() != 0){
                        tiempo += 2*tpo_ferry + left.front(); // Para llegar a la izquierda
                    }
                    else{ // Caso en que los dos sean 0
                        tiempo = 0; // REVISAAAAAAAR
                    }
                }
                else{
                    if(right.front() < left.front()){
                        tiempo += tpo_ferry;
                        interruptor = true;
                    }
                    else{
                        tiempo = left.front();
                    }
                }

            }

            // El ferry esta en el lado derecho
            else{
                if (tiempo >= right.front()){
                    if(left.size() != 0 && right.size() != 0){
                        if(right.front() < left.front()){ // En el caso de que tome autos en el lado derecho estando en el lado izquierdo
                            coches_subidos = 0;
                            for(int k = 0; k<n; k++){
                                if(tiempo >= right.front()){
                                    right.pop();
                                    coches_subidos ++;
                                }
                            }
                            tiempo += tpo_ferry;
                            for(int c = 0; c<coches_subidos; c++){
                                cout << tiempo << " " << endl;
                            }
                            // Sigue en el lado izquierdo
                        } // En el caso de que tome autos en el lado izquierdo estando ahi
                        else{
                            coches_subidos = 0;
                            tiempo += tpo_ferry;
                            for(int k = 0; k<n; k++){
                                if(tiempo >= left.front()){
                                    left.pop();
                                    coches_subidos ++;
                                }
                            }
                            tiempo += tpo_ferry;
                            for(int c = 0; c<coches_subidos; c++){
                                cout << tiempo << " " << endl;
                            interruptor = true; // EL ferry se encuentra en el lado derecho
                            }
                        }

                    }
                    else if(left.size() != 0 && right.size() == 0){
                        tiempo += tpo_ferry + left.front(); // Para llegar a la derecha
                    }
                    else if(left.size() == 0 && right.size() != 0){
                        tiempo += 2*tpo_ferry + left.front(); // Para llegar a la izquierda
                    }
                    else{ // Caso en que los dos sean 0
                        tiempo = 0; // REVISAAAAAAAR
                    }
                }
                else{
                    if(left.front() < right.front()){ // El otro lado poner right.front() < left.front()
                        tiempo += tpo_ferry;
                        interruptor = false;
                    }
                    else{
                        tiempo = right.front();
                    }
                }

            }
    /*
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
            */
        }

    }


    return 0;
}

