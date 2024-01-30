#include <iostream>
#include <list>

#include "grafo_LA.h"

using namespace std;

template <typename T>
void input_graph(Graph<T> &g, unsigned int num_edges){
    Vertex u=0, v=0;
    for (auto i=0; i<num_edges; ++i){
        cin >> u >> v;
        cout << endl;
        cout << u << "--" << v;
    }
    g.new_edge(u, v);
}

template<typename T>
void display_graph(Graph<T> &g){
    for (auto v=0; v < g.get_num_vertices(); v++){
        list<T> adj_v = g.get_adj(v);
        display_list(adj_v);
    }
}

template <typename T>
void display_list(list<T> lst){
    for (ItemEdge v:lst){
        cout << v.get_value() << ", ";
    }
    cout << endl;
}

int main(){
    unsigned int vertices = 0, edges = 0;

    cin >> vertices >> edges;
    cout << "Vertices: " << vertices << endl;
    cout << "Edges: " << edges << endl;

    Graph<ItemEdge> g{vertices};
    input_graph(g, edges);

    display_graph(g);
    return 0;
}