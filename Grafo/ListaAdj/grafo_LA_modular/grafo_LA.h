#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<list>

typedef unsigned int Vertex;

using namespace std;

class ItemEdge{
private:
    unsigned int value = 0;
public:
    ItemEdge (){}
    ItemEdge(unsigned int value) : value(value){}
    void set_value(unsigned int v){
        value = v;
    }
    unsigned int get_value(){
        return value;
    }
};

template<typename T>
class Graph{
private:
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    list<T> *adj;
public:
    Graph (unsigned int);
    ~Graph();
    void new_edge(Vertex, Vertex);
    list<T> get_adj(Vertex v) {return adj[v];}
    unsigned int get_num_vertices() {return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
};

template<typename T>
Graph<T>::Graph(unsigned int v):num_vertices(v), num_edges(0){
    adj = new list<T>[num_vertices];
}

template<typename T>
Graph<T>::~Graph(){
    for (auto i=0; i<num_vertices; i++){
        adj[i].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_vertices = num_edges = 0;
}

template<typename T>
void Graph<T>::new_edge(Vertex u, Vertex v){
    ItemEdge item_v{v}, item_u{u};
    adj[u].push_back(item_v);
    adj[v].push_back(item_u);
    num_edges++;
}
#endif