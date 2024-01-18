#include <iostream>
#include <cstdlib>
#include <limits>
#include <list>
#include <vector>

typedef unsigned int Vertex;
typedef float Weight;

class NeuronBlock;
class Brain;
class HeapVertex;
class MinPriorityQueueVertex;
class UnionFind;

class ItemVertex{
public:
    Vertex v;
    Weight w;
    ItemVertex(){}
    ItemVertex(Vertex v, Weight w): v(v), w(w){}
};

class UnionFind{
private:
    std::vector<int> id;
    unsigned int count;
public:
    UnionFind(int n): count(n){
        id.resize(n);
        for (int i=0; i<id.size(); i++){
            id.push_back(i);
        }
    }

    int find(int p){
        return id[p];
    }

    void unite(int p, int q){

        int pID = find(p), qID = find(q);

        if (pID == qID) return;

        for (int i=0; i < id.size(); i++){
            if (id[i] == pID) id[i] = qID;
        }

        count--;
    }
};

class NeuronBlock{
public:
    unsigned int num_vertices;
    unsigned int num_edges;
    unsigned int num_sick;
    std::list<ItemVertex> *adj;
    std::vector<unsigned int> sick;
public:
    NeuronBlock(unsigned int nV):
    num_vertices(nV), num_sick(0){
        adj = new std::list<ItemVertex> [num_vertices];
    }

    void add_edge(unsigned int u, unsigned int v, float w){
        ItemVertex edge_to_v{v, w};
        adj[u].push_back(edge_to_v);
    }

    //retorna a soma dos pesos da mst
    float kruskal();
};

float NeuronBlock::kruskal(){
    std::list<ItemVertex> result;
    UnionFind uf(num_vertices);

    for(Vertex i=0; i<num_vertices; i++){
        for (Vertex j=0; j < num_vertices - i; j++){
            if (adj[j].front().w > adj[j+1].front().w){
                std::swap(adj[j], adj[j+1]);
            }
        }
    }

    for (Vertex u = 0; u<num_vertices; ++u){
        for (auto& neighbor:adj[u]){
            Vertex v = neighbor.v;
            Vertex w = neighbor.w;

            if (uf.find(u) != uf.find(v)){
                result.push_back(neighbor);
                uf.unite(u, v);
            }
        }
    }

    float sum;
    for(auto v:result){
        sum += v.w;
    }

    return sum; 
}


int main(){

    unsigned int vertices, edges;

    std::cin >> vertices >> edges;
    NeuronBlock nB{vertices};

    for(int i = 0; i <= edges; i++){
        Vertex u, v;
        Weight w;
        std::cin >> u >> v >> w;

        nB.add_edge(u, v, w);
    }

    float mst_sum;

    mst_sum = nB.kruskal();

    std::cout << "Peso da mst: " << mst_sum << std::endl;
}


