// Incluye todas las librerias STL necesarias para programación competitiva
#include <bits/stdc++.h>

using namespace std;

/*
Autor: Daniel Andrés Moreno Cartagena
Id_usuario: dnlmoreno
Sentencia de autoría: El codigo ha sido generado de manera personal
Análisis asintótico de la solución:
- Tiempo: El peor caso para el codigo es O(n), siendo n el tamano de la entrada. 
        Esto ya que en el codigo se utilizan dos librerias. La priority queue y el unordered_map. En la primera solo se utiliza la funcion push, siendo su complejidad O(log n).
        En la segunda se utilizan las funciones at, count y erase, las cuales en el peor caso seran el tamaño del mismo unordered_map que se este utilizando. Este caso ocurrira cuando
        su tabla hash este llena y deba expandirse (copiar todos los elementos) o bien en un caso extremo cuando todas las entradas puedan terminar en el mismo cubo, lo que 
        implicaria recorrer la lista enlazada de ese cubo, ya que el unordered_map de C++ se implementa con encadenamiento. Ademas de esto, al final del codigo se itera de manera
        separada cada uno de los elementos de los unordered_map lo que provoca un tiempo O(n) siendo n el tamano del unordered_map iterado, el cual podria ser el tamano de la entrada.
        ***Si haces push en la cola de prioridad por cada elemento de la entrada (n), tienes nlogn****

- Espacio: El peor caso para el codigo es O(n), siendo n el tamano de la entrada en unidades de bits. 
        Esto debido a que los valores de la entrada se guardaran en los diferentes unordered_map, por ende, cada uno por separado en el peor caso podria llegar a ocupar un espacio
        de O(n) elementos dentro de una estructura. Asimismo, la salida, la cual es una priority queue, contendra a todos los concursantes con sus respectivos tiempos y problemas resueltos, 
        de esta manera, el codigo puede llegar a tener las cincos estructuras simultaneas de esta forma: 3*n * 4 bytes + 3*n * 4 bytes + 3*n * 4 bytes + 3*c * 4 bytes (estructuras aux_solved, solved, output para n,) 
        (y estructuras incorrect y received para c), ya que cada uno almancena 3 enteros, siendo c una cantidad x de elementos de la entrada, pero no todos, ya que no todos pueden llegar a 
        guardar la cantidad total de datos de entrada, por lo tanto el numero total de espacio a ocupar en Big notation de este algoritmo sera de O(n)
*/

/*
La siguiente estructura fue extraída del siguiente sitio:
https://stackoverflow.com/questions/32685540/why-cant-i-compile-an-unordered-map-with-a-pair-as-key
*/
// Esta estructura permite utilizar pares en el unordered_map
struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

// La cola de prioridad se crea en base a esta estructura
struct Tripleta {
    int cons;
    int prob;
    int tp;

    // Inicializo las variables de la estructura
    Tripleta(int cons, int prob, int tp)
        : cons(cons), prob(prob), tp(tp)
    {
    }
};

// Estructura de comparacion para la cola de prioridad
// En primer lugar se prioriza la cantidad de problemas a resolver y en caso de empate, se prioriza el que tomo menos tiempo
struct comparator {
    bool operator()(Tripleta const& p1, Tripleta const& p2){
        if (p1.prob > p2.prob) return false; 
        else if (p1.prob < p2.prob) return true;
        else{
            if (p1.tp < p2.tp) return false; 
            else if (p1.tp > p2.tp) return true;
            else{
                if (p1.cons < p2.cons) return false;
                else if (p1.cons > p2.cons) return true;
            }
        }
    }
};

int main(){

    // Permite utilizar técnicas de I/O más rápidas. Logra que cin/cout obtengan la misma velocidad que scanf/printf
    // tie () es un método que garantiza el vaciado de cout antes de que cin acepte una entrada
    ios_base::sync_with_stdio(0); cin.tie(0);

    int cases, contestant, problem, time, num_problem, temp;
    string letter, line;

    getline(cin,line);
    stringstream casos(line);
    casos >> cases;

    //Pasa la primera linea en blanco
    getline(cin,line);
    getline(cin,line);

    int i = 0;
    while(i<cases){
        // Se crean los mapas dentro del while para que guarden valores por casos
        unordered_map<int, vector<int> > received; // key: concursante
        unordered_map<pair<int,int>, int, pair_hash> incorrect; //key: concursante, problema
        unordered_map<pair<int,int>, int, pair_hash> aux_solved; //key: concursante, problema
        unordered_map<int, vector<int> > solved; //key: concursante
        priority_queue<Tripleta, vector<Tripleta>, comparator> output; //cola que contendra a todos los concursantes que hicieron alguna submission

        //En el caso que la linea este vacia. Sirve para cambiar de caso.
        if (line == ""){
            getline(cin,line);
            i++;
            if(i!=cases) cout << endl;
        }
        else{
            while(line != ""){
                stringstream ss(line);
                ss >> contestant;
                ss >> problem;
                ss >> time;
                ss >> letter;

                if (letter == "C"){
                    // En el caso de que el concursante ya hubiera enviado un problema correcto e incorrecto
                    if (solved.count(contestant) == 1 && incorrect.count(make_pair(contestant,problem)) == 1){
                        // Si el concursante envia el mismo problema correcto, este no se suma al tiempo o problema
                        if (aux_solved.count(make_pair(contestant,problem)) != 1){
                            // Si el problema es el mismo que se encuentra en los incorrectos, se le suma la cantidad de veces incorrectas que tuvo el problema.
                            // Se le anade un problema a sus correctos
                            solved.at(contestant)[1] += time + incorrect.at(make_pair(contestant,problem));
                            solved.at(contestant)[0] += 1;
                            aux_solved[make_pair(contestant,problem)] = 0;
                            incorrect.erase(make_pair(contestant,problem));
                        }
                    } // Concursante ya habia envaido un problema, pero no estaba en los incorrectos
                    else if(solved.count(contestant) == 1 && incorrect.count(make_pair(contestant,problem)) != 1){
                        if (aux_solved.count(make_pair(contestant,problem)) != 1){
                            solved.at(contestant)[1] += time;
                            solved.at(contestant)[0] += 1;
                            aux_solved[make_pair(contestant,problem)] = 0;
                        }
                    } // Concursante envio el problema incorrecto anteriormente y no ha enviado ninguno correcto
                    else if(solved.count(contestant) != 1 && incorrect.count(make_pair(contestant,problem)) == 1){
                        solved[contestant] = vector<int> {1, time + incorrect.at(make_pair(contestant,problem))};
                        incorrect.erase(make_pair(contestant,problem));
                        aux_solved[make_pair(contestant,problem)] = 0;
                    }
                    else{ // Se crea el primer problema resuelto por ese concursante
                        solved[contestant] = vector<int> {1, time};
                        aux_solved[make_pair(contestant,problem)] = 0;
                    }
                }

                else if (letter == "I"){
                    // En el caso de que el concursante ya envio ese problema incorrecto se le suma 20 al tiempo
                    if (incorrect.count(make_pair(contestant,problem)) == 1){
                        incorrect[make_pair(contestant,problem)] += 20;
                    }
                    else{ // Primera vez que envia ese problema incorrecto
                        incorrect[make_pair(contestant,problem)] = 20;
                    }
                }

                else if (letter == "R" || letter == "U" || letter == "E"){
                    // Si no existe la clave el problema se guarda en el mapa de problemas recibidos
                    if (solved.count(contestant) == 0){
                        received[contestant] = vector<int> {0, 0};
                    }
                }
                getline(cin,line);
            }
        }

        // Se itera sobre los problemas incorrectos que quedaron para cada participante, con el fin de agregar a los concursantes que no enviaron ningun problema correcto
        // De esta forma los participantes hicieron submission, pero tienen tiempo y problemas resueltos 0
        for(unordered_map<pair<int,int>,int, pair_hash>::iterator it = incorrect.begin(); it != incorrect.end(); ++it){
            received[it->first.first] = vector<int> {0, 0};
        }

        // Se ingresan los valores y se ordenan por prioridad
        for(auto x : solved){
            output.push(Tripleta(x.first, x.second[0], x.second[1]));

            // Se revisa si los concursantes ya enviaron una submission correcta, de esta forma se deja en recibidos solo a los concursantes que no enviaron ningun problema correcto
            if (received.count(x.first) == 1){
                received.erase(x.first);
            }
        }

        // Ordena a los recibidos por el numero del concursante
        for(auto x : received){
            output.push(Tripleta(x.first, x.second[0], x.second[1]));
        }

        // Se imprime la salida de la cola que contiene a todos los concursantes que hicieron submission
        temp = output.size();
        while (!output.empty()){
            Tripleta p = output.top();
            output.pop();
            cout << p.cons << " " << p.prob << " " << p.tp;
            cout << endl;
        }
    }

    return 0;
}
