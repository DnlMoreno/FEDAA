#include <bits/stdc++.h>

using namespace std;

int main(){

    ios_base::sync_with_stdio(0); cin.tie(0);
    int cases, n, tpo_ferry, m, tpo_llegada, tiempo, coches_subidos;
    string arrive, line;
    bool interruptor; // False significa que el ferry esta en el lado izquierdo
    queue<int> left, right;

    getline(cin,line);
    stringstream ff (line);
    ff >> cases;

    //cout << cases << endl;

    for(int i = 0; i<cases; i++){
        getline(cin,line);
        stringstream ss(line);
        ss >> n;
        ss >> tpo_ferry;
        ss >> m;

        //cout << n << " " << tpo_ferry << " " << m << endl;

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

            //cout << tpo_llegada << " " << arrive << endl;
        }

        //cout << "-----------------------------------------------------------------" << endl;

        tiempo = 0;
        interruptor = false;
        while(!left.empty() || !right.empty()){

            // El ferry se encuentra en el lado izquierdo
            if (interruptor == false){
                if(left.size() != 0){
                    if (tiempo >= left.front()){ //Condicion que evalua si en la cola del lado izquierdo hay autos en el tiempo general del programa
                        coches_subidos = 0;
                        for(int k = 0; k<n; k++){
                            if(left.size() != 0 && tiempo >= left.front()){
                                left.pop();
                                coches_subidos ++;
                            }
                        }
                        tiempo += tpo_ferry;
                        for(int c = 0; c<coches_subidos; c++){
                            cout << tiempo << endl;
                        }
                        interruptor = true;
                    }

                    else{ //En el caso de que el tiempo general fuera menor que el tiempo en el que llegara un auto a la cola de la izquierda
                        if(right.size() != 0 && right.front() < left.front()){ //Se revisa cual a cual de las dos colas de las orillas del lago llegara primero un auto
                            tiempo = right.front();
                            tiempo += tpo_ferry;
                            interruptor = true;
                        }
                        else{
                            tiempo = left.front();
                            coches_subidos = 0;
                            for(int k = 0; k<n; k++){
                                if(left.size() != 0 && tiempo >= left.front()){
                                    left.pop();
                                    coches_subidos ++;
                                }
                            }
                            tiempo += tpo_ferry;
                            for(int c = 0; c<coches_subidos; c++){
                                cout << tiempo << endl;
                            }
                            interruptor = true;
                        }
                    }
                }
                else{ // Ya no llegaran mas auto en la cola izquierda y el ferry este en el lado izquierdo
                    if (!right.empty()){
                        if (right.front() <= tiempo){
                            tiempo += tpo_ferry;
                            interruptor = true;
                        }
                        else{
                            tiempo = right.front();
                            tiempo += tpo_ferry;
                            interruptor = true;
                        }
                    }
                }
            }
            // El ferry esta en el lado derecho
            else{
                if(right.size() != 0){
                    if (tiempo >= right.front()){
                        coches_subidos = 0;
                        for(int k = 0; k<n; k++){
                            if(right.size() != 0 && tiempo >= right.front()){
                                right.pop();
                                coches_subidos ++;
                            }
                        }
                        tiempo += tpo_ferry;
                        for(int c = 0; c<coches_subidos; c++){
                            cout << tiempo << endl;
                        }
                        interruptor = false;
                    }

                    else{ // VER QUE PASA SI INTENTO ACCEDER A UN ELEMENTO Y ES VACIO (CON LEFT.FRONT() POR EJEMPLO)
                        if(left.size() != 0 && left.front() < right.front()){
                            tiempo = left.front();
                            tiempo += tpo_ferry;
                            interruptor = false;
                        }
                        else{
                            tiempo = right.front();
                            coches_subidos = 0;
                            for(int k = 0; k<n; k++){
                                if(right.size() != 0 && tiempo >= right.front()){
                                    right.pop();
                                    coches_subidos ++;
                                }
                            }
                            tiempo += tpo_ferry;
                            for(int c = 0; c<coches_subidos; c++){
                                cout << tiempo << endl;
                            }
                            interruptor = false;
                        }
                    }
                }
                else{ // Ya no llegaran mas auto en la cola izquierda y el ferry este en el lado izquierdo
                    if (!left.empty()){
                        if (left.front() <= tiempo){
                            tiempo += tpo_ferry;
                            interruptor = false;
                        }
                        else{
                            tiempo = left.front();
                            tiempo += tpo_ferry;
                            interruptor = false;
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    return 0;
}


