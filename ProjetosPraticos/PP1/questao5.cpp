#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

typedef unsigned int Vertex;

class DigraphAL{
private:
    unsigned int num_vertices, num_edges;
    std::list<Vertex> *adj;
public:
    DigraphAL(unsigned int);
    ~DigraphAL();
    void add_edge(Vertex, Vertex);
    void remove_edge(Vertex, Vertex);
    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
    std::list<Vertex> get_adj(Vertex v){return adj[v];}
};

DigraphAL::DigraphAL(unsigned int num_vertices): num_vertices(num_vertices),
                                                 num_edges(0){
    adj = new std::list<Vertex>[num_vertices];
}

DigraphAL::~DigraphAL(){
    for(unsigned int i=0; i<num_vertices; i++){
        adj[i].clear();
    }

    delete[] adj;
    num_vertices = num_edges = 0;
}

bool search_element_in_list(std::list<Vertex> lst, Vertex flag){
    for (auto elem:lst){
        if (elem == flag) return true;
    }
    return false;
}

void DigraphAL::add_edge(Vertex u, Vertex v){
    if (!search_element_in_list(adj[u], v) && u != v){
        adj[u].push_back(v);
        num_edges++;
        return;
    }
    return;
}

void DigraphAL::remove_edge(Vertex u, Vertex v){
    if (search_element_in_list(adj[u], v)){
        adj[u].remove(v);
        num_edges--;
    }
}

void display_list(std::list<Vertex> lst){
    for (auto elem: lst){
        std::cout << elem << ", ";
    }
    std::cout << std::endl;
}

void display_graph(DigraphAL &g){

    std::cout << "num_vertices:" << g.get_num_vertices() << std::endl;
    std::cout << "num_edges:" << g.get_num_edges() << std::endl;

    for (int v=0; v < g.get_num_vertices(); v++){
        std::cout<< v << ": ";display_list(g.get_adj(v));
    }
}

int main(){

    unsigned int num_vertices = 0, num_edges=0;

    std::cin >> num_vertices;
    std::cin >> num_edges;

    DigraphAL g{num_vertices};

    for(unsigned int i=0; i < num_edges; i++){
        Vertex u=0, v=0;
        std::cin >> u;
        std::cin >> v;
        g.add_edge(u, v);
    }

    display_graph(g);

}