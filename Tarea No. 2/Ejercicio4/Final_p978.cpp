// Incluye todas las librerias STL necesarias para programación competitiva
#include <bits/stdc++.h>

using namespace std;

/*
Autor: Daniel Andrés Moreno Cartagena
Id_usuario: dnlmoreno
Sentencia de autoría: El codigo ha sido generado de manera personal
Análisis asintótico de la solución:
- Tiempo: El peor caso para el codigo es O(n), siendo n el tamano de la entrada.
        Esto ya que en el codigo se utilizan dos librerias. La priority queue y la queue. En la primera se utilizan las funciones push, pop, top, size y empty, las cuales tienen un 
        tiempo de complejidad de O(log n), O(log n), O(1), O(1) y O(1) respectivamente. En la segunda se utilizan las funciones push, pop, front y empty, las cuales tienen un 
        tiempo de complejidad O(1). Por lo tanto, el tiempo queda condicionado al tamaño de la entrada + la cantidad de batallas hasta que un equipo se quede sin lemmings, dando
        de esta manera un tiempo de complejidad en Big notation de O(n)
        *****El costo de inserción y eliminación en las colas de prioridad se paga por cada lemming insertado, lo que es O(n), por lo que el costo será O(nlogn)*****

- Espacio: El peor caso para el codigo es O(n), siendo n el tamano de la entrada en unidades de bits. 
        Esto debido a que los valores de la entrada se guardaran en dos priority queue de manera separada, lo cual dara un espacio ocupado de n/2 * 4 bytes + n/2 * 4 bytes. Ademas,
        se utiliza una estructura queue que contendra los lemmings sobrevivientes eliminados de su equipo respectivo, por ende, el espacio ocupado en el algoritmo no aumentara, sino que
        ira disminuyendo gradualmente los lemmings vayan muriendo. Por lo tanto, en Big notation, el numero total de espacio a ocupar por este algoritmo sera de O(n). 
*/

void batallaLemmings(priority_queue<int> &cola1, priority_queue<int> &cola2, queue<pair<string,int> > &temp);
void sobrevivientes(priority_queue<int> &cola1, priority_queue<int> &cola2, queue<pair<string,int> > &temp);

int main(){
    // Permite utilizar técnicas de I/O más rápidas. Logra que cin/cout obtengan la misma velocidad que scanf/printf
    // tie () es un método que garantiza el vaciado de cout antes de que cin acepte una entrada
    ios_base::sync_with_stdio(0); cin.tie(0);

    int cases, num_battle, green, blue, aux;
    priority_queue<int> sg, sb; // Ordena los Lemmings de ambos equipos segun su ataque
    queue<pair<string,int> > temp; // Guarda a los lemming que sobrevivieron en los combates, para luego pasarlos a su equipo correspondiente
 
    cin >> cases;

    for(int i=0; i<cases; i++){
        cin >> num_battle;
        cin >> green;
        cin >> blue;

        // Se leen los lemmings de ambos equipos y se ordenan por prioridad
        for(int j=0; j<green; j++){
            cin >> aux;
            sg.push(aux); // Equipo verde
        }
        for(int j=0; j<blue; j++){
            cin >> aux;
            sb.push(aux); // Equipo azul
        }

        // Se itera hasta que ya no queden lemmings en alguno de los dos equipos
        while(!sg.empty() && !sb.empty()){
            // Se recorre segun el numero de batallas que habran
            for (int k=0; k<num_battle; k++){ 
                batallaLemmings(sg, sb, temp);
                if(sg.empty() || sb.empty()) break; // Si no quedan mas lemmings en un equipo se termina esa ronda de batalla
            }
            // Una vez terminada las batallas, se agregan los sobreviviente a sus respectivos equipós
            sobrevivientes(sg, sb, temp); 
        }

        // Se evalua a los ganadores. En este caso, si el tamano del verde es mayor significa que no quedan lemmings en el equipo azul, por la condicion de salida descrita en el while de arriba
        if(sg.size() > sb.size()){ 
            cout << "green wins" << endl;
            // Impresion de lemmings que sobrevivieron a la batalla
            while(!sg.empty()){
                cout << sg.top() << endl;
                sg.pop();    
            }
        }
        else if(sg.size() == sb.size()) cout << "green and blue died" << endl; // A ambos equipos no le quedan lemmings
        // En el caso de que el azul ganara
        else{
            cout << "blue wins" << endl;
            // Impresion de lemmings que sobrevivieron a la batalla
            while(!sb.empty()){
                cout << sb.top() << endl;
                sb.pop();    
            }
        }
        if (i+1 != cases) cout << endl;
    }
    return 0;
}

void batallaLemmings(priority_queue<int> &cola1, priority_queue<int> &cola2, queue<pair<string,int> > &temp){
    /*** Ocurre la batalla y se guarda al lemming del equipo ganador 
        en los sobrevivientes, en caso contrario, ambos murieron ***/

    int battle = 0;
    string ganador = "Empate";

    // Si el lemming del equipo cola1 es mas fuerte
    if (cola1.top() > cola2.top()){
        battle = cola1.top() - cola2.top();
        ganador = "Green";
        cola1.pop();
        cola2.pop();
        temp.push({ganador, battle}); // Se añade el sobreviviente junto con su nombre de equipo, para posteriormente traspasarlo a su equipo respectivo
    }
    else if(cola1.top() == cola2.top()){ // Ambos lemming mueren
        cola1.pop();
        cola2.pop();
    }
    // Si el lemming del equipo cola2 es mas fuerte
    else{
        battle = cola2.top() - cola1.top();
        ganador = "Blue";
        cola1.pop();
        cola2.pop();
        temp.push({ganador, battle}); 
    }
}

void sobrevivientes(priority_queue<int> &cola1, priority_queue<int> &cola2, queue<pair<string,int> > &temp){
    /*** Se traspasa a los lemmings sobrevivientes a sus equipos respectivos ***/

    while(!temp.empty()){
        if (temp.front().first == "Green"){
            cola1.push(temp.front().second);
            temp.pop();
        }
        else if (temp.front().first == "Blue"){
            cola2.push(temp.front().second);
            temp.pop();
        }
    }
}
