#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>

typedef unsigned int Vertex;

class GraphAL{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    std::list<Vertex> *adj;
public:
    GraphAL(unsigned int);
    ~GraphAL();
    void add_edge(Vertex, Vertex);
    void remove_edge(Vertex, Vertex);
    unsigned int get_num_vertices(){
        return num_vertices;
    }
    unsigned int get_num_edges(){
        return num_edges;
    }
    std::list<Vertex> get_adj(Vertex v){
        return adj[v];
    }

};

GraphAL::GraphAL(unsigned int num_vertices):num_vertices(num_vertices), 
                                            num_edges(0)
{
    adj = new std::list<Vertex>[num_vertices];
}

GraphAL::~GraphAL(){
    for(unsigned int i=0; i<num_vertices; i++){
        adj[i].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_vertices = num_edges = 0;
}

template<typename T>
bool find_element(std::list<T> lst, T flag){
    for(T elem:lst){
        if (elem == flag)
            return true;
    }
    return false;
}

void GraphAL::add_edge(Vertex u, Vertex v){
    if (!find_element(adj[u], v) || !find_element(adj[v], u)){
        adj[u].push_back(v);
        adj[v].push_back(u);
        num_edges++;
    }else{
        return;
    }
}

void GraphAL::remove_edge(Vertex u, Vertex v){
    if (find_element(adj[u], v) || find_element(adj[v], u)){
        adj[u].remove(v);
        adj[v].remove(u);
        num_edges--;
    }
}
// Auxiliares
template <typename T>
void display_list(std::list<T> lst){
    for(auto elem: lst){
        std::cout << elem <<", ";
    }
    std::cout << std::endl;
}

void display_graph(GraphAL &g){

    std::cout << "num_vertices: " << g.get_num_vertices() << std::endl;
    std::cout << "num_edges: " << g.get_num_edges() << std::endl;

    for(unsigned int i=0; i<g.get_num_vertices(); i++){
        std::cout << i <<": ";
        std::list<Vertex> l_adj = g.get_adj(i);
        display_list(l_adj);
    }
}



int main(){

    unsigned int num_vertices = 0, num_edges=0;

    std::cin >> num_vertices;
    std::cin >> num_edges;

    GraphAL g{num_vertices};

    for(unsigned int i=0; i < num_edges; i++){
        Vertex u=0, v=0;
        std::cin >> u;
        std::cin >> v;
        g.add_edge(u, v);
    }

    display_graph(g);

}