#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <cmath>

// Entrada: 4 7 0 1 -1.0 1 0 3.1 1 2 1.2 0 2 -1.0 0 3 0.0 3 0 1.4 3 2 6.4


typedef unsigned int Vertex;
typedef float Weight;

class WeightedDigraphAM{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    Weight **adj;
public:
    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
    Weight get_weight_edge(Vertex u, Vertex v){return adj[u][v];}
    
    std::list<Vertex> get_adj(Vertex );
    WeightedDigraphAM(unsigned int);
    ~WeightedDigraphAM();
    void add_edge(Vertex, Vertex, Weight);
    void remove_edge(Vertex, Vertex);
};

WeightedDigraphAM::WeightedDigraphAM(unsigned int num_vertices): num_vertices(num_vertices), 
                                                             num_edges(0){
    unsigned int LINES = num_vertices;
    unsigned int COLUMNS = num_vertices;
    adj = new Weight*[LINES];
    for (int i=0; i<LINES; i++){
        adj[i] = new Weight[COLUMNS];
        for (int j=0; j<COLUMNS; j++){
            adj[i][j] = INFINITY;
        }
    }
}

WeightedDigraphAM::~WeightedDigraphAM(){
    for(int i=0; i<num_vertices; i++){
        delete[] adj[i];
    }
    delete[] adj;
    num_vertices = num_edges = 0;
}

void WeightedDigraphAM::add_edge(Vertex u, Vertex v, Weight w){
    adj[u][v] = w;
    num_edges++;
}

void WeightedDigraphAM::remove_edge(Vertex u, Vertex v){
    adj[u][v] = INFINITY;
    num_edges--;
}

std::list<Vertex> WeightedDigraphAM::get_adj(Vertex v){
    std::list<Vertex> return_adj{};
    for (unsigned int i=0; i<num_vertices; i++){
        if(!isinff(adj[i][v])){
            return_adj.push_back(i);
        }
    }
    return return_adj;
}

void display_graph(WeightedDigraphAM &g){
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

    WeightedDigraphAM g{vertices};

    for (int i=2; i<=edges*3; i+=3){
        g.add_edge(input[i], input[i+1], input[i+2]);
    }

    display_graph(g);

}