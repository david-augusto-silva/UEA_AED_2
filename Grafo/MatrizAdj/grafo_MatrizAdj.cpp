#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

typedef unsigned int Vertex;
typedef unsigned int Weight;

class Edge{
public:
    Weight weight;
    Edge(){};
    Edge(Weight w): weight(w){};
};

class Graph{
private:
    unsigned int vertices;
    unsigned int edges;
    Edge **adj;
public:
    Graph(Vertex); // O
    ~Graph(); // O
    void create_edge(Vertex, Vertex); // 0
    void remove_edge(Vertex, Vertex);
    unsigned int get_vertices(){ return vertices;}
    unsigned int get_edges() {return edges;}
    std::list<Edge> get_adj(Vertex);
};

// Métodos da classe Graph
Graph::Graph(Vertex v): vertices(v), edges(0){
    adj = new Edge*[vertices];
    for (int i=0; i < vertices; i++){
        adj[i] = new Edge[vertices]{0};
    }
    std::cout<< "graph appears"<<std::endl;
}

Graph::~Graph(){
    for(int i=0; i<vertices; i++){
        delete[] adj[i];
    }
    delete[] adj;

    std::cout << "graph dies" << std::endl; 
}

void Graph::create_edge(Vertex u, Vertex v){
    Edge edge{1};
    adj[u][v] = edge;
    adj[v][u] = edge;
    edges++;
}

void Graph::remove_edge(Vertex u, Vertex v){
    if (u < (vertices) && v < vertices && (adj[u][v].weight != 0 && adj[v][u].weight != 0)){
        adj[u][v].weight = 0;
        adj[v][u].weight = 0;
        edges--;
        //std::cout << "Edge (" << u <<", "<<v<<") removed"<< std::endl;
    }
    //else{
    //    std::cout<< "edge does not exist" << std::endl;
    //    return;
    //}
}

std::list<Edge> Graph::get_adj(Vertex v){
    std::list<Edge> adj_r{};
    for (auto i=0; i<v; i++){
        if (adj[v][i].weight != 0){
            adj_r.push_back(i);
        }
    }
    return adj_r;
}

//Exibição

// Main
int main(int argc, char const *argv[]){
    std::vector<int> values{};
    for (int i = 1; i<argc; i++){
        values.push_back(std::atoi(argv[i]));
    }
   
    unsigned int num_vertices = values[0], num_edges = values[1];

    Graph g{num_vertices};  
    for(int i=2; i < (g.get_vertices())*2; i+=2){
        g.create_edge(values[i], values[i+1]);
    }

    std::list<Edge> list_vertices = g.get_adj(0);

    std::cout << list_vertices;
 
    g.remove_edge(0,1);
    g.remove_edge(8, 2);


    return 0;
}