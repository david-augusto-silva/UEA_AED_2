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

int get_index(std::vector<ItemVertex> v, ItemVertex i){
    int index = -1;
    do{index++;}while(v[index].v == i.v && v[index].w == i.w);

    return index;
}



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
    std::vector<Vertex> heapV;
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
    void insert(Vertex elem){
        heapV.push_back(elem);
        minHeapfyInsert(elem);
    }

    void build_min_heapV(std::vector<Vertex> v){
        for(auto key:v){
            insert(key);
        }
    }

    int extractMin(){
        if (heapV.empty()){
            return -1;
        }

        Vertex min = heapV[0];
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
    void enqueue(Vertex v){
        minHeap.insert(v);
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
    std::vector<Vertex> sick;

public:
    NeuronBlock(){
        this->num_vertices = 0;
        this->num_edges=0;
        this->num_sick=0;
    }

    void init(unsigned int num_vertices){
        this->num_vertices=num_vertices;
        this->num_edges=0;
        adj_n = new std::list<ItemVertex>[num_vertices];
    }

    void add_edge(unsigned int u, unsigned int v, float w){
        ItemVertex uv{v, w};
        ItemVertex vu{u, w};

        adj_n[u].push_back(uv);
        adj_n[v].push_back(vu);
    }

    void add_sick(Vertex v){
        sick.push_back(v);
    }

    void set_num_vertices(unsigned int num_vertices){
        this->num_vertices = num_vertices;
        adj_n = new std::list<ItemVertex>[num_vertices];
    }

    //retorna a soma dos pesos da mst
    float kruskal();
};

class Brain{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    std::pair<std::list<ItemVertex>, NeuronBlock> *adj_b;
    Vertex in;
    Vertex out;

public:
    Brain(unsigned int num_vertices):num_vertices(num_vertices), num_edges(0){
        adj_b = new std::pair<std::list<ItemVertex>, NeuronBlock>[num_vertices];
    }

    void add_edge(Vertex u, Vertex v, Weight w){
        ItemVertex u_to_v{v, w};
        adj_b[u].second = NeuronBlock{};
        adj_b[u].first.push_back(u_to_v); 
        num_edges++;
    }

    void init_neuronBlock(Vertex u,unsigned int num_v_neuron){
        adj_b[u].second.set_num_vertices(num_v_neuron);
    }

    void add_neuron_sick(Vertex u, Vertex sick_v){
        adj_b[u].second.add_sick(sick_v);
    }

    void add_neuron_edge(Vertex u, Vertex v1, Vertex v2, Weight w){
        adj_b[u].second.add_edge(v1, v2, w);
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

        for(auto& neighbor:adj_b[u].first){
            Vertex v = neighbor.v;
            Weight w = neighbor.w;

            if (adj_b[u].second.sick.size() != 0){
                sum += adj_b[u].second.kruskal();
            }
            
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.enqueue(u);
            }
        }
    }
    return sum;
}

int main() {
    
    unsigned int num_vertices_brain=0, num_edges_brain=0;    
    Vertex in=0, out=0;

    //Ordem e tamanho do grafo Brain
    std::cin >> num_vertices_brain >> num_edges_brain;

    Brain b{num_vertices_brain};

    // Adiciona arestas ao grafo Brain
    for (unsigned int i=0; i<num_edges_brain; i++){
        Vertex u=0, v=0;
        Weight w=0.0;
        std::cin >> u >> v >> w;
        b.add_edge(u-1, v-1, w);
    }
    
    // Entrada e saída 
    std::cin >> in >> out;
    b.set_in_out(in-1, out-1);

    //Blocos de Neurônios
    for(Vertex v=0; v<num_vertices_brain; v++){
        unsigned int num_vertices_nBlock=0, num_edges_nBlock=0;
        unsigned int num_sick=0;

        std::cin >> num_vertices_nBlock >> num_edges_nBlock;
        b.init_neuronBlock(v, num_vertices_nBlock);

        std::cin >> num_sick;
        if(num_sick != 0){
            for (unsigned int j=0; j < num_sick; j++){
                Vertex sick_v = 0;
                std::cin >> sick_v;
                b.add_neuron_sick(v, sick_v-1);
            }
        }

        for(unsigned int i=0; i<num_edges_nBlock; i++){
            Vertex ub=0, vb=0;
            Weight wb=0.0;

            std::cin >> ub >> vb >> wb;
            b.add_neuron_edge(v, ub-1, vb-1, wb);
        }
    }

    float result = 0.0;

    //Cálculo da MST
    result = b.dijkstra();

    std::cout << result << std::endl;

}