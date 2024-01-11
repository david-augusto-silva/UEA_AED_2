#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>

typedef unsigned int Vertex;

// representa os MOVIMENTOS dos cavalos


class Graph{ 
private:
    unsigned int vertices, edges;
    std::list<Vertex> *adj;
    
public:
    Graph();
    ~Graph();
    void add_edge(Vertex, Vertex);
    unsigned int get_vertices(){return vertices;}
    unsigned int get_edges(){return edges;}
    std::list<Vertex> get_adj(Vertex v){return adj[v];}
    void adj_sort(Vertex );
    void bfs(Vertex);

};

Graph::Graph():vertices(8), edges(0){
    adj = new std::list<Vertex>[vertices];
}

Graph::~Graph(){
    for(int i=0; i<vertices; i++){
        adj[i].clear();
    }
    delete[] adj;
    vertices = edges = 0;
}

void Graph::adj_sort(Vertex u){
    std::vector<Vertex> aux{};
    for (auto i: adj[u]){
        aux.push_back(i);
    }

    Vertex temp;
    bool swap;

    int n = aux.size();

    for (int i=0; i < n; i++){
        swap=false;
        for(int j=0; j< n-i-1; j++){
            if (aux[j] > aux[j+1]){
                temp = aux[j];
                aux[j] = aux[j+1];
                aux[j+1] = temp;
                swap = true;
            }
        }
        if(!swap) break;
    }
    
    for(auto i:aux){
        adj[u].push_back(i);
    }

}

void Graph::add_edge(Vertex u, Vertex v){
    for(Vertex vert:adj[u]){
        if (vert == v) return;
    }

    adj[u].push_back(v);
    
    edges++;
}



int main(int argc, const char* argv[]){
    std::vector<const char*> input_cl{};
    for (int i=1; i<argc; i++){
        const char* str = argv[i];
        input_cl.push_back(str);
    }

    std::vector<int> input_graph{};
    for(auto elem:input_cl){
        input_graph.push_back(elem[0] - 'a');
        input_graph.push_back(elem[1] - '1');
    }



}