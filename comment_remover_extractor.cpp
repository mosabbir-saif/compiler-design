#include<bits/stdc++.h>
#define ll long long    
using namespace std;

signed main(){
    ifstream file("inputf.in");
    string s;
    ll char_count = 0, word_count = 0, line_count = 0; bool flag = false;
    while(getline(file, s)){
        stringstream ss(s);
        string word; ss >> word;
        if(word[0] == '/' && word[1] == '/'){
            cout << "Commented line: " << s << endl << endl;
            continue;
        } if(word[0] == '/' && word[1] == '*'){
            flag = true;
            cout << "Commented lines: " << endl << s << endl;
            continue;
        } if(flag) cout << s << endl;
        if(word.size() >= 2 && word.substr(word.size()-2, 2) == "*/") flag = false;
    }
    file.close();
}