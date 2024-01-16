#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

void insertion_sort(vector<int> &input){

    int i, j, chave;
    for (j=1; j < input.size(); j++){
        chave = input[j];
        i = j-1;
        while (i >= 0 && input[i] > chave){
            input[i+1] = input[i];
            i--;
        }
        input[i+1] = chave;
    }
}

void bubble_sort(vector<int> &input){
    int i, j;
    for(i=input.size(); i>0; i--){
        for(j = 0; j < i; j++){
            if (input[j] < input[j-1]){
                swap(input[j], input[j-1]);
            }
        }
    }

}

void selection_sort(vector<int> &input){
    for (int i=0; i < input.size(); i++){    
        int min_id = i;
        for (int j = i+1; j < input.size(); j++){
            if (input[j] < input[min_id]){
                min_id = j;
            }
        }
        swap(input[i], input[min_id]);
    }
}

int part(vector<int> &input, int p, int r){
    int x, tmp, i, j;
    x = input[p];
    tmp = input[r+1];
    input[r+1]=x;
    i = p; j=r+1;

    while (true){
        do{i = i+1;}while(input[i]<x);
        do{j = j-1;}while(input[j]>x);
        if (i<j){
            swap(input[i], input[j]);
        }else{
            swap(input[p], input[j]);
            input[r+1] = tmp;
            break;
        }
    }
    return j;

}

void quicksort(vector<int> &input, int pivot, int r){
    if(pivot < r){
        int q = part(input, pivot, r);
        quicksort(input, pivot, q-1);
        quicksort(input, q+1, r);
    }
}

void merge(vector<int> &input, int p, int q, int r){
    int n1 = q-p+1, n2 = r-q, i, j;
    vector<int> L(n1), R(n2);
    
    for(i=0; i < n1; i++){L[i] = input[p+i];}
    for(j=0; j < n2; j++){R[j] = input[q+j+1];}
   
    i = 0; j = 0;

    for (int k=p; k <= r; k++){
        if (i < n1 && (j >=n2 || L[i] <= R[j])){
            input[k] = L[i]; i++;
        }else{
            input[k] = R[j]; j++;
        }
    }

}

void merge_sort(vector<int> &input, int p, int r){
    if (p < r){
        int q = floor((p+r)/2);
        merge_sort(input, p, q);
        merge_sort(input, q+1, r);
        merge(input, p, q, r);
    }
}


void display_vector(vector<int> &input){
    for (int i=0; i < input.size(); i++){
        cout << input[i] << " ";
    }
    cout << endl;
}

int main(){

    vector<int> a{0,5,48,26,35,14,1,2,3,4,6,7,8,9};

    cout << "Antes da ordenação:  "; display_vector(a); 

    //insertion_sort(a, insertion_time);
    merge_sort(a, 0, a.size());

    cout << "Depois da ordenação: "; display_vector(a);
    return 0;

}