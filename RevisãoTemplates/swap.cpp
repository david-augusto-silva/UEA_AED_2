#include <iostream>

using namespace std;

template<typename T>
void mySwap(T &item1, T &item2){
    T aux = item1;
    item1 = item2;
    item2 = aux;
};

int main(){

    int a = 21, b = 22;
    string f1 = "olá", f2 = "hello";

    cout << "Antes: " << endl;
    cout << "a = " << a << ", b = " << b << "\n";
    cout << "f1 = " << f1 << ", f2 = " << f2 << endl << endl;  

    mySwap(a, b);
    mySwap(f1, f2);

    cout << "Depois: " << endl;
    cout << "a = " << a << ", b = " << b << "\n";
    cout << "f1 = " << f1 << ", f2 = " << f2<<endl;  

}