#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

//entrada: 4 7 0 1 -1.0 1 0 3.1 1 2 1.2 0 2 -1.0 0 3 0.0 3 0 1.4 3 2 6.4

typedef unsigned int Vertex;
typedef float Weight;

class VertexWeightPair{
public:
    Weight weight;
    Vertex vertex;
    VertexWeightPair(Vertex v, Weight w): vertex(v), weight(w){}
};

class WeightedDigraphAL{
private:
    unsigned int num_vertices,
                 num_edges;
    std::list<VertexWeightPair> *adj;
public:
    WeightedDigraphAL(unsigned int);
    ~WeightedDigraphAL();
    void add_edge(Vertex, Vertex, Weight);
    void remove_edge(Vertex, Vertex);

    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
    std::list<VertexWeightPair> get_adj(Vertex v){return adj[v];}
};

WeightedDigraphAL::WeightedDigraphAL(unsigned int num_vertices):num_vertices(num_vertices),
                                                                num_edges(0){
    adj = new std::list<VertexWeightPair>[num_vertices];
}

WeightedDigraphAL::~WeightedDigraphAL(){
    for (int i=0; i<num_vertices; i++){
        adj[i].clear();
    }

    delete[] adj;
    num_vertices = num_edges = 0;
}

bool search_element_in_list(std::list<VertexWeightPair> lst, VertexWeightPair flag){
    for (auto elem: lst){
        if ((elem.vertex) == (flag.vertex) && (elem.weight) == (flag.weight))
            return true;
    }
    return false;
}

void WeightedDigraphAL::add_edge(Vertex u, Vertex v, Weight w){
    VertexWeightPair vertex_v{v, w};
    if (!search_element_in_list(adj[u], vertex_v))
        adj[u].push_back(vertex_v);
        num_edges++;
}

void WeightedDigraphAL::remove_edge(Vertex u, Vertex v){
    
}

void display_list(std::list<VertexWeightPair> lst){
    for (auto elem:lst){
        std::cout << "(" << elem.vertex << ", " << elem.weight << "), ";
    }
}

void display_graph(WeightedDigraphAL &g){
    std::cout << "num_vertices: " << g.get_num_vertices() << std::endl;
    std::cout << "num_edges: " << g.get_num_edges() << std::endl;
    for (int i=0; i<g.get_num_vertices(); i++){
        std::cout << i << " : "; display_list(g.get_adj(i));
        std::cout << std::endl;
    }
}

int main(int argc, const char* argv[]){
    std::vector<float> input{};

    for (int i=1; i<argc; i++){
        input.push_back(atof(argv[i]));
    }
    
    unsigned int vertices = input[0], edges=input[1];

    WeightedDigraphAL g{vertices};
    


    for (int i=2; i<edges*3; i+=3){
        g.add_edge(input[i], input[i+1], input[i+2]);
    }

    display_graph(g);

}