#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <cmath>

typedef unsigned int Vertex;
typedef float Weight;

class Edge{
public:
    Weight weight;
    Edge(){};
    Edge(Weight w):weight(w){}
};

class WeightedDigraphAM{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    Edge **adj;
public:
    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
    Weight get_weight_edge(Vertex u, Vertex v){return adj[u][v].weight;}
    
    std::list<Vertex> get_adj(Vertex );
    WeightedDigraphAM(unsigned int);
    ~WeightedDigraphAM();
    void add_edge(Vertex, Vertex, Weight);
    void remove_edge(Vertex, Vertex);
    bool bellman_ford(Vertex);
};

WeightedDigraphAM::WeightedDigraphAM(unsigned int num_vertices):
num_vertices(num_vertices), num_edges(0){
    const unsigned int L = num_vertices, C = num_vertices;
    adj = new Edge*[L];
    for(int i=0; i<C; i++){
        adj[i] = new Edge[C]{INFINITY};
    }
}

WeightedDigraphAM::~WeightedDigraphAM(){
    for(int i=0; i<num_vertices; i++){
        delete[] adj[i];
    }
    delete[] adj;
    num_vertices=num_edges=0;
}

void WeightedDigraphAM::add_edge(Vertex u, Vertex v, Weight w){
    if (adj[u][v].weight == INFINITY){
        adj[u][v].weight = w;
    }
}