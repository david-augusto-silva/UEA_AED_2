#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void display_vector(vector<T> vec){
    for (T value:vec){
        cout << value << " ";
    }
    cout << endl;
}

template<typename T>
void print_empty(vector<T> vec){
    if (!vec.empty())
        cout << "O vetor NÃO ESTÁ vazio" << endl;
    else
        cout << "O vetor ESTÁ vazio" << endl;
}

int main(){

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

    display_vector(v);

    cout << "Tamanho: " << v.size() << endl;
    cout << "Capacidade: " << v.capacity() << endl;
    cout << "Tamanho máximo: " << v.max_size() << endl;

    cout << "Saída de 'begin()' e 'end()': ";
    for (auto i = v.begin(); i != v.end(); i++){
        cout<< *i <<" ";
    }
    cout << endl;

    cout << "Saída de 'rbegin()' e 'rend()': ";
    for (auto ir = v.rbegin(); ir != v.rend(); ir++){
        cout << *ir << " ";
    }
    cout << endl;


    print_empty(v);

    v.clear();

    print_empty(v);

    v.assign(5, 10);
    display_vector(v);
    
    v.push_back(54);
    display_vector(v);

    v.pop_back();
    display_vector(v); 
    cout << endl;

    vector<int> u;
    u.assign(8, 64);

    cout<< "Antes da troca: \n";
    cout << "v = "; display_vector(v);
    cout << "u = "; display_vector(u);


    u.swap(v);

    cout<< "Depois da troca: \n";
    cout << "v = "; display_vector(v);
    cout << "u = "; display_vector(u);


    return 0;
}