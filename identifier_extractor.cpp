#include<bits/stdc++.h>
#define ll long long    
using namespace std;
signed main(){
    ifstream file("inputf.in");
    string s;
    vector<string> keywords = {"bool", "char", "char8_t", "char16_t", "char32_t", "int", "long", "short", "signed", "unsigned", "float", "double", "void", "wchar_t", "if", "else", "switch", "case", "default", "for", "while", "do", "break", "continue", "goto", "true", "false", "nullptr", "new", "delete", "sizeof", "alignas", "alignof", "class", "struct", "union", "enum", "friend", "mutable", "this", "public", "private", "protected", "inline", "explicit", "virtual", "override", "final", "constexpr", "consteval", "constinit", "operator", "typedef", "using", "typename", "template", "concept", "requires", "try"};
    vector<ll> dig = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    vector<char> valids = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};
    cout << "Valid identifier: " << endl;
    while(getline(file, s)){
        stringstream ss(s); string word;
        while(ss >> word){
            bool flag = true;
            if(find(valids.begin(), valids.end(), word[0]) == valids.end()) continue;
            if(find(keywords.begin(), keywords.end(), word) != keywords.end()) continue;
            for(char c : word){
                if(c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z'){
                    if(c != '_'){
                        flag = false; break;
                    }
                }
            }
            if(flag) cout << word << " ";
        }
    }
    file.close();
}


