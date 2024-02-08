#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <list>

class Dict{
private:
    std::vector<std::string> hash_table;
    static const int TAM_ASCII = 256;
    static const int HASH_SIZE = 26;
    int h_aux(const std::string& k){
        int hash = 0;
        for (int i=0; i< k.size(); i++){
            hash += static_cast<int>(k[i])*(int)pow(TAM_ASCII, k.size() - i - 1)%HASH_SIZE;
        }
        return hash % HASH_SIZE;
    }
    int H(const std::string& k, int i){
        return (h_aux(k) + i) % HASH_SIZE;
    }
public:
    Dict():hash_table(HASH_SIZE, ""){}

    int hash_insert(const std::string& k){
        int i=0;
        do{
            int pos = H(k, i);
            if (hash_table[pos].empty()){
                hash_table[pos] = k;
                return pos;
            }else{
                i++;
            }
        }while(i != HASH_SIZE);
        std::cerr << "Não há mais espaço para chaves";
        return -1;
    }

    int hash_search(const std::string& k){
        int i=0;
        int pos=0;
        do{
            pos = H(k, i);
            if(hash_table[pos] == k){
                return pos;
            }
            i++;
        }while(!hash_table[pos].empty() || i != HASH_SIZE);
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
    std::string pattern;
    std::vector<int> skip_table;
public:
    BoyerMoore(std::string pattern):pattern(pattern){
        int m = pattern.size();
        skip_table.assign(256, -1);
        
        for(int j=0; j < m; j++){
            skip_table[pattern[j]] = j;
        }
    }

    int match(std::string text){
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
    char i = 'a';
    do{
        std::string s = "";
        d.hash_insert(s+i);
        i++;
    }while(i != 'z'+1);


    d.show_hash();

}