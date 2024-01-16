#include <iostream>
#include <list>
#include <vector>
#include <limits>

template <typename It,typename T>
void my_iota(It begin, It end, T val){
    while (begin != end){
        *begin = val;
        ++begin;
        ++end;
    }
}

typedef float Weight;
typedef unsigned int Vertex;

class MinPriorityQueue;
class MinBinHeap;
class UnionFind;

class wVertex{
public:
    Weight w;
    Vertex v;
    wVertex(Vertex v, Weight w):v(v), w(w){}
};

class SubGraph{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    std::list<wVertex> *adj;
public:
    SubGraph(unsigned int num_vertices, unsigned int num_edges):num_vertices(num_vertices), num_edges(num_edges){
        adj = new std::list<wVertex>[num_vertices];
    }
    ~SubGraph(){
    for (int i=0; i < num_vertices; i++){
        adj[i].clear();
    }

    delete[] adj;

    num_vertices = num_edges = 0;
    }

    void add_edge(Vertex u, Vertex v, Weight w){
        wVertex new_vertex{v, w};

        adj[u].push_back(new_vertex);
        num_edges++;
    }
    
    unsigned int set_num_vertices(unsigned int v){
        num_vertices = v;
    }
    unsigned int set_num_edges(unsigned int e){
        num_edges = e;
    }
    unsigned int get_num_edges(){
        return num_edges;
    }
    unsigned int get_num_vertices(){
        return num_vertices;
    }
    std::list<wVertex> get_adj(Vertex v){
        return adj[v];
    }

    std::vector<Weight> dijkstra(Vertex source);
    std::list<wVertex> SubGraph::kruskal();
};


class GraphV{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    std::list<std::pair<wVertex, SubGraph>> *adj;
public:
    GraphV(unsigned int num_vertices, unsigned int num_edges):num_vertices(num_vertices), num_edges(num_edges){
        adj = new std::list<std::pair<wVertex, SubGraph>>[num_vertices];
    }
    ~GraphV(){
        for(int i=0; i<num_vertices; i++){
            adj[i].clear();
        }

        delete[] adj;

        num_vertices = num_edges = 0;
    }
    void add_edge(Vertex u, Vertex v, Weight w){
        wVertex edge_uv{v, w};
        SubGraph g{0, 0};
        std::pair<wVertex, SubGraph> p{edge_uv, g};
        adj[u].push_back(p);
    }
    void create_subgraph(Vertex v, unsigned int num_vertices, unsigned int num_edges){
        (adj[v].begin())->second.set_num_vertices(num_vertices);
        (adj[v].begin())->second.set_num_edges(num_edges);
    }
    
    std::vector<Weight> dijkstra(Vertex source){
        std::vector<Weight> dist(num_vertices, std::numeric_limits<Weight>::infinity());
        dist[source] = 0;

        PriorityQueue pq;
        pq.enqueue(source);
        while (!pq.is_empty()){
            Vertex u = pq.dequeue();

            for (auto& neighbor:adj[u]){
                Vertex v = neighbor.first.v;
                Weight w = neighbor.first.w;

                if(dist[u]+w < dist[v]){
                    dist[v] = dist[u] + w;
                    pq.enqueue(v);
                }
            }
        }
    }

};

class MinBinHeap{
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
        int l = leftC(index);
        int r = rightC(index);
        int smallest = index;

        if (l < heapV.size() && heapV[l] < heapV[index]){
            smallest = l;
        }
        if (r < heapV.size() && heapV[r] < heapV[smallest]){
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
    int extractMin(){
        if (heapV.empty()){
            return -1;
        }
        int max = heapV[0];
        heapV[0] = heapV.back();
        heapV.pop_back();
        minHeapfyRemove(0);

        return max;
    }
    bool heap_empty() const{
        return heapV.empty();
    }
};

class PriorityQueue{
private:
    MinBinHeap minHeap;
public:
    void enqueue(int key){
        minHeap.insert(key);
    }
    int dequeue(){
        return minHeap.extractMin();
    }
    bool is_empty() const{
        return minHeap.heap_empty();
    }
};

class UnionFind{
private:
    std::vector<int> parent;
public:
    UnionFind(int n){
        parent.resize(n);
        my_iota(parent.begin(), parent.end(), 0);
    }

    int find(int x){
        if (parent[x] != x){
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void unite(int x, int y){
        int rX = find(x);
        int rY = find(y);

        if (rX != rY){
            parent[rX] = rY;
        }
    }
};

std::vector<Weight> SubGraph::dijkstra(Vertex source){
    std::vector<Weight> dist(num_vertices, std::numeric_limits<Weight>::infinity());
    dist[source] = 0;

    PriorityQueue pq;
    pq.enqueue(source);

    while (!pq.is_empty()){
        Vertex u = pq.dequeue();

        for (auto& neighbor : adj[u]){
            Vertex v = neighbor.v;
            Weight w = neighbor.w;

            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.enqueue(v);
            }
        }
    }

    return dist;
}

std::list<wVertex> SubGraph::kruskal(){
    std::list<wVertex> result;
    UnionFind uf(num_vertices);

    //vetor de arestas ordenado por peso
    std::vector<wVertex> edges;
    for(Vertex u=0; u < num_vertices; ++u){
        for(auto& neighbor:adj[u]){
            Vertex v = neighbor.v;
            Vertex w = neighbor.w;
            edges.push_back({v, w});
        }
    }

    //ordenação em ordem crescente de peso
    for (Vertex i = 0; i < num_vertices - 1; i++){
        for (Vertex j = 0, j < num_vertices - i - 1; j++){
            if (adj[])
        }
    }
}

int main(){

    


}