// Incluye todas las librerias STL necesarias para programación competitiva
#include <bits/stdc++.h>

using namespace std;

/*
Autor: Daniel Andrés Moreno Cartagena
Id_usuario: dnlmoreno
Sentencia de autoría: El codigo ha sido generado de manera personal
Análisis asintótico de la solución:
- Tiempo: El peor caso para el codigo es O(n), siendo n el tamano de la entrada. 
        Esto ya que en el codigo se usa solo la libreria de priority queue utilizando las funciones push, pop y top, las cuales tienen un tiempo de complejidad de O(log n), O(log n) y
        O(1) respectivamente. Por lo tanto, el tiempo queda condicionado por el tamaño de la entrada que es cuando se recorre el archivo completo en el primer while mas la cantidad
        de tasks que se tienen que hacer para imprimir la salida, quedando así, un tiempo en Big notation de O(n).
        ****tus consultas log(n) las haces por cada entrada, por lo que el costo es O(nlogn)*****

- Espacio: El peor caso para el codigo es O(n), siendo n el tamano de la entrada en unidades de bits. 
        Esto debido a que los valores de la entrada se guardaran en la priority queue como 3 enteros, lo cual ocupara un espacio de 3*n * 4 bytes + las otras variables de 4 bytes dentro
        del algoritmo. Por lo tanto, en Big notation, el numero total de espacio a ocupar por este algoritmo sera de O(n). 
*/

// La cola de prioridad se crea en base a esta estructura
struct Registro {
    int period;
    int q_num;
    int a1;

    // Inicializo las variables de la estructura
    Registro(int period, int q_num, int a1)
        : period(period), q_num(q_num), a1(a1)
    {
    }
};

// Estructura de comparacion para la cola de prioridad
// En primer lugar, se prioriza el menor periodo y en caso de empate, se prioriza el menor Q_num
struct comparator {
    bool operator()(Registro const& p1, Registro const& p2){
        if (p1.period < p2.period) return false; // Ordena segun el tiempo en orden creciente
        else if (p1.period > p2.period) return true;
        // En el caso de que el tiempo sea igual ordena segun el Q_num en orden creciente
        else{ 
            if (p1.q_num < p2.q_num) return false;
            else if (p1.q_num > p2.q_num) return true;
        }
    }
};


int main(){

    // Permite utilizar técnicas de I/O más rápidas. Logra que cin/cout obtengan la misma velocidad que scanf/printf
    // tie () es un método que garantiza el vaciado de cout antes de que cin acepte una entrada
    ios_base::sync_with_stdio(0); cin.tie(0);

    int q_num, period, task;
    priority_queue<Registro, vector<Registro>, comparator> query;
    string line, regist;

    // Se lee el archivo de entrada hasta el penultimo valor (#), ingresando los valores a la cola de prioridad
    while(true){
        getline(cin, line);
        stringstream ss(line);
        ss >> regist;
        if(regist == "#") break; // Se llego al penultimo valor del txt

        ss >> q_num;
        ss >> period;
        if(regist == "Register") query.push(Registro(period, q_num, period)); // Se ingrasan 3 valores, ya que el ultimo no se actualiza y permite saber el periodo inicial del registro
    }

    getline(cin, line);
    stringstream kk(line);
    kk >> task;

    for(int i=0; i<task; i++){
        // Se crea una variable aux que contenga el primer valor que hay en la cola de prioridad y se elimina el valor de la cola de prioridad
        Registro aux = query.top(); 
        query.pop();

        // Impresion de salida
        cout << aux.q_num << endl; 

        // Se vuelve a agregar el valor que se elimino, pero sumado con el periodo inicial de dicho valor
        query.push(Registro(aux.period + aux.a1, aux.q_num, aux.a1));
    }

    return 0;
}
