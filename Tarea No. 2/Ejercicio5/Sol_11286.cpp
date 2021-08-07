#include <bits/stdc++.h>

using namespace std;

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
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n_frosh, c1, c2, c3, c4, c5, aux, popular_cursos;
    string line;

    n_frosh = 1;
    while(true){
        unordered_map<vector<int>,int,VectorHasher> keyCursos;
        list<int> maximo(1,0);
        bool interruptor = false;
        getline(cin,line);
        stringstream ff (line);
        ff >> n_frosh;

        if (n_frosh == 0) break; // Condición de termino

        popular_cursos = 0;
        for(int i=0;i<n_frosh; i++){
            getline(cin,line);
            stringstream cc (line);
            cc >> c1;
            cc >> c2;
            cc >> c3;
            cc >> c4;
            cc >> c5;
            vector<int> cursos{c1,c2,c3,c4,c5};
            sort(cursos.begin(), cursos.end());

            if (keyCursos.count(cursos) == 1){
                keyCursos.at(cursos) += 1;
                if (keyCursos.at(cursos) >= maximo.front()){
                    maximo.push_front(keyCursos.at(cursos));
                    //interruptor = true;
                }
            }
            else{
                keyCursos[cursos] = 1;
                //maximo.push_front(keyCursos.at(cursos));
            }
        }

        aux = maximo.front();
        while(aux == maximo.front()){
            popular_cursos += maximo.front();
            maximo.pop_front();
        }

        cout << popular_cursos << endl;

        //if(interruptor == true) cout << maximo << endl;
        //else cout << n_frosh << endl;

    }

    return 0;
}
