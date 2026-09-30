#include<bits/stdc++.h>
#define ll long long    
using namespace std;
signed main(){
    ifstream file("inputf.in");
    string s;
    ll char_count = 0, word_count = 0, line_count = 0;
    while(getline(file, s)){
        line_count++;
        stringstream ss(s);
        string word;
        while(ss >> word){
            word_count++;
            char_count += word.size();
        }
    }
    file.close();
    cout << "Characters: " << char_count << endl << "Words: " << word_count << endl << "Lines: " << line_count << endl;
}