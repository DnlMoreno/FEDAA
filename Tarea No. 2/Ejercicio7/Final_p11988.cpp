// Incluye todas las librerias STL necesarias para programación competitiva
#include <bits/stdc++.h>

using namespace std;

/*
Autor: Daniel Andrés Moreno Cartagena
Id_usuario: dnlmoreno
Sentencia de autoría: El codigo ha sido generado de manera personal
Análisis asintótico de la solución:
- Tiempo: El peor caso para el codigo es O(n), siendo n el tamano de la entrada para cada caso. 
        Esto ya que en el codigo se utilizan las funciones begin, size, push_back e insert de la libreria list, las cuales tienen un tiempo de complejidad O(1), O(1), O(1) y O(n) respectivamente.
        Y posteriormente se itera sobre todos los caracteres de la lista dando un tiempo O(n) para cada caso. Por lo tanto, el tiempo en Big notation sera de O(n), de acuerdo al tamaño de la 
        entrada para cada caso respectivo.

- Espacio: El peor caso para el codigo es O(n), siendo n el tamano de la entrada en unidades de bits. 
        Esto debido a que los valores de la entrada por caso se guardaran en una lista enlazada de tipo char. Por ende, los valores ocuparan un espacio de n * 1 bytes. Por lo tanto, en 
        Big notation, el numero total de espacio a ocupar por este algoritmo sera de O(n). 
*/

int main(){
    // Permite utilizar técnicas de I/O más rápidas. Logra que cin/cout obtengan la misma velocidad que scanf/printf
    // tie () es un método que garantiza el vaciado de cout antes de que cin acepte una entrada
    ios_base::sync_with_stdio(0); cin.tie(0);

    string line;

    // Se itera hasta que se recorra todo el txt
    while(cin >> line){
        list<char> lista;
        list<char>::iterator it;
        bool home = false, fin = false;

        // Se recorre toda la linea de caracteres
        for(int i=0; i<line.size(); i++){

            // Las dos primeras condiciones permiten evaluar si se comenzara a escribir del principio o del final
            if (line[i] == '['){
                home = true;
                fin = false;
                it = lista.begin(); // Iterador en el elemento inicial de la lista
            }
            else if (line[i] == ']'){
                home = false;
                fin = true;
            }

            // Una vez que comiencen las letras, se escribe en donde quedo el cursor
            else{
                if(home==true){
                    lista.insert(it, line[i]); // Al comienzo se inserta una letra seguida de otra 
                }
                else if(fin==true){
                    lista.push_back(line[i]); // Las letras se insertan al final
                }

                // En el caso de que hubieran letras antes que "[" o "]"
                else{
                    lista.push_back(line[i]);
                }
            }
        }

        // Se itera sobre todo el texto limpio en el orden correspondiente
        for (auto& x: lista){
            cout << x << "";
        }
        cout << endl;
    }
    return 0;
}

