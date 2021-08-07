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

int main(){

    ios_base::sync_with_stdio(0); cin.tie(0);

    int cases, contestant, problem, time, aux_id;
    string letter, line;

    unordered_map<pair<int,int>, int, pair_hash> dict;
    unordered_map<int, vector<int> > resueltos;

    getline(cin,line);
    stringstream casos(line);
    casos >> cases;

    //Pasa la primera linea en blanco
    getline(cin,line);
    getline(cin,line);

    cout << "Casos: " << cases << endl;
    cout << "Linea: " << line << endl;

    int i = 0;
    while(i<cases){
        aux_id = 0;
        if (line == ""){
            getline(cin,line);
            i++;
        }
        else{
            while(line != ""){
                stringstream ss(line);
                ss >> contestant;
                ss >> problem;
                ss >> time;
                ss >> letter;

                cout << contestant << " " << problem  << " " << time << " " << letter << endl;

                if (letter == "C"){
                    // En el caso de que exista la clave
                    if (dict.count(make_pair(contestant,problem)) == 1){
                        dict[make_pair(contestant,problem)] += time;
                    }
                    else{ // Simplemente se crea
                        dict[make_pair(contestant,problem)] = time;
                    }
                }

                else if (letter == "I"){
                    // En el caso de que exista la clave
                    if (dict.count(make_pair(contestant,problem)) == 1){
                        dict[make_pair(contestant,problem)] += 20;
                    }
                    else{ // Simplemente se crea
                        dict[make_pair(contestant,problem)] = 20;
                    }
                }

                getline(cin,line);
            }
        }
    }

    for(unordered_map<pair<int,int>,int, pair_hash>::iterator it = dict.begin(); it != dict.end(); ++it){
        if (it->first.first != aux_id){
            cout << "{" << it->first.first << ", " << it->first.second << "}: " << it->second << endl;
        }
        aux_id = it->first.first;
    }

/*
    // My attempt on iteration
    for(auto it = dict.begin(); it != dict.end(); ++it){
        cout << it->first.first << "\n";
    }


    for(auto x : dict){
        cout << " " << x.first << " => " << x.second <<"\n";
    }
*/
    return 0;
}
