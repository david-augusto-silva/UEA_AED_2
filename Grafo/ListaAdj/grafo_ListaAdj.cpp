// Grafo ListaAdj
#include <iostream>
#include <list>

using namespace std;

typedef unsigned int Vertex;

class ItemEdge{
public:
    unsigned int value;
    ItemEdge() {};
    ItemEdge(unsigned int value) : value(value){}
};

template<typename T>
class Graph{
private:
    unsigned int num_vertices=0;
    unsigned int num_edges=0;
    list<T> *adj; // vetor de list<T>
public:
    Graph(unsigned int);
    ~Graph();
    void add_edge(Vertex, Vertex);
    list<T> get_adj(Vertex v){return adj[v];}
    unsigned int get_num_vertices() { return num_vertices;}
    unsigned int get_num_edges() {return num_edges;}
};

template <typename T>
Graph<T>::Graph(unsigned int num_vertices):num_vertices(num_vertices), num_edges(0){
    adj = new list<T>[num_vertices];
}

template <typename T>
Graph<T>::~Graph(){
    for (unsigned int i =0; i<num_vertices; ++i){
        adj[i].clear(); // limpar cada lista
    }

    delete[] adj;
    adj = nullptr;
    num_vertices = num_edges = 0;

}

template <typename T>
void Graph<T>::add_edge(Vertex u, Vertex v){
    ItemEdge item_vetex_v{v};
    ItemEdge item_vetex_u{u};
    adj[u].push_back(item_vetex_v);
    adj[v].push_back(item_vetex_u);
    num_edges++;
}

// ----------------------------
template <typename T>
void input_graph(Graph<T> &g, unsigned int num_edges){
    Vertex u = 0;
    Vertex v = 0;
    for (unsigned int i=0; i<num_edges; ++i){
        cin >> u >> v;
        cout <<endl;
        cout << u << "--" << v;
    }
    g.add_edge(u, v);
}

template <typename T>
void display_graph(Graph<T> &g){
    for (auto v = 0; v < g.get_num_vertices(); v++){
        list<T> adj_v = g.get_adj(v);
        display_list(adj_v);
    }
    
}

template <typename T>
void display_list(list<T> lst){ // ItemVertex item_vertex : lst
    for (ItemEdge item_vertex : lst){
        cout << item_vertex.value << ", ";
    }
    cout << endl;
}

template <typename T>
void dsf(Graph<T> &g){
    
}

int main(){
    unsigned int vertices = 0;
    unsigned int edges = 0;
    
    cin >> vertices >> edges;
    cout << "num_vertices: " << vertices << endl;
    cout << "num_edges: " << edges << endl;
    
    Graph<ItemEdge> g{vertices};
    input_graph(g, edges);
    
    display_graph(g);
    return 0;    
}

// 9 12