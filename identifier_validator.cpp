#include <bits/stdc++.h>
using namespace std;
int isIdentifier(string str){
    int i = 0;
    if(!(isalpha(str[i]) || str[i] == '_')){
        return 0;
    }
    i++;
    while(i < str.size()){
        if(str[i] == ' ') return 0;
        if(!(isalnum(str[i]) || str[i] == '_')){
            return 0;
        }
        i++;
    }
    return 1;
}
signed main(){
    ifstream file("inputf.in");
    string str;
    getline(file, str);
    if(isIdentifier(str)) cout << "Accepted: Valid Identifier" << endl; 
    else cout << "Rejected: Invalid Identifier" << endl;
}
