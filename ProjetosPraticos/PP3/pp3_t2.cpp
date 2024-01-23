#include <iostream>
#include <cstdlib>
#include <limits>
#include <list>
#include <vector>
#include <iomanip>

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

void lst_sort(std::list<ItemVertex>& lst){
    for (auto i=lst.begin(); i!=lst.end(); ++i){
        for(auto j=std::next(i); j!=lst.end(); ++j){
            if(i->w > j->w){
                std::swap(*i, *j);
            }
        }
    }
}

class HeapVertex{
private: 
    std::vector<int> heapV;
    int parent(int index){return index-1/2;}
    int leftC(int index){return 2*index+1;}
    int rightC(int index){return 2*index+2;}

    void minHeapfyInsert(int index){
        while (index > 0 && heapV[index] < heapV[parent(index)]){
            std::swap(heapV[index], heapV[parent(index)]);
            index = parent(index);
        }
    }

    void minHeapfyRemove(int index){
        int l=leftC(index);
        int r = rightC(index);
        int smallest = index;

        if (l < heapV.size() && heapV[l] < heapV[index]){
            smallest=l;
        }
        if(r < heapV.size() && heapV[r] < heapV[smallest]){
            smallest = r;
        }

        if (smallest != index){
            std::swap(heapV[index], heapV[smallest]);
            minHeapfyRemove(smallest);
        }
    }
public:
    void insert(int key){
        heapV.push_back(key);
        minHeapfyInsert(key);
    }

    void build_min_heapV(std::vector<int> v){
        for(auto key:v){
            insert(key);
        }
    }

    int extractMin(){
        if (heapV.empty()){
            return -1;
        }

        int min = heapV[0];
        heapV.pop_back();
        minHeapfyRemove(0);
        return min;
    }

    bool heap_empty() const{
        return heapV.empty();
    }
};

class MinPriorityQueueVertex{
private:
    HeapVertex minHeap;
public:
    void enqueue(int key){
        minHeap.insert(key);
    }
    Vertex dequeue(){
        return minHeap.extractMin();
    }
    bool is_empty() const{
        return minHeap.heap_empty();
    }
};

class UnionFind{
private:
    std::vector<int> id;
    unsigned int count;
public:
    UnionFind(int n): count(n){
        id.resize(n);
        for (int i=0; i<id.size(); i++){
            id[i] = i;
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
    std::list<ItemVertex> *adj_n;
    std::vector<unsigned int> sick;

public:
    NeuronBlock(){};

    void init(unsigned int num_vertices){
        this->num_vertices=num_vertices;
        this->num_edges=0;
        adj_n = new std::list<ItemVertex>[num_vertices];
    }

    void add_edge(unsigned int u, unsigned int v, float w){
        adj_n[u].emplace_back(v, w);
        adj_n[v].emplace_back(u, w);
    }

    void add_sick(Vertex v){
        sick.push_back(v);
    }

    void set_num_vertices(unsigned int num_vertices){
        this->num_vertices = num_vertices;
    }

    //retorna a soma dos pesos da mst
    float kruskal();
};

class Brain{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    std::list<std::pair<ItemVertex, NeuronBlock>> *adj_b;
    Vertex in;
    Vertex out;

public:
    Brain(unsigned int num_vertices):num_vertices(num_vertices), num_edges(0){
        adj_b = new std::list<std::pair<ItemVertex,NeuronBlock>>[num_vertices];
    }

    void add_edge(Vertex u, Vertex v, Weight w){
        ItemVertex u_to_v{v, w};
        ItemVertex v_to_u{u, w};

        auto& u_lst = adj_b[u];
        auto& v_lst = adj_b[v];

        u_lst.emplace_back(u_to_v, NeuronBlock{});
        v_lst.emplace_back(u_to_v, NeuronBlock{});
    }

    void init_neuronBlock(unsigned int num_v_neuron,Vertex u, Vertex v){
        for(auto bv:adj_b[u]){
            if(bv.first.v == v){
                bv.second.set_num_vertices(num_v_neuron);
                break;
            }
        }
    }

    void add_neuron_sick(Vertex u, Vertex sick_v){
        adj_b[u].
    }

    void add_neuron_edge(Vertex u1, Vertex v1, Vertex u2, Vertex v2, Weight w){
        for(auto bv:adj_b[u1]){
            if(bv.first.v == v1){
                bv.second.add_edge(u2, v2, w);
            }
        }
    }
    
    void set_in_out(Vertex i, Vertex o){
        this->in=i;
        this->out=o;
    }

    //nanorobot move
    float dijkstra();
};

float NeuronBlock::kruskal(){
    std::list<ItemVertex> result;
    UnionFind uf(num_vertices);

    for(Vertex v=0; v < num_vertices; v++){
        lst_sort(adj_n[v]);
    }

    for (Vertex u = 0; u<num_vertices; ++u){
        for (auto& neighbor:adj_n[u]){
            Vertex v = neighbor.v;
            Weight w = neighbor.w;

            if (uf.find(u) != uf.find(v)){
                result.push_back(neighbor);
                uf.unite(u, v);
            }
        }
    }

    float sum=0.0;
    for(auto v:result){
        sum += v.w;
    }

    return sum; 
}

// Quando visita um vertice, já é calculada a MST
float Brain::dijkstra(){
    std::vector<Weight> dist(num_vertices, std::numeric_limits<Weight>::infinity());
    dist[in] = 0;

    float sum = 0.0;

    MinPriorityQueueVertex pq;
    pq.enqueue(in);

    while (!pq.is_empty()){
        Vertex u = pq.dequeue();

        for(auto& neighbor:adj_b[u]){
            Vertex v = neighbor.first.v;
            Weight w = neighbor.first.w;

            if (neighbor.second.sick.size() != 0){
                sum += neighbor.second.kruskal();
            }
            
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.enqueue(v);
            }

        }
    }

    return sum;

}

int main() {
    
    unsigned int num_vertices_brain=0, num_edges_brain=0;
    unsigned int num_vertices_nBlock=0, num_edges_nBlock=0;
    unsigned int num_sick=0;
    Vertex in=0, out=0;


    std::cin >> num_vertices_brain >> num_edges_brain;

    Brain b{num_vertices_brain};

    // Adiciona os vertices ao cérebro ("grafão")
    for (unsigned int i=0; i<num_edges_brain; i++){
        Vertex u=0, v=0;
        Weight w=0.0;
        std::cin >> u >> v >> w;
        b.add_edge(u-1, v-1, w);
    }

    // Entrada e saída 
    std::cin >> in >> out;
    b.set_in_out(in-1, out-1);


    std::cin >> num_vertices_nBlock >> num_edges_nBlock;

    std::cin >> num_sick;
    if(num_sick != 0){
        for 
    }
}