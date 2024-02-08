#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <list>

class Dict{
private:
    std::vector<std::pair<std::string, std::string>> hash_table;
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
    Dict():hash_table(HASH_SIZE,{"", ""}){}

    int hash_insert(const std::string& key, const std::string& value){
        int i=0;
        do{
            int pos = H(key, i);
            if (hash_table[pos].first.empty() && hash_table[pos].second.empty()){
                hash_table[pos].first = key;
                hash_table[pos].second = value;
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
            if(hash_table[pos].first == k){
                return pos;
            }
            i++;
        }while((!hash_table[pos].first.empty() && !hash_table[pos].second.empty()) || i != HASH_SIZE);
        return -1;
    }

    std::string hash_value_search(const std::string& value){
        for(auto p:hash_table){
            if(p.second == value){
                return p.first;
            }
        }
        return "";
    }

    void show_hash(){
        int i=0;
        for(auto p:hash_table){
            std::cout << i << ": " << "<" << p.first << " , " << p.second << ">" << std::endl;
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

void decipher(std::string &s){
    char c = '\0';
    for(size_t i=0; i<s.size(); i++){
        c = s[i];
        
        if((s[i] >= 'a' && s[i] <= 'z') && (s[i] != 20 && s[i] != 46)){
            if (c < 'd'){
                c = 123 + (s[i]-'a') - 3;
            }else{
                c = s[i] - 3;
            }
            
            s[i] = c;
        }         
    } 
}

int main(){
    
    std::string artefact;
    std::string translated;
    std::string deciphered;
    std::vector<std::string> patterns;

    Dict d;
    {
    d.hash_insert("a", ":::");
    d.hash_insert("b", ".::");
    d.hash_insert("c", ":.:");
    d.hash_insert("d", "::.");
    d.hash_insert("e", ":..");
    d.hash_insert("f", ".:.");
    d.hash_insert("g", "..:");
    d.hash_insert("h", "...");
    d.hash_insert("i", "|::");
    d.hash_insert("j", ":|:");
    d.hash_insert("k", "::|");
    d.hash_insert("l", "|.:");
    d.hash_insert("m", ".|:");
    d.hash_insert("n", ".:|");
    d.hash_insert("o", "|:.");
    d.hash_insert("p", ":|.");
    d.hash_insert("q", ":.|");
    d.hash_insert("r", "|..");
    d.hash_insert("s", ".|.");
    d.hash_insert("t", "..|");
    d.hash_insert("u", ".||");
    d.hash_insert("v", "|.|");
    d.hash_insert("w", "||.");
    d.hash_insert("x", "-.-");
    d.hash_insert("y", ".--");
    d.hash_insert("z", "--.");
    }

    std::cin >> artefact;

    std::string aux;
    while(true){
        std::cin >> aux;
        if(aux == "fim") break;
        patterns.push_back(aux);
    }

    //std::cout << artefact << std::endl;
    //TRADUÇÃO
    for(size_t i=0; i < artefact.size(); i+=3){
        aux = "";
        aux = artefact.substr(i, 3);
        if(aux == "---"){
            translated.append(" ");
        }else if(aux == "~~~"){
            translated.append(".");
        }else{
            translated.append(d.hash_value_search(aux));
        }
    }

    std::cout << translated << std::endl;

    decipher(translated);

    std::cout << translated << std::endl;

}