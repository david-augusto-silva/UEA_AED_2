#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>

typedef unsigned int Vertex, Weight;

class GraphAM{
private:
    unsigned int num_vertices, num_edges;
    Weight **adj;
    bool find_vertex(Vertex, Vertex);
public:
    GraphAM(unsigned int);//
    ~GraphAM();//
    void add_edge(Vertex, Vertex);//
    void remove_edge(Vertex, Vertex);//
    std::list<Vertex> get_adj(Vertex);
    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
    Weight get_weight_edge(Vertex u, Vertex v){return adj[u][v];}
};

GraphAM::GraphAM(unsigned int num_vertices):num_vertices(num_vertices),
                                            num_edges(0){
    adj = new Weight*[num_vertices];
    for (int i=0; i<num_vertices; i++){
        adj[i] = new Weight[num_vertices];
        for(int j=0; j<num_vertices; j++){
            adj[i][j] = 0;
        }
    }
}

GraphAM::~GraphAM(){
    for(int i=0; i<num_vertices; i++){
        delete[] adj[i];
    }
    delete[] adj;
}

bool GraphAM::find_vertex(Vertex u, Vertex v){
    if(adj[u][v] == 1 || adj[v][u] == 1){
        return true;
    }
    return false;
}

void GraphAM::add_edge(Vertex u, Vertex v){
    if (!find_vertex(u, v))
        adj[u][v] = 1;
        adj[v][u] = 1;
        num_edges++;
}

void GraphAM::remove_edge(Vertex u, Vertex v){
    if ((u < num_vertices) && (v < num_vertices) && (find_vertex(u, v))){
        adj[u][v] = 0;
        adj[v][u] = 0;
        num_edges--;
    }
}

std::list<Vertex> GraphAM::get_adj(Vertex v){
    std::list<Vertex> list_adj_r{};
    for (auto i=0; i < num_vertices; i++){
        list_adj_r.push_back(adj[v][i]);
    }

    return list_adj_r;
}

//Exibição
template <typename T>
void display_list(std::list<T> list){
    for(auto elem : list){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;
}

void show_adj_mat(GraphAM &g){

    std::cout << "num_vertices: " << g.get_num_vertices() << " "<< std::endl;
    std::cout << "num_edges: " << g.get_num_edges() <<" "<<std::endl;

    for(unsigned int i=0; i<g.get_num_vertices();i++){
        display_list(g.get_adj(i));
    }
}


int main(){
    unsigned int num_vertices = 0, num_edges=0;

    std::cin >> num_vertices;
    std::cin >> num_edges;

    GraphAM g{num_vertices};

    for(unsigned int i=0; i < num_edges; i++){
        Vertex u=0, v=0;
        std::cin >> u;
        std::cin >> v;
        g.add_edge(u, v);
    }

    show_adj_mat(g);
}