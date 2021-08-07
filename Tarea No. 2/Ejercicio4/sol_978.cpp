#include <bits/stdc++.h>

using namespace std;

void batallaLemmings(priority_queue<int> &cola1, priority_queue<int> &cola2);

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    freopen("Entrada_problema.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int cases, num_battle, green, blue, aux;
    priority_queue<int> sg, sb;
 
    cin >> cases;

    for(int i=0; i<cases; i++){
        cin >> num_battle;
        cin >> green;
        cin >> blue;

        for(int j=0; j<green; j++){
            cin >> aux;
            sg.push(aux);
        }

        for(int j=0; j<blue; j++){
            cin >> aux;
            sb.push(aux);
        }

        for (int k=0; k<num_battle; k++){
            if (green > blue){
                for(int j=0; j<blue; j++){
                    batallaLemmings(sg, sb);
                }
            }
            else{
                for(int j=0; j<green; j++){
                    batallaLemmings(sg, sb);
                }
            }
            if(!sg.empty() || !sb.empty()) break;
        }

        if(sg.size() != 0) cout << "green wins" << endl;
        else if(sb.size() != 0) cout << "blue wins" << endl;
        else if(sg.size() == 0 && sb.size() == 0) cout << "green and blue died" << endl;

        cout << "Popping out elementsA...";
        while (!sg.empty())
        {
            cout << ' ' << sg.top();
            sg.pop();
        }

        cout << endl;
        cout << "Popping out elementsB...";
        while (!sb.empty())
        {
            cout << ' ' << sb.top();
            sb.pop();
        }

        cout << endl;


/*
        while(!sg.empty()){
            cout << sg.top() << endl;
            sg.pop();    
        }

        while(!sb.empty()){
            cout << sb.top() << endl;
            sb.pop();    
        }
*/
    }
    
    return 0;
}

void batallaLemmings(priority_queue<int> &cola1, priority_queue<int> &cola2){
    int battle = 0;
    if (cola1.top() > cola2.top()){
        battle = cola1.top() - cola2.top();
        cola1.pop();
        cola2.pop();
        cola1.push(battle); 
    }
    else if(cola1.top() == cola2.top()){
        cola1.pop();
        cola2.pop();
    }
    else{
        battle = cola2.top() - cola1.top();
        cola1.pop();
        cola2.pop();
        cola2.push(battle); 
    }
}