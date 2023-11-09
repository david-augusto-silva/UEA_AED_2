#include<iostream>
#include<list>

using namespace std;
template<typename T>
void exibir_lista(list<T> lista){
    for (auto i:lista)
        cout << i << ' ';
    cout<<endl;
}   

int main(){
    list<int> l{12,24,48,72};

    exibir_lista(l);
    cout << endl;

    auto prim = l.begin();
    auto ult = l.end();
    cout << "Primeiro item da lista: " << *prim <<endl;
    cout << "Último item da lista: " << *(--ult) << endl;

    cout << "Tamanho da lista: " << l.size();
    
}
