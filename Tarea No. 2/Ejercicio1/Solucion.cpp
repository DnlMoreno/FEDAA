#include <bits/stdc++.h>

using namespace std;

// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};

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

// Estructura de comparación para la cola de prioridad
// En primer lugar se prioriza la cantidad de problemas a resolver y en caso de empate, se prioriza el que tomo menos tiempo
struct comparator {
    bool operator()(Tripleta const& p1, Tripleta const& p2){
        if (p1.prob > p2.prob) return false; // Si p1 hizo mas problema que p2, entonces esta ordenado
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

    ios_base::sync_with_stdio(0); cin.tie(0);

    int cases, contestant, problem, time, num_problem, temp;
    string letter, line;

    getline(cin,line);
    stringstream casos(line);
    casos >> cases;

    //Pasa la primera linea en blanco
    getline(cin,line);
    getline(cin,line);

    //cout << "Casos: " << cases << endl;

    int i = 0;
    while(i<cases){
        // Se crean los mapas dentro del while para que guarden valores por casos
        // La clave seran los concursantes y el vector guarda el concursante, problemas resueltos y el tiempo
        unordered_map<int, vector<int> > received;
        unordered_map<pair<int,int>, int, pair_hash> incorrect;
        unordered_map<int, vector<int> > solved;
        priority_queue<Tripleta, vector<Tripleta>, comparator> output;

        //En el caso que la linea este vacia, para cambiar de caso
        if (line == ""){
            getline(cin,line);
            i++;
            cout << endl;
        }
        else{
            while(line != ""){
                stringstream ss(line);
                ss >> contestant;
                ss >> problem;
                ss >> time;
                ss >> letter;

                //cout << contestant << " " << problem  << " " << time << " " << letter << endl;

                if (letter == "C"){
                    // En el caso de que el concursante ya hubiera enviado un problema
                    if (solved.count(contestant) == 1 && incorrect.count(make_pair(contestant,problem)) == 1){
                        // Si el problema es el mismo que se encuentra en los incorrectos, se le suma la cantidad de veces incorrectas que tuvo el problema
                        solved.at(contestant)[1] += time + incorrect.at(make_pair(contestant,problem));
                        solved.at(contestant)[0] += 1;
                        incorrect.erase(make_pair(contestant,problem));
                    }
                    else if(solved.count(contestant) == 1 && incorrect.count(make_pair(contestant,problem)) != 1){
                        solved.at(contestant)[1] += time;
                        solved.at(contestant)[0] += 1;
                    }

                    else if(solved.count(contestant) != 1 && incorrect.count(make_pair(contestant,problem)) == 1){
                        solved[contestant] = vector<int> {1, time + incorrect.at(make_pair(contestant,problem))};
                        incorrect.erase(make_pair(contestant,problem));
                    }
                    else{ // Se crea el primer problema resuelto por ese concursante
                        solved[contestant] = vector<int> {1, time};
                    }
                }

                else if (letter == "I"){
                    // En el caso de que exista la clave, se le suma 20 al tiempo de ese concursante
                    if (incorrect.count(make_pair(contestant,problem)) == 1){
                        incorrect[make_pair(contestant,problem)] += 20;
                    }
                    else{
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

        // Se ingresan los valores junto con ordenar por prioridad el caso iterado
        for(auto x : solved){
            output.push(Tripleta(x.first, x.second[0], x.second[1]));

            // Se revisa si los concursantes ya enviaron una submission correcta o incorrecta, en ese caso, se elimina del map que contiene a los concursantes que sus
            // primeras respuestas habian estado en las cateogrias ('R', 'U' or 'E')
            if (received.count(x.first) == 1){
                received.erase(x.first);
            }
        }

        for(unordered_map<pair<int,int>,int, pair_hash>::iterator it = incorrect.begin(); it != incorrect.end(); ++it){
            if (solved.count(it->first.first) != 1){
                output.push(Tripleta(it->first.first, 0, 0));
            }
        }

        for(auto x : received){
            output.push(Tripleta(x.first, x.second[0], x.second[1]));
        }

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

