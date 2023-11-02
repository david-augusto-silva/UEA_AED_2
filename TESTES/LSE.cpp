#include<iostream>

using namespace std;

class Task{
public: 
    string data_e_hora;
    string descricao;
    bool status;


    Task(){
        this->data_e_hora = "";
        this->descricao = "";
        this->status = false;
    }
};



int main(){

    Task t1("25/10/2023 8:00", "Tomar café da manhã");

    return 0;

}