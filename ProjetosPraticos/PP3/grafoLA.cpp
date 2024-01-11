#include <iostream>
#include <list>
#include <vector>
#include <limits>


typedef float Weight;
typedef unsigned int Vertex;

class wVertex{
public:
    Weight w;
    Vertex v;
    wVertex(Vertex v, Weight w):v(v), w(w){}
};

class MinPriorityQueue;
class MinBinHeap;

class GraphV{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    std::list<wVertex> *adj;
public:
    GraphV(unsigned int num_vertices):num_vertices(num_vertices), num_edges(0){
        adj = new std::list<wVertex>[num_vertices];
    }
    GraphV(){
    for (int i=0; i < num_vertices; i++){
        adj[i].clear();
    }

    delete[] adj;

    num_vertices = num_edges = 0;
    }

    void add_edge(Vertex u, Vertex v, Weight w){
        wVertex new_vertex{v, w};

        adj[u].push_back(new_vertex);
    }
    bool remove_edge(Vertex u, Vertex v){
        for (auto elem:adj[u]){
            if (elem.v == v){
                adj[u].remove(elem);
                return true;
            }
        }
        return false;
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

std::vector<Weight> GraphV::dijkstra(Vertex source){
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


int main(){

    


}