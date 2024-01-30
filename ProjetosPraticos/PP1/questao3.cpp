#include <iostream>
#include <cstdint>
#include <vector>
#include <list>

typedef unsigned int Vertex;
typedef float Weight;

class WeightVertexPair{
public:
    Vertex vertex;
    Weight weight;

    WeightVertexPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight){};
};


class WeightedGraphAL{
private:
    unsigned int num_vertices, num_edges;
    std::list<WeightVertexPair> *adj;
public:
    WeightedGraphAL(unsigned int); //
    ~WeightedGraphAL();//
    void add_edge(Vertex, Vertex, Weight);//
    void remove_edge(Vertex, Vertex);

    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
    std::list<WeightVertexPair> get_adj(Vertex v){return adj[v];}
};

WeightedGraphAL::WeightedGraphAL(unsigned int num_vertices): num_vertices(num_vertices),
                                                             num_edges(0){
    adj = new std::list<WeightVertexPair>[num_vertices];
}

WeightedGraphAL::~WeightedGraphAL(){
    for(int i=0; i<num_vertices; i++){
        adj[i].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_vertices = num_edges = 0;
}

bool search_element_in_list(std::list<WeightVertexPair> lst, Vertex flag){
    for(auto elem:lst){
        if ((elem.vertex == flag)){
            return true;
        }
    }
    return false;
}

void WeightedGraphAL::add_edge(Vertex u, Vertex v, Weight w){
    WeightVertexPair v_vertex{v, w};
    WeightVertexPair u_vertex{u, w};

    if (!search_element_in_list(adj[v], u) || 
        !search_element_in_list(adj[u], v)){
    adj[v].push_back(u_vertex);
    adj[u].push_back(v_vertex);
    num_edges++;
    }
}

void WeightedGraphAL::remove_edge(Vertex u, Vertex v){
    
}


void display_list(std::list<WeightVertexPair> lst){
    for (auto elem: lst){
        std::cout << "(" << elem.vertex << ", " << elem.weight << "), ";
    }
    std::cout << std::endl;
}

void display_graph(WeightedGraphAL &g){

    std::cout << "num_vertices: " << g.get_num_vertices() <<std::endl;
    std::cout << "num_edges: " << g.get_num_edges() << std::endl;

    for(int i=0; i<g.get_num_vertices(); i++){
        std::cout << i << ": "; 
        display_list(g.get_adj(i));
    }
}

int main(){
    unsigned int num_vertices = 0, num_edges=0;
    
    std::cin >> num_vertices;
    std::cin >> num_edges;

    WeightedGraphAL g{num_vertices};

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