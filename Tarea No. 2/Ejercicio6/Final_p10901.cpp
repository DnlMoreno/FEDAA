// Incluye todas las librerias STL necesarias para programación competitiva
#include <bits/stdc++.h>

using namespace std;

/*
Autor: Daniel Andrés Moreno Cartagena
Id_usuario: dnlmoreno
Sentencia de autoría: El codigo ha sido generado de manera personal
Análisis asintótico de la solución:
- Tiempo: El peor caso para el codigo es O(n log n), siendo n el tamano de la entrada para cada caso respectivo. 
        Esto ya que en el codigo se utilizan dos librerias. La queue y el vector. En la primera se utilizan las funciones push, empty, front y size las cuales tienen un tiempo de complejidad
        de O(1). En la segunda se utiliza la funcion push_back, la cual en el peor caso puede tener un tiempo O(n), por si tiene que relocalizar el vector. Asimismo, a este vector
        se le aplica la funcion sort de la STL para ordenar todos los elementos que contiene, por ende el tiempo sera O(n log n), de acuerdo al tamaño de la entrada para cada caso respectivo.

- Espacio: El peor caso para el codigo es O(n), siendo n el tamano de la entrada en unidades de bits. 
        Esto debido a que los valores de la entrada se guardaran en dos queues como pares de enteros. Por ende, los valores ocuparan un espacio de 2*n * 4 bytes. Asimismo, los
        valores de salida se guardaran en un vector como pares de entero, pero a medida que se guarden en este vector, se iran eliminando de la cola respectiva, por ende, 
        el espacio ocupado se mantendra durante toda la ejecucion del programa. Por lo tanto, en Big notation, el numero total de espacio a ocupar por este algoritmo sera de O(n). 
*/

void transportarCars(queue<pair<int, int> > &cola, int &tiempo, int &tpo_ferry, vector< pair <int,int> > &llegada, bool &interruptor, int n);
void trasladoFerryVacio(int &tiempo, int &tpo_ferry);

int main(){

    // Permite utilizar técnicas de I/O más rápidas. Logra que cin/cout obtengan la misma velocidad que scanf/printf
    // tie () es un método que garantiza el vaciado de cout antes de que cin acepte una entrada
    ios_base::sync_with_stdio(0); cin.tie(0);

    int cases, n, tpo_ferry, m, tpo_llegada, tiempo;
    string arrive, line;
    bool interruptor; // False significa que el ferry esta en el lado izquierdo
    queue<pair<int, int> > left, right; // Colas de autos que se forman en el lado izquierdo y derecho

    getline(cin,line);
    stringstream ff (line);
    ff >> cases;

    for(int i = 0; i<cases; i++){
        getline(cin,line);
        stringstream ss(line);
        ss >> n;
        ss >> tpo_ferry;
        ss >> m;

        // Se lee la entrada para ese caso y se agregan los autos a su cola respectiva
        for(int j = 0; j<m; j++){
            getline(cin,line);
            stringstream tt(line);
            tt >> tpo_llegada;
            tt >> arrive;

            // Para el lado izquierdo y derecho
            if(arrive == "left"){
                left.push({j, tpo_llegada}); // j permite saber el orden de llegada de de los autos en el archivo de entrada
            }
            else{
                right.push({j, tpo_llegada});
            }
        }

        tiempo = 0; // Tiempo general
        interruptor = false; // comienza en el lado izquierdo
        vector< pair <int,int> > llegada; // Vector que guardara la salida. Guarda el orden de llegada y el tiempo en el que llego el auto al otro lado respectivamente
        while(!left.empty() || !right.empty()){

            // El ferry se encuentra en el lado izquierdo
            if (interruptor == false){
                if(left.size() != 0){

                    //Condicion que evalua si en la cola del lado izquierdo hay autos mientras el ferry esta en el lado izquierdo. Si hay autos, los transporta y pasa al lado derecho
                    if (tiempo >= left.front().second){
                        transportarCars(left, tiempo, tpo_ferry, llegada, interruptor, n);
                        interruptor = true;
                    }

                    else{ //En el caso de que aun no lleguen autos en el lado izquierdo

                        //Se revisa a cual de las dos colas de las orillas del lago llegara primero un auto
                        //En el caso de que llegue primero al lado derecho, se le suma el tiempo de traslado del ferry
                        if(right.size() != 0 && right.front().second < left.front().second){
                            if (tiempo < right.front().second) tiempo = right.front().second;
                            trasladoFerryVacio(tiempo, tpo_ferry);
                            interruptor = true;
                        }
                        else{ //En el caso de que llegue primero al lado izquierdo, el tiempo general sera el tiempo en el que llega el auto al lado izquierdo y luego se traslada al lado derecho
                            tiempo = left.front().second;
                            transportarCars(left, tiempo, tpo_ferry, llegada, interruptor, n);
                            interruptor = true;
                        }
                    }
                }

                // Ya no llegaran mas auto en la cola izquierda y el ferry esta en el lado izquierdo
                else{
                    if (!right.empty()){
                        // Por si un auto ya esta esperando en el lado derecho y el tiempo general es mayor
                        if (right.front().second <= tiempo){ 
                            trasladoFerryVacio(tiempo, tpo_ferry);
                            interruptor = true;
                        }
                        // En caso contrario, se iguala al tiempo en que llega el auto al lado derecho
                        else{
                            tiempo = right.front().second; // Tiempo en que llega el auto al lado derecho
                            trasladoFerryVacio(tiempo, tpo_ferry);
                            interruptor = true;
                        }
                    }
                }
            }

            // El ferry esta en el lado derecho
            else{
                if(right.size() != 0){

                    //Condicion que evalua si en la cola del lado derecho hay autos mientras el ferry esta en el lado derecho. Si hay autos, los transporta y pasa al lado izquierdo
                    if (tiempo >= right.front().second){
                        transportarCars(right, tiempo, tpo_ferry, llegada, interruptor, n);
                        interruptor = false;
                    }

                    else{//En el caso de que aun no lleguen autos al lado derecho

                        //Se revisa a cual de las dos colas de las orillas del lago llegara primero un auto
                        //En el caso de que llegue primero al lado izquierdo, se le suma el tiempo de traslado del ferry
                        if(left.size() != 0 && left.front().second < right.front().second){
                            if (tiempo < left.front().second) tiempo = left.front().second;
                            trasladoFerryVacio(tiempo, tpo_ferry);
                            interruptor = false;
                        }
                        else{ //En el caso de que llegue primero al lado derecho, el tiempo general sera el tiempo en el que llega el auto al lado derecho y luego se traslada al lado izquierdo
                            tiempo = right.front().second;
                            transportarCars(right, tiempo, tpo_ferry, llegada, interruptor, n);
                            interruptor = false;
                        }
                    }
                }

                // Ya no llegaran mas auto en la cola derecha y el ferry esta en el lado derecho
                else{
                    if (!left.empty()){
                        // Por si un auto ya esta esperando en el lado izquierdo y el tiempo general es mayor
                        if (left.front().second <= tiempo){
                            trasladoFerryVacio(tiempo, tpo_ferry);
                            interruptor = false;
                        }
                        // En caso contrario, se iguala al tiempo en que llega el auto al lado izquierdo
                        else{
                            tiempo = left.front().second; // Tiempo en que llega el auto al lado izquierdo
                            trasladoFerryVacio(tiempo, tpo_ferry);
                            interruptor = false;
                        }
                    }
                }
            }
        }
        // Se ordena el vector que contiene el orden de llegada de los autos junto con el tiempo al cual llegaron al otro lado
        sort(llegada.begin(), llegada.end());

        // Impresion del output
        for (int k=0; k<llegada.size(); k++){
            cout << llegada[k].second << endl;
        }
        if (i+1!=cases) cout << endl;
    }

    return 0;
}


void transportarCars(queue<pair<int, int> > &cola, int &tiempo, int &tpo_ferry, vector< pair <int,int> > &llegada, bool &interruptor, int n){
    /*** El ferry transporta de un lado a otro, de acuerdo a su capacidad, 
    la cantidad de autos que hay esperando en el lado en el cual se encuentra ***/

    // n es la capacidad del ferry
    for(int k = 0; k<n; k++){
        if(cola.size() != 0 && tiempo >= cola.front().second){
            llegada.push_back(make_pair(cola.front().first, tiempo+tpo_ferry)); // Se suben los coches con su correspondiente tiempo de llegada al otro lado
            cola.pop();
        }
    }
    tiempo += tpo_ferry;
}

void trasladoFerryVacio(int &tiempo, int &tpo_ferry){
    /* Ferry se traslada de forma vacia */
    tiempo += tpo_ferry;
}

