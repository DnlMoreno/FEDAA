#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <queue>
#include <unordered_map> 


using namespace std;

int main(int argc, char* argv[]){
    unordered_map<int, vector<pair<int, int>> > nivel;

    vector<int> vecinos = {1,2,3,4,5,6,7,8,9};
    vector<int> padres = {5,7,9,0,6,3,8,7,6};

    for(int i =0; i<vecinos.size(); i++){
        nivel[vecinos[i]].push_back(make_pair(padres[i],vecinos[i]));
        //nivel[vecinos[i]] = vector<pair<int, int>> {make_pair(padres[i],vecinos[i])};
    }
        
    //cout << "(" << nivel.at(3).size() << "," << nivel.at(5).size() << ")" <<endl;

    for(auto& x: nivel.at(3)){
        cout << "(" << x.first << "," << x.second << ")" <<endl;
        x.first = 21;
    }

    for(auto& x: nivel.at(3)){
        cout << "(" << x.first << "," << x.second << ")" <<endl;
    }

    for(int i =0; i<vecinos.size(); i++){
        nivel[vecinos[i]].push_back(make_pair(padres[i],vecinos[i]));
        //nivel[vecinos[i]] = vector<pair<int, int>> {make_pair(padres[i],vecinos[i])};
    }

    //cout << "(" << nivel.at(3).size() << "," << nivel.at(5).size() << ")" <<endl;

    for(auto& x: nivel.at(3)){
        cout << "(" << x.first << "," << x.second << ")" <<endl;
    }



    for (auto& x: nivel){
        cout << x.first << ": Tamaño vector: " << x.second.size() << endl;
        for(int i =0; i<x.second.size(); i++){
            cout << "(" << x.second[0].first << "," << x.second[0].second << ")" <<endl;
        }
    }

	return 0;
}