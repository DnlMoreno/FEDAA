#include <bits/stdc++.h>

using namespace std;

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

    int cases, contestant, problem, time;
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
        // La clave seran los concursantes y el vector guarda el concursante, los problemas resueltos y el tiempo
        unordered_map<int, vector<int> > received;
        unordered_map<int, vector<int> > scoring;
        priority_queue<Tripleta, vector<Tripleta>, comparator> output;

        //En el caso que la linea este vacia, para cambiar de caso
        if (line == ""){
            getline(cin,line);
            cout << endl;
            i++;
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
                    if (scoring.count(contestant) == 1){
                        scoring.at(contestant)[1] += 1;
                        scoring.at(contestant)[2] += time;
                    }
                    else{ // Se crea el primer problema resuelto por ese concursante
                        scoring[contestant] = vector<int> {contestant, 1, time};
                    }
                }

                else if (letter == "I"){
                    // En el caso de que exista la clave, se le suma 20 al tiempo de ese concursante
                    if (scoring.count(contestant) == 1){
                        scoring.at(contestant)[2] += 20;
                    }
                    else{ // Se crea la submission del concursante con un valor de tiempo 20
                        scoring[contestant] = vector<int> {contestant, 0, 20};
                    }
                }

                else if (letter == "R" || letter == "U" || letter == "E"){
                    // Si no existe la clave el problema se guarda en el mapa de problemas recibidos
                    if (scoring.count(contestant) == 0){
                        received[contestant] = vector<int> {contestant, 0, 0};
                    }
                }
                getline(cin,line);
            }
        }

        // Se ingresan los valores junto con ordenar por prioridad el caso iterado
        for(auto x : scoring){
            output.push(Tripleta(x.second[0], x.second[1], x.second[2]));

            // Se revisa si los concursantes ya enviaron una submission correcta o incorrecta, en ese caso, se elimina del map que contiene a los concursantes que sus
            // primeras respuestas habian estado en las cateogrias ('R', 'U' or 'E')
            if (received.count(x.first) == 1){
                received.erase(x.first);
            }

        }

        for(auto x : received){
            output.push(Tripleta(x.second[0], x.second[1], x.second[2]));
        }

        while (!output.empty()) {
            Tripleta p = output.top();
            output.pop();
            cout << p.cons << " " << p.prob << " " << p.tp << "\n";
        }

        // Salida de valores por casos
/*
        for(auto x : scoring){
            cout << x.first << " => " << "[" << x.second[0] << "," << x.second[1] << "," << x.second[2] << "]" <<"\n";
        }


        for(auto x : received){
            cout << x.first << " => " << "[" << x.second[0] << "," << x.second[1] << "," << x.second[2] << "]" <<"\n";
        }

        cout << "----------------------------------------------------------------------" << endl;
 */
    }

    return 0;
}

