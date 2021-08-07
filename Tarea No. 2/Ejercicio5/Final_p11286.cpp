// Incluye todas las librerias STL necesarias para programación competitiva
#include <bits/stdc++.h>

using namespace std;

/*
Autor: Daniel Andrés Moreno Cartagena
Id_usuario: dnlmoreno
Sentencia de autoría: El codigo ha sido generado de manera personal
Análisis asintótico de la solución:
- Tiempo: El peor caso para el codigo es O(n), siendo n el tamano de la entrada. 
        Esto ya que en el codigo se utilizan dos librerias. Un unordered_map y un vector. En la primera solo se utiliza las funciones at y count, las cuales en el peor caso seran 
        el tamaño del mismo unordered_map que se este utilizando. Este caso ocurrira cuando su tabla hash este llena y deba expandirse (copiar todos los elementos) o bien en un 
        caso extremo cuando todas las entradas puedan terminar en el mismo cubo, lo que implicaria recorrer la lista enlazada de ese cubo, ya que el unordered_map de C++ se 
        implementa con encadenamiento lo que provoca un tiempo O(n) siendo n el tamano del unordered_map iterado, el cual podria ser el tamano de la entrada. Por el contrario,
        el vector solo utilizara un espacio fijo que guardara 5 cursos, siendo el constructor O(1). Ademas, se aplica la funcion sort de la STL al vector, la cual en este caso tendra un tiempo
        de O(5*log 5) lo que implica trabajo constante. Por lo tanto, en Big notation el tiempo de este algoritmo sera O(n).

- Espacio: El peor caso para el codigo es O(n), siendo n el tamano de la entrada en unidades de bits. 
        Esto debido a que los valores de la entrada se guardaran en la unordered_map como 6 enteros. El peor caso se daria cuando todas
        las combinaciones de los cursos fueran distintos, lo cual ocupara un espacio de 6*n * 4 bytes. Por el contrario, en la situación en la que no todas las combinacion de cursos fueran 
        distintas, no se guardaran los n elementos, ya que en ese caso solo se actualiza el valor de la popularidad, pero no se agrega otro elemento en el unordered_map.
        Por lo tanto, en Big notation, el numero total de espacio a ocupar por este algoritmo sera de O(n). 
*/

/*
La siguiente estructura fue extraída del siguiente sitio:
https://jimmy-shen.medium.com/stl-map-unordered-map-with-a-vector-for-the-key-f30e5f670bae
*/
// Estructura que permite utilizar un vector como llave en un unordered_map
struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

int main(){

    // Permite utilizar técnicas de I/O más rápidas. Logra que cin/cout obtengan la misma velocidad que scanf/printf
    // tie () es un método que garantiza el vaciado de cout antes de que cin acepte una entrada
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n_frosh, c1, c2, c3, c4, c5;
    string line;

    n_frosh = 1;
    while(true){
        unordered_map<vector<int>,int,VectorHasher> keyCursos; // Guardara como clave los cursos ordenados
        int maximo = 0, single = 0, mult = 1;
        bool interruptor=false;

        getline(cin,line);
        stringstream ff (line);
        ff >> n_frosh;

        if (n_frosh == 0) break; // Condicion de termino. Indica que ya no hay mas casos

        // Se itera por la cantidad del numero de frosh
        for(int i=0;i<n_frosh; i++){
            getline(cin,line);
            stringstream cc (line);
            cc >> c1;
            cc >> c2;
            cc >> c3;
            cc >> c4;
            cc >> c5;
            // Se guardan todos los cursos en un vector y luego se ordena el vector
            vector<int> cursos{c1,c2,c3,c4,c5};
            sort(cursos.begin(), cursos.end());

            // En el caso de que alguien ya hubiera inscritos los mismos cursos
            if (keyCursos.count(cursos) == 1){
                keyCursos.at(cursos) += 1;
                interruptor = true; // Significa que ya hay una combinacion de cursos repetidos

                // Se guarda el numero de estudiantes que tomaron la combinacion de cursos con mas popularidad
                if (keyCursos.at(cursos) > maximo){
                    maximo = keyCursos.at(cursos);
                    mult = 1;
                }
                // En el caso de que hubieran dos cursos o mas con la misma popularidad. Permite posteriormente, sumar la cantidad de cursos con mayor popularidad (multiplicando)
                // Dando como resultado el numero total de estudiantes que estan en esos cursos
                else if(keyCursos.at(cursos) == maximo){
                    mult += 1;
                }
            }

            // En el caso de que nadie hubiera inscrito esa combinacion de cursos todavia
            else{
                keyCursos[cursos] = 1;
                single += 1; // Variable que cuenta la cantidad de cursos que se inscriben, en el caso de que no se repitiera ningun curso
            }
        }

        // Imprime la combinacion de cursos con mayor popularidad
        // En el caso de que hubiera una combinacion de cursos repetidos
        if(interruptor == true){
            if (mult == 1) cout << maximo << endl;
            else cout << maximo*mult << endl;
        }
        // En el caso de que ninguna combinacion de cursos se repitiera, imprime la cantidad de estudiantes, ya que todos tomaron los cursos con la misma popularidad
        else cout << single << endl;
    }

    return 0;
}

