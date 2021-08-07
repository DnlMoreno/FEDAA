// Incluye todas las librerias STL necesarias para programación competitiva
#include <bits/stdc++.h>

using namespace std;

/*
Autor: Daniel Andrés Moreno Cartagena
Id_usuario: dnlmoreno
Sentencia de autoría: El codigo ha sido generado de manera personal
Análisis asintótico de la solución:
- Tiempo: El peor caso para el codigo es O(n), siendo n el tamano de la entrada.
        Esto ya que en el codigo se utilizan dos librerias. La queue y la slack. En la primera se utilizan las funciones push, pop, front y size, las cuales tienen un 
        tiempo O(1). En la segunda solo se utilizan las funciones push y top, las cuales tienen un tiempo O(1). Por lo tanto, el tiempo queda condicionado netamente
        por el tamaño de la entrada, al cual se le podria sumar el tiempo constante que se hace en la comparaciones del tren proviniente de la direccion A (comparador e input)
        y la estacion con la permutacion esperada (station y permutation), quedando así, un tiempo en Big notation de O(n).

- Espacio: El peor caso para el codigo es O(n), siendo n el tamano de la entrada en unidades de bits. 
        Esto debido a que los valores de la entrada se guardaran en los diferentes queue de manera separada, lo cual da una valor de n * 4 bytes + n * 4 bytes + n * 4 bytes 
        (input, pemutation y comparador), si los valores del input ingresan a la slack (estacion), estos seguiran manteniendo el mismo espacio ocupado, ya que se borraran del input 
        e ingresaran al slack, en cambio, si los valores del input ingresan al output (direccion B), el espacio ocupado ira disminuyendo en 4 bytes, ya que se borrara un valor del input y del 
        comparador, pero se agregara un valor al output. Por lo tanto, en Big notation, el numero total de espacio a ocupar por este algoritmo sera de O(n). 
*/

int main(){

    // Permite utilizar técnicas de I/O más rápidas. Logra que cin/cout obtengan la misma velocidad que scanf/printf
    // tie () es un método que garantiza el vaciado de cout antes de que cin acepte una entrada
    ios_base::sync_with_stdio(0); cin.tie(0);

    int coaches, aux, temp;
    cin >> coaches;

    // Cuando coaches sea 0 significa que se leyo la ultima linea del txt
    while(coaches != 0){
        // input viene en orden creciente, la permutation y comparador son el orden esperado de salida, y output el orden en que salieron los coaches
        // Se utiliza comparador, para trabajarlo con los coaches de entrada, en cambio, la permutation se utiliza para compararlo con los coaches del output
        queue<int> input, permutation, comparador, output; 
        stack<int> station;

        // Se rellenan el tren que viene en la direccion A y la permutacion esperada
        for(int i=1; i<=coaches; i++){
            cin >> aux;
            if (aux == 0) break; // Si aux es 0 significa que se cambio de caso

            input.push(i); //Tren de la direccion A
            permutation.push(aux); //Orden esperado en el archivo de entrada
            comparador.push(aux); //Orden esperado en el archivo de entrada
        }

        // Se agregan los coaches al output (direccion B) hasta que se obtenga la misma cantidad de coaches de entrada
        while(output.size() != coaches && aux != 0){

            // Condicion que compara el primer coach de entrada (que se encuentra en la cabeza en ese momento) con el primer coach esperado (que se encuentra en la cabeza en ese momento)
            if (input.size() != 0 && input.front() == comparador.front()){
                output.push(input.front()); //Tren direccion B
                comparador.pop();
                input.pop();
            }

            // Si el coach front de la entrada es distinto al coach front del comparador
            else if(input.size() != 0 && input.front() != comparador.front()){

                // Si en la estacion no hay coaches y el coach front de la entrada es distinto al coach front esperado (comparador), entonces pasa directo a la estacion
                if (station.size() == 0){
                    station.push(input.front());
                    input.pop();
                }

                // En caso contrario,...
                else{
                    // se compara el primer coach en el top de la pila con el coach front esperado en el comparador...
                    if (comparador.front() == station.top()){
                        output.push(station.top());
                        comparador.pop();
                        station.pop();
                    }
                    // si son distintos, entonces el coach front que viene en el input (direccion A) se agrega a la estacion
                    else{
                        station.push(input.front());
                        input.pop();
                    }
                }
            }

            // Si en el input (direccion A), ya que no quedan coaches, entonces todos los coaches de la estacion pasan al output (direccion B)
            if (input.size() == 0){
                while(!station.empty()){
                    output.push(station.top());
                    station.pop();
                }
            }
        }

        // Si aux no es 0 significa que aun no se ha salido del caso con n coaches
        if (aux != 0){ 
            temp = 0;

            // Se compara la salida obtenida (output) con la salida esperada (permutation)
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
            if (coaches != 0) cout << endl; // Condicion que dice que no es la ultima linea del archivo
        }
    }
    cout << endl;

    return 0;
}
