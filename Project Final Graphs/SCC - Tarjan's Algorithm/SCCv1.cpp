#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
#define NIL -1

using namespace std;

class Graph{
    int n;
    list<int> *adj;
    void SCCUtil(int u, int disc[], int low[], int &time,
                 bool stackMember[], stack<int> &stk);

public:
    Graph(int _n){
        n = _n;
        adj = new list<int>[n];
    }
    ~Graph() { delete[] adj; }
    void addEdge(int v, int w);
    void SCC();
};
void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}
/************SCCUtil parameter description:
 u ---> the next node to be visited
 disc ---->disc[u]The order of stored vertex u in depth-first traversal (stored is the time of discovery)
 low ----->low[u] stores the order of the ancestor with the smallest order that the u node can reach through its descendants or its own back edge 
 time ----> timestamp, it is quoted
 stackMember -----> What are the vertices marked into the stack, only the current node and its ancestors
 stk -------> stack, used to store the current node and its ancestors, when a strong connected component is found, the top element of the stack will exit,
	 Until the strong connected component is removed 
*/
void Graph::SCCUtil(int u, int disc[], int low[], int &time,
                    bool stackMember[], stack<int> &stk)
{
    disc[u] = low[u] = ++time;
    stk.push(u);
    stackMember[u] = true; //

    list<int>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); it++)
    {
        int v = *it;
        if (disc[v] == -1)
        {
            SCCUtil(v, disc, low, time, stackMember, stk);

            low[u] = min(low[u], low[v]);
        }
        else if (stackMember[v] == true) //v is the ancestor of u
        {
            low[u] = min(low[u], disc[v]); //It can be changed to low[u] = disc[v]
        }
    }

    int w = 0;
    if (low[u] == disc[u])     //Found a strong connected component,
    {                          //u is the root of the DFS subtree where the strong connected component is located
        while (stk.top() != u) //You can only use u as the root, not the entire stack
        {
            w = (int)stk.top();
            cout << w << " ";
            stackMember[w] = false;
            stk.pop();
        }
        w = (int)stk.top(); // u
        cout << w << " " << endl;
        stackMember[w] = false;
        stk.pop();
    }
}

void Graph::SCC()
{
    int *disc = new int[n];
    int *low = new int[n];
    bool *stackMember = new bool[n];
    stack<int> stk;
    int time = 0;

    for (int i = 0; i < n; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }

    for (int i = 0; i < n; i++)
        if (disc[i] == NIL) //disc also acts as a visited array, marking whether it has been visited
            SCCUtil(i, disc, low, time, stackMember, stk);
}
int main()
{
    cout << "\nSCCs in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.SCC();

    cout << "\nSCCs in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.SCC();

    cout << "\nSCCs in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.SCC();

    cout << "\nSCCs in fourth graph \n";
    Graph g4(11);
    g4.addEdge(0, 1);
    g4.addEdge(0, 3);
    g4.addEdge(1, 2);
    g4.addEdge(1, 4);
    g4.addEdge(2, 0);
    g4.addEdge(2, 6);
    g4.addEdge(3, 2);
    g4.addEdge(4, 5);
    g4.addEdge(4, 6);
    g4.addEdge(5, 6);
    g4.addEdge(5, 7);
    g4.addEdge(5, 8);
    g4.addEdge(5, 9);
    g4.addEdge(6, 4);
    g4.addEdge(7, 9);
    g4.addEdge(8, 9);
    g4.addEdge(9, 8);
    g4.SCC();

    cout << "\nSCCs in fifth graph \n";
    Graph g5(5);
    g5.addEdge(0, 1);
    g5.addEdge(1, 2);
    g5.addEdge(2, 3);
    g5.addEdge(2, 4);
    g5.addEdge(3, 0);
    g5.addEdge(4, 2);
    g5.SCC();

    return 0;
}