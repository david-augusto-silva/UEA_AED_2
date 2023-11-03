#include <iostream>

using namespace std;
typedef int Id;

template <typename T>
class Node{
public:
    T data;
    Node* next;

    Node(): next(nullptr){};
    Node(const T& data) : data(data), next(nullptr){}
};

template <typename T>
class List{
private:
    Node<T>* head;
    Node<T>* last;
    int length;

public:
    List() : head(nullptr){}

    ~List(){
        while (head){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void initialize(){
        head = new Node<T>();
        head->next = nullptr;
        last = head;
        length = 0;
    }
    void add(T item){
        last->next = new Node<T>();
        last = last->next;
        last->next = nullptr;
        last->data = item;
        length++;
    }
    void remove(Node<T> *p, T &item);
    Node<T>* find(Id key){
        Node<T> *p = head->hext;
        while (p != nullptr && p->data != key){
            p = p->next;
        }
        return p;
    }
    const Node<T>* getItems();
};
/* template<typename T>
void List<T>::initialize(){
    
}  */ 

template<typename T>
void display_list(const Node<T> *head){
    cout << "Lista: \n";
    Node<T> *p = head->next;
    while (p!=nullptr){
        cout << p->data << ", ";
        p = p->next;
    }
    cout << "(/)" << endl;
}


int main(){
    List<int> lista;

    lista.initialize();
    
    int numeros[6] = {1, 2, 3, 4, 5, 6};

    for (int i=0; i<6; i++){
        lista.add(numeros[i]);
    }

    display_list();
}