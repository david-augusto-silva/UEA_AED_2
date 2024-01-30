#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <cmath>

typedef unsigned int Vertex;
typedef float Weight;

class WeightedGraphAM{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    Weight **adj;
public:
    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
    Weight get_weight_edge(Vertex u, Vertex v){return adj[u][v];}
    
    std::list<Vertex> get_adj(Vertex );
    WeightedGraphAM(unsigned int);
    ~WeightedGraphAM();
    void add_edge(Vertex, Vertex, Weight);
    void remove_edge(Vertex, Vertex);
};

WeightedGraphAM::WeightedGraphAM(unsigned int num_vertices): num_vertices(num_vertices), 
                                                             num_edges(0){
    adj = new Weight*[num_vertices];
    for (int i=0; i<num_vertices; i++){
        adj[i] = new Weight[num_vertices];
        for (int j=0; j<num_vertices; j++){
            adj[i][j] = INFINITY;
        }
    }
}

WeightedGraphAM::~WeightedGraphAM(){
    for(int i=0; i<num_vertices; i++){
        delete[] adj[i];
    }
    delete[] adj;
    num_vertices = num_edges = 0;
}

void WeightedGraphAM::add_edge(Vertex u, Vertex v, Weight w){
    if (adj[u][v] == INFINITY && adj[v][u] == INFINITY){
        adj[u][v] = w;
        adj[v][u] = w;
        num_edges++;
    }
}

void WeightedGraphAM::remove_edge(Vertex u, Vertex v){
    adj[u][v] = INFINITY;
    adj[v][u] = INFINITY;
    num_edges--;
}

std::list<Vertex> WeightedGraphAM::get_adj(Vertex v){
    std::list<Vertex> return_adj{};
    for (unsigned int i=0; i<num_vertices; i++){
        if(!isinff(adj[i][v])){
            return_adj.push_back(i);
        }
    }
    return return_adj;
}

void display_graph(WeightedGraphAM &g){
    std::cout << "num_vertices: " << g.get_num_vertices() << std::endl;
    std::cout << "num_edges: " << g.get_num_edges() << std::endl;
    for (int u=0; u<g.get_num_vertices(); u++){
        for (int v=0; v<g.get_num_vertices(); v++){
            std::cout << g.get_weight_edge(u, v) << " ";
        }
        std::cout << std::endl;
    }
}

int main(){

    unsigned int num_vertices = 0, num_edges=0;
    
    std::cin >> num_vertices;
    std::cin >> num_edges;

    WeightedGraphAM g{num_vertices};

    for(unsigned int i=0; i < num_edges; i++){
        Vertex u=0, v=0;
        Weight w=0.0;
        std::cin >> u;
        std::cin >> v;
        std::cin >> w;
        g.add_edge(u, v, w);
    }

    display_graph(g);

}