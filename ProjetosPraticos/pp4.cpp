#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>

class HashDict{
private:
    std::vector<std::pair<std::string, std::string>> hash_table;
    static const int TAM_ASCII = 256;
    static const int HASH_SIZE = 26;
    int h_aux(const std::string& k){
        int hash = 0;
        for (size_t i=0; i< k.size(); i++){
            hash += static_cast<int>(k[i])*(int)pow(TAM_ASCII, k.size() - i - 1)%HASH_SIZE;
        }
        return hash % HASH_SIZE;
    }
    int H(const std::string& k, int i){
        return (h_aux(k) + i) % HASH_SIZE;
    }
public:
    HashDict():hash_table(HASH_SIZE,{"", ""}){}

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
        std::cerr << "Nao ha espaco para chaves";
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

std::string uppercase(std::string& s){
    std::string upper = s;
    for(size_t i=0; i < s.size(); i++){
        upper[i] = toupper(s[i]);
    }
    return upper;
}

std::string lowercase(std::string& s){
    std::string lower = s;
    for(size_t i=0; i < s.size(); i++){
        lower[i] = tolower(s[i]);
    }
    return lower;
}

class BoyerMoore{
private:
    std::vector<int> skip_table;
    void init_skip_table(std::string pattern){
        int m = pattern.size();
        skip_table.assign(256, -1);
        
        for(int j=0; j < m; j++){
            skip_table[pattern[j]] = j;
        }
    }
public:
    BoyerMoore(){}   

    bool match(std::string text, std::string pattern){
        int n = text.size(),
            m = pattern.size(),
            skip = 0;

            init_skip_table(pattern);
            for(int i=0; i <= n-m; i+=skip){
                skip = 0;
                for(int j = m-1; j >=0; j--){
                    if(pattern[j] != text[i+j]){
                        skip = j - skip_table[text[i+j]];
                        if(skip < 1) skip = 1;
                        break;
                    }
                }
                if (skip == 0) return true;
            }
            return false;
    }

    int match_print(std::string text, std::string pattern){
        int n = text.size();
        int m = pattern.size();
        int skip = 0;

        init_skip_table(pattern);

        std::cout << uppercase(pattern) << ": ";
        for(int i=0; i <=n-m; i+=skip){
            skip=0;
            for(int j = m-1; j >=0; j--){
                if(pattern[j] != text[i+j]){
                    skip = j - skip_table[text[i+j]];
                    if (skip < 1) skip = 1;
                    break;
                }
            }
            std::cout << skip << " ";
            if (skip == 0){
                std::cout <<"("<< i << ") ";
                skip = 1;
            }            
        }
        std::cout << std::endl;
        return -1;
    }
};

std::string decipher(std::string &s, int p){
    std::string t= lowercase(s);

    char c = '\0';
    for(size_t i=0; i<t.size(); i++){
        c = t[i];
        
        if((t[i] >= 'a' && t[i] <= 'z') && (t[i] != 20 && t[i] != 46)){
            c = t[i] - p;
            if(c < 'a'){
                c += 26;
            }
            t[i] = c;
        }         
    }
    return uppercase(t); 
}

void search_for_patterns(std::string text, std::vector<std::string> patterns){
    BoyerMoore b;
    std::vector<int> skips;

    bool found = false;
    int c_found = 0;

    for(size_t i=0; i < patterns.size(); i++){
        int c = 1;
        std::string s = "";
        while(c <= 26){
            s = decipher(text, c);
            found = b.match(s, patterns[i]);
            if(found){
                c_found = c;
                b.match_print(s, patterns[i]);
                break;
            }
            c++;
        }   
        if(!b.match(decipher(text, c_found), patterns[i])){
            b.match_print(decipher(text, c_found), patterns[i]);
        }    

    }
}

int main(){
    
    std::string artefact;
    std::string translated;
    std::string deciphered;
    std::vector<std::string> patterns;

    HashDict d;
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
        if(aux == "fim" || aux == "FIM") break;
        patterns.push_back(uppercase(aux));
    }

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
     
    search_for_patterns(translated, patterns);
}    
   