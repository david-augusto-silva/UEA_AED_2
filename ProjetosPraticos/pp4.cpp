#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

typedef std::string str;

class Dict{
private:
    std::vector<int> hash_table;
    static const int HASH_SIZE = 26;
    int h_aux(int k){
        return k % HASH_SIZE;
    }
    int H(int k, int i){
        return (h_aux(k) + i) % HASH_SIZE;
    }
public:
    Dict():hash_table(HASH_SIZE, -1){}

    int hash_insert(int k){
        int i=0;
        do{
            int pos = H(k, i);
            if (hash_table[pos] == -1){
                hash_table[pos] = k;
                return pos;
            }else{
                i++;
            }
        }while(i != HASH_SIZE);
        std::cerr << "Não há mais espaço para chaves";
        return -1;
    }

    int hash_search(int k){
        int i=0;
        int pos=0;
        do{
            pos = H(k, i);
            if(hash_table[pos] == k){
                return pos;
            }
            i++;
        }while(hash_table[pos] != -1 || i != HASH_SIZE);
        return -1;
    }

    void show_hash(){
        int i=0;
        for(auto k:hash_table){
            std::cout << i << ": " << k << std::endl;
            i++;
        }
    }
};

class BoyerMoore{
private:
    str pattern;
    std::vector<int> skip_table;
public:
    BoyerMoore(str pattern):pattern(pattern){
        int m = pattern.size();
        skip_table.assign(256, -1);
        
        for(int j=0; j < m; j++){
            skip_table[pattern[j]] = j;
        }
    }

    int match(str text){
        int n = text.size();
        int m = pattern.size();
        int skip = 0;

        for(int i=0; i <=n-m; i+=skip){
            skip=0;
            for(int j = m-1; j >=0; j--){
                if(pattern[j] != text[i+j]){
                    skip = j - skip_table[text[i+j]];
                    if (skip < 1) skip = 1;
                    break;
                }
            }
            if (skip == 0){
                std::cout << i << std::endl;
                skip = 1;
            }

            return -1;
        }
    }
};

int main(){
    
    Dict d;

    int i=0;
    while(i != -1){
        i = d.hash_insert(rand() % 100);
    }

    d.show_hash();
    
    int j = d.hash_search(98);

    if (j == -1){
        std::cout << "Elemento não encontrado\n";
    }else{
        std::cout << "Elemento encontrado na posição " << j << std::endl;
    }
}