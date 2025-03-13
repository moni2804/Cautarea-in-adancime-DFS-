/*
 * Indexarea grafului sau a nodurilor am facut-o de la 1
 * In demo am verificat pe doua grafuri: unul care contine un ciclu si unul care nu contine niciun ciclu
 * in perf am facut ambele grafice
 * Am mai introdus comentarii prin cod pentru a fi mai usor de inteles ce face fiecare functie sau cum am verificat unele conditii
 * Am doua functii de dfs si dfs_visit: una pentru a afisa oridia de parcurgere dfs pentru grafurile din demo si una care nu afiseaza nimic pentru sortarea topologica si pentru perf
 *
 * Complexitati:
 * DFS: O(V+E)
 * Sortarea Topologica: O(V+E);
 * Tarjan: O(V+E)
 * initierea grafului si eliberarea(free) lui: O(V)
 * printarea listei: O(V+E)
 */
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include "Profiler.h"
using namespace std;

Profiler profiler;

enum{
    WHITE= 0,
    GREY,
    BLACK
};

typedef struct node {
    int key;
    node* adj[4500]; /// nr max de edge-uri
    int adj_size; ///nr de vecini
    int color;
}Node;

queue<Node*>q;
int ciclu=0; ///nu are cicluri

void dfs_visit( Node* start ,int &ciclu){
    start->color = GREY;

    for(int i = 0; i < start->adj_size; i++){
        if (start->adj[i]->color == WHITE){
            dfs_visit(start->adj[i],ciclu);
        }else if(start->adj[i]->color==GREY){
            ciclu=1; //avem cilcu
        }
        // inca un else in care verific daca da de un nod gri => NU poate sa fie sortat topologic
    }
    start->color = BLACK;
    cout<<start->key<<" "; ///afisarea parcurgerii dfs
    q.push(start);
    // punem in stack nodurile stack + daca nu o fost niciodata nod gri
    //poate mai trebuie afisat/augumentat
}
// V = nr noduri
void dfs(Node* list[], int V){
    for( int i = 1; i<= V; i++){
        if(list[i]->color == WHITE){
            dfs_visit(list[i],ciclu);
        }
    }
}

///initierea grafului
void init_graph(Node* graph[], int V) {
    for (int i = 1; i <= V; i++) {
        graph[i] = new Node();
        graph[i]->key = i;
        graph[i]->adj_size = 0;
        graph[i]->color = WHITE;
    }
}

///eliberarea grafului
void free_graph(Node* graph[], int V) {
    for (int i = 1; i <= V; i++) {
        delete graph[i];
    }
}

///afisarea listei de noduri
void print(node *graf[],int V){
    for(int i=1;i<V;i++){
        cout<<graf[i]->key<<" : ";
        for(int j=0;j<graf[i]->adj_size;j++){
            cout<<graf[i]->adj[j]->key<<" ";
        }
        cout<<endl;
    }

}


///o functie dfs fara afisare
void dfs_visit_without_print( Node* start ,int &ciclu, Operation &op){
    start->color = GREY;
    op.count();

    for(int i = 0; i < start->adj_size; i++){
        if (start->adj[i]->color == WHITE){
            op.count();
            dfs_visit_without_print(start->adj[i],ciclu,op);
        }else if(start->adj[i]->color==GREY){
            op.count();
            ciclu=1; //avem cilcu
        }
        // inca un else in care verific daca da de un nod gri => NU poate sa fie sortat topologic
    }
    start->color = BLACK;
    op.count();
    q.push(start);
    // punem in stack nodurile stack + daca nu o fost niciodata nod gri
    //poate mai trebuie afisat/augumentat
}

void dfs_without_print(Node* list[], int V,Operation &op){
    for( int i = 1; i<= V; i++){
        if(list[i]->color == WHITE){
            op.count();
            dfs_visit_without_print(list[i],ciclu,op);
        }
    }
}

void topological_sort(Node* graf[],int V,Operation &op){
    ciclu=0;
    ///golesc stack-ul
    while (!q.empty()){
        q.pop();
    }

    dfs_without_print(graf,V,op);

    if(ciclu==1){
        cout<<"Graful are ciclu, nu poate fi sortat topologic"<<endl;
    }else{
        while (!q.empty()){
            cout<<q.front()->key<<" ";
            q.pop();
        }
        cout<<endl;
    }

}

void tarjanDFS(Node* graf[], int u, int disc[], int low[], bool in_stack[], stack<Node*>& s, int& time_counter, vector<vector<int>>& scc) {
    disc[u] = low[u] = ++time_counter; ///initierea timpilor de descoperire si low-link

    s.push(graf[u]);
    in_stack[u] = true;

    ///vizitam vecinii nodurilor
    for (int i = 0; i < graf[u]->adj_size; i++) {
        Node* v = graf[u]->adj[i];

        if (disc[v->key] == -1) { ///vecin nevizitat sau neverificat
            tarjanDFS(graf, v->key, disc, low, in_stack, s, time_counter, scc);
            low[u] = min(low[u], low[v->key]);
        } else if (in_stack[v->key]) {
            low[u] = min(low[u], disc[v->key]);
        }
    }

    if (low[u] == disc[u]) {
        vector<int> currentSCC;
        int v;
        do {
            v = s.top()->key;
            s.pop();
            in_stack[v] = false;
            currentSCC.push_back(v);
        } while (v != u);
        scc.push_back(currentSCC);
    }
}

void tarjan(Node* graf[], int V) {
    int disc[4500];    // Discovery times
    int low[4500];     // Lowest discovery times
    bool in_stack[4500];
    stack<Node*> s;
    int time_counter = 0;
    vector<vector<int>> scc;

    ///am initializat vectorii declarati mai sus cu valorile initiale
    fill(disc, disc + V + 1, -1);
    fill(low, low + V + 1, -1);
    fill(in_stack, in_stack + V + 1, false);

    for (int i = 1; i <= V; i++) {
        if (disc[i] == -1) {
            tarjanDFS(graf, i, disc, low, in_stack, s, time_counter, scc);
        }
    }

    ///afisarea
    int counter=1;
    for (const auto& scc_it : scc) {
        cout<<counter++<<" : ";
        for (int node : scc_it) {
            cout << node << " ";
        }
        cout << endl;
    }
}


void demo(){
    int V=9; ///9 noduri de la 1 la 9
    Node* graf[4500];
    init_graph(graf, V); ///initializarea grafului
    Operation op_demo=profiler.createOperation("Demo",V); ///ca sa pot utiliza functiile pentru perf


    ///Am luat doua cazuri: daca am ciclu in graf si daca nu am ciclu
    //am ciclu
    vector<pair<int, int>> edges = {
            {1, 2},
            {2, 3},
            {3, 1},
            {1, 5},
            {1, 6},
            {1, 7},
            {1, 8},
            {1, 9}
    };
    ///am introdus muchiile in matricea sau lista din graf, mi-a fost mai usor sa o vad ca pe o matrice
    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;
        graf[u]->adj[graf[u]->adj_size++] = graf[v];
    }

    ///afisez graful la inceput
    print(graf,V);
    ///parcurgerea dfs
    cout<<endl<<"DFS:"<<endl;
    dfs(graf,V);
    ///sortarea topologica
    cout<<endl<<"Sortarea topologica: "<<endl;
    topological_sort(graf,V,op_demo);
    ///tarjan
    cout<<endl<<"Tarjan"<<endl;
    tarjan(graf,V);
    cout<<endl<<"-----------------------"<<endl;

    free_graph(graf, V);

    ///Al doilea graf
    ///nu am ciclu
    edges = {
            {1, 2},
            {2, 3},
            {3, 4},
            {1, 5},
            {5, 6},
            {6, 7},
            {7, 8},
            {8, 9}
    };
    init_graph(graf, V);
    ciclu=0; ///reinitiat flag-ul pentru cicluri

    ///introdus muchiile
    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;
        graf[u]->adj[graf[u]->adj_size++] = graf[v];
    }
    ///afisar graful initial
    print(graf, V);
    ///parcurgerea dfs
    cout<<endl<<"DFS"<<endl;
    dfs(graf, V);
    ///sortarea topologica
    cout<<endl<<"Sortarea topologica: "<<endl;
    topological_sort(graf,V,op_demo);
    ///tarjan
    cout<<endl<<"Tarjan"<<endl;
    tarjan(graf,V);
    free_graph(graf, V);


}

void perf(){
    ///numarul de varfuri ramane 100, iar numarul de muchii variaza
    int V=100;
    for(int E=1000;E<4500;E+=100){
        ///am 30 de teste pentru s fi mai dreapta linia din grafic
        for(int test=0;test<30;test++) {
            Node *graf[4500];
            init_graph(graf, V);

            Operation op_e = profiler.createOperation("Operatii muchiile variaza", E);

            ///introdus muchii random si am verificat daca nu am deja muchie intre nosuri prin conditia edge_set.find({u, v}) == edge_set.end()
            set<pair<int, int>> edge_set;
            int edges = 0;
            while (edges < E) {
                int u = rand() % V + 1;
                int v = rand() % V + 1;
                if (u != v && edge_set.find({u, v}) == edge_set.end()) {
                    graf[u]->adj[graf[u]->adj_size++] = graf[v];
                    edge_set.insert({u, v});
                    edges++;
                }
            }

            dfs_without_print(graf, V, op_e);

            free_graph(graf, V);
        }
    }

    ///numarul de muchii ramane 4500, iar numarul de varfuri variaza
    int E = 4500;
    for ( V = 100; V <= 200; V += 10) {
        ///am 30 de teste pentru s fi mai dreapta linia din grafic
        for(int test=0;test<30;test++) {
            Node *graf[4500];
            init_graph(graf, V);

            Operation op_v = profiler.createOperation("DFS numarul varfurilor variaza", V);

            ///introdus muchii random si am verificat daca nu am deja muchie intre nosuri prin conditia edge_set.find({u, v}) == edge_set.end()
            set<pair<int, int>> edge_set;
            int edges = 0;
            while (edges < E) {
                int u = rand() % V + 1;
                int v = rand() % V + 1;
                if (u != v && edge_set.find({u, v}) == edge_set.end()) {
                    graf[u]->adj[graf[u]->adj_size++] = graf[v];
                    edge_set.insert({u, v});
                    edges++;
                }
            }

            dfs_without_print(graf, V, op_v); // Perform DFS and count operations

            free_graph(graf, V);
        }

    }

    profiler.divideValues("DFS numarul varfurilor variaza",30);
    profiler.divideValues("Operatii muchiile variaza",30);
    profiler.showReport();
}


int main() {
    //demo();
    perf();
    return 0;
}