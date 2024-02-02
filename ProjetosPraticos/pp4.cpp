#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

typedef std::string str;

class Dict{
private:
    std::vector<int> hash_table;
    const int HASH_SIZE;
    int h_aux(int k){
        return k % HASH_SIZE;
    }
    int H(int k, int i){
        return (h_aux(k) + i) % HASH_SIZE;
    }
public:
    Dict(int hash_size): HASH_SIZE(hash_size){
        hash_table.assign(HASH_SIZE, -1);
    }

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
    
}