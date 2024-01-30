#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#define SKIP_SIZE 255

class BoyerMoore{
private:
    std::vector<int> skip_table;
    std::string pattern;

public:
    BoyerMoore(std::string pattern):pattern(pattern){
        int m = pattern.size();
        skip_table.assign(SKIP_SIZE, -1);

        for(int j=0; j<m; j++){
            skip_table[pattern[j]] = j;
        }
    }

    int match(std::string text);
};

int BoyerMoore::match(std::string text){
    int n = text.size(),
        m = pattern.size(),
        skip = 0;
    
    for(int i=0; i <= n-m; i+=skip){
        skip = 0;
        for(int j= m-1; j >= 0; j--){
            if(pattern[j] != text[i+j]){
                skip = j - skip_table[text[i+j]];
                if (skip < 1) skip = 1;
                break; 
            }
        }
        if (skip == 0) return i;
    }
    return -1;
}
