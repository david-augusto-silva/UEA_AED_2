#include <iostream>
#include <cstdint>
#include <vector>
#include <list>

// 7 12 0 1 1.5 0 2 0.4 0 3 1.3 1 2 -2.5 1 4 1.4 3 2 3.1 3 6 1.3 2 4 -1.9 2 5 0.6 2 6 10.0 4 5 1.7 6 5 -2.8

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

bool search_element_in_list(std::list<WeightVertexPair> lst, WeightVertexPair flag){
    for(auto elem:lst){
        if ((elem.vertex == flag.vertex) && (elem.weight == flag.weight)){
            return true;
        }
    }
    return false;
}

void WeightedGraphAL::add_edge(Vertex u, Vertex v, Weight w){
    WeightVertexPair v_vertex{v, w};
    WeightVertexPair u_vertex{u, w};

    if (!search_element_in_list(adj[v], u_vertex) && 
        !search_element_in_list(adj[u], v_vertex)){
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

    std::cout << "num_verices:" << g.get_num_vertices() <<std::endl;
    std::cout << "num_edges:" << g.get_num_edges() << std::endl;

    for(int i=0; i<g.get_num_vertices(); i++){
        std::cout << i << ": "; 
        display_list(g.get_adj(i));
    }
}

int main(int argc, const char* argv[]){
    std::vector<float> input{};
    for (auto i=1; i<argc; i++){
        input.push_back(atof(argv[i]));
    }

    unsigned int vertices = input[0], edges = input[1];

    WeightedGraphAL g{vertices};

    //adicionando arestas ao grafo
    for(int i=2; i<edges*3; i+=3){
        g.add_edge(input[i], input[i+1], input[i+2]);
    }

    display_graph(g);

}