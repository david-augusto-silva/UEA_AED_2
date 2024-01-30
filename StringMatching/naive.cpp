#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

class NaiveSM{
private:
    std::string pattern;
public:
    NaiveSM(std::string pattern):pattern(pattern){}
    int match(std::string text);
};

int NaiveSM::match(std::string text){
    int n = text.size(),
        m = pattern.size();
    
    for(int s=0; s < n-m; s++){
        int j;
        for(j=0; j < m; j++){
            if(text[s+j] != pattern[j]) break;
        }
        if (j==m) return s;
    }
    return n;
}