#include <iostream>
#include <vector>
#include <cmath>

class MaxBinHeap{
private:
    std::vector<int> heap;
    
    int parent(int index){return (index-1)/2;}
    int leftC(int index){return 2*index+1;}
    int rightC(int index){return 2*index+2;}

    void maxHeapfyInsert(int index){
        while (index > 0 && heap[index] > heap[parent(index)]){
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
    void maxHeapfyRemove(int index){
        int l = leftC(index);
        int r = rightC(index);
        int largest = index;

        if (l < heap.size() && heap[l]>heap[index]){
            largest = l;
        }

        if (r < heap.size() && heap[r]>heap[largest]){
            largest = r;
        }

        if (largest != index){
            std::swap(heap[index], heap[largest]);
            maxHeapfyRemove(largest);
        }
    }
public:
    void insert(int );
    int extractMax();
    void showHeap();

    bool hEmpty() const{
        return heap.empty();
    }
};

class PriorityQueue{
private:
    MaxBinHeap maxHeap;
public:
    void enqueue(int key){
        maxHeap.insert(key);
    }

    int dequeue(){
        return maxHeap.extractMax();
    }

    bool qEmpty() const{
        return maxHeap.hEmpty();
    }
};

void MaxBinHeap::insert(int key){
    heap.push_back(key);
    maxHeapfyInsert(heap.size()-1);
}

void MaxBinHeap::showHeap(){
    for (auto key:heap){
        std::cout << key << " ";
    }
    std::cout << std::endl;
}

int MaxBinHeap::extractMax(){
    if (heap.empty()){
        std::cerr << "Heap vazio!" << std::endl;
        return -1;
    }

    int max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    maxHeapfyRemove(0);

    return max;

}

int main(){
    std::vector<int> input{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    MaxBinHeap mHeap;

    for (auto i:input){
        mHeap.insert(i);
    }

    mHeap.showHeap();

    std::cout << "Removendo o valor máximo: " << mHeap.extractMax() << std::endl;

    std::cout << "Heap após a remoção: ";
    mHeap.showHeap();

    return 0;
}