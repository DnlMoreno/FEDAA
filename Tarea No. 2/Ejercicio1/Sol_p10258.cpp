#include <bits/stdc++.h>

using namespace std;

int main(){

    ios_base::sync_with_stdio(0); cin.tie(0);

    int cases, contestant, problem, time;
    string letter, txt, line;

    unordered_map<int, vector<int> > dict;

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

                //int aux = dict.at(contestant)[1];
                //cout << aux << endl;
                //dict.at(contestant).pop_back();
                //dict.at(contestant).push_back(213);
                //dict[contestant].pop_back()

                cout << contestant << " " << problem  << " " << time << " " << letter << endl;

                if (letter == "C"){
                    if (dict.count(contestant) == 1){
                            if (dict.at(contestant)[0] == problem){
                                dict.at(contestant)[1]
                                dict[contestant] = vector<int> {problem, time};
                            }
                    }
                    else{
                        dict[contestant] = vector<int> {problem, time};
                    }

                    //if (dict.size() != 0)
                        //cout << "1.- Vector[0]" << "=>" << dict.at(contestant)[0] << endl;
                }
                if (letter == "I"){
                    if (dict.count(contestant) == 1){
                        dict[contestant] = vector<int> {problem, 20};
                    }
                    else{
                        dict[contestant] = vector<int> {problem, 20};
                    }
                }
                cout << "1.- Vector[0]" << "=>" << dict.at(contestant)[0] << endl;

                getline(cin,line);
            }
        }
    }

/*        cout << "For: " << i << endl;
        int it = 0;
        while(getline(cin,line)){
            cout << "While: " << it << endl;
            stringstream ss(line);
            ss >> contestant;
            ss >> problem;
            ss >> time;
            ss >> letter;

            cout << contestant << " " << problem  << " " << time << " " << letter << endl;


        }
    }

    for(auto x : dict){
        cout << " " << x.first << " => " << "[" << x.second[0] << "," << x.second[1] << "]" <<"\n";
    }*/

    cout << "----------------------------------------------------------" << endl;

    cout << "Vector[0]" << "=>" << dict.at(make_pair(contestant,problem))[0] << endl;
    cout << "Vector[1]" << "=>" << dict.at(make_pair(contestant,problem))[1] << endl;
    dict.at(make_pair(contestant,problem)).pop_back();
    dict.at(make_pair(contestant,problem)).push_back(213);
    cout << "Vector[0]" << "=>" << dict.at(make_pair(contestant,problem))[0] << endl;
    cout << "Vector[1]" << "=>" << dict.at(make_pair(contestant,problem))[1] << endl;

    cout << "----------------------------------------------------------" << endl;

    return 0;
}

