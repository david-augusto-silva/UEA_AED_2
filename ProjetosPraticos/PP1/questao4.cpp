#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <cmath>

// Entrada: 7 12 0 1 1.5 0 2 0.4 0 3 1.3 1 2 -2.5 1 4 1.4 3 2 3.1 3 6 1.3 2 4 -1.9 2 5 0.6 2 6 10.0 4 5 1.7 6 5 -2.8



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
    if (adj[u][v] == INFINITY && adj[v][u] == INFINITY)
        adj[u][v] = w;
        adj[v][u] = w;
        num_edges++;
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
    std::cout << "num_vertices:" << g.get_num_vertices() << std::endl;
    std::cout << "num_edges:" << g.get_num_edges() << std::endl;
    for (int u=0; u<g.get_num_vertices(); u++){
        for (int v=0; v<g.get_num_vertices(); v++){
            std::cout << g.get_weight_edge(u, v) << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, const char* argv[]){

    std::vector<float> input{};

    for(int i=1; i<argc; i++){
        input.push_back(atof(argv[i]));
    }

    unsigned int vertices = input[0],
                 edges = input[1];

    WeightedGraphAM g{vertices};

    for (int i=2; i<=edges*3; i+=3){
        g.add_edge(input[i], input[i+1], input[i+2]);
    }

    display_graph(g);

}