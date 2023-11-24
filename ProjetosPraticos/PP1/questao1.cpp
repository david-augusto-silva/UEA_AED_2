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
    for(int i=0; i<num_vertices; i++){
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
    adj[u].push_back(v);
    adj[v].push_back(u);
    num_edges++;
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

    for(auto i=0; i<g.get_num_vertices(); i++){
        std::cout << "v[" << i << "]: ";
        std::list<Vertex> l_adj = g.get_adj(i);
        display_list(l_adj);
    }
}



int main(int argc, const char *argv[]){

    std::vector<unsigned int> input{};

    for (auto i=1; i<argc; i++){
        input.push_back(atoi(argv[i]));
    }
    unsigned int num_vertices = input[0], num_edges = input[1];

    GraphAL g{num_vertices};

    for (auto i=2; i<=num_edges*2; i+=2){
        g.add_edge(input[i], input[i+1]);
    }

    display_graph(g);

}