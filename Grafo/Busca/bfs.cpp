#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>

typedef unsigned int Vertex;

class Graph{ // Tabuleiro de xadrez
private:
    unsigned int vertices, edges;
    std::list<Vertex> *adj;
public:
    Graph(Vertex);
    ~Graph();
    void add_edge(Vertex, Vertex);
    unsigned int get_vertices(){return vertices;}
    unsigned int get_edges(){return edges;}
    std::list<Vertex> get_adj(Vertex v){return adj[v];}
    
    void bfs(Vertex);

};

Graph::Graph(Vertex v):vertices(v), edges(0){
    adj = new std::list<Vertex>[v];
}

Graph::~Graph(){
    for(int i=0; i<vertices; i++){
        adj[i].clear();
    }
    delete[] adj;
    vertices = edges = 0;
}

void Graph::add_edge(Vertex u, Vertex v){
    adj[u].push_back(v);
    edges++;
}

void Graph::bfs(Vertex s){
    std::vector<bool> visited{};
    visited.assign(vertices, false);

    std::queue<Vertex> Q{};
    Q.push(s);

    Vertex u;
    while (!Q.empty()){
        u = Q.front();
        Q.pop();

        

        for(Vertex ad:adj[u]){
            if (!visited[ad]){
                visited[ad] = true;
                Q.push(ad);
            }
        }
        
        std::cout << u << " ";
    }
}

int main(int argc, const char* argv[]){

    Graph g{4};

    g.add_edge(0,1);
    g.add_edge(0,2);
    g.add_edge(1,2);
    g.add_edge(2,0);
    g.add_edge(2,3);
    g.add_edge(3,3);

    g.bfs(2);
    return 0;

}

    