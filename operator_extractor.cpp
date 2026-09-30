#include<bits/stdc++.h>
#define ll long long    
using namespace std;
signed main(){
    ifstream file("inputf.in");
    string s;
    vector<string>operators = {"+", "-", "/", "%", "++", "--", "*=", "+=", "-=", "=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "==", "!=", "<", ">", "<=", ">=", "<=>", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "?:", ".", "->", "->", "::", "[]", "()", ",", "&", "*", "**", "+++", "---"};
    cout << "Valid operators: ";
    set<string>st;
    while(getline(file, s)){
        if(s == "#include<bits/stdc++.h>") continue;
        stringstream ss(s);
        string word;
        while(ss >> word){
            for(string c : operators){
                if(word.find(c) != string::npos){
                    auto it = word.find(c);
                    if(c == "+"){
                        if(it > 0 && word[it-1] == '+') continue; 
                        if(it + 1 < word.size() && (word[it+1] == '+' || word[it+1] == '=')) continue;
                    }
                    if(c == "-"){
                        if(it > 0 && word[it-1] == '-') continue; 
                        if(it + 1 < word.size() && (word[it+1] == '-' || word[it+1] == '=' || word[it+1] == '>')) continue;
                    }
                    if(c == "*"){
                        if(it > 0 && (word[it-1] == '/' || word[it-1] == '*')) continue;
                        if(it + 1 < word.size() && (word[it+1] == '/' || word[it+1] == '=' || word[it+1] == '*')) continue;
                    }
                    if(c == "/"){
                        if(it > 0 && (word[it-1] == '/' || word[it-1] == '*')) continue; 
                        if(it + 1 < word.size() && (word[it+1] == '/' || word[it+1] == '=' || word[it+1] == '*')) continue;
                    }
                    if(c == "="){
                        if(it > 0 && (word[it-1] == '=' || word[it-1] == '!' || word[it-1] == '<' || word[it-1] == '>')) continue;
                        if(it + 1 < word.size() && word[it+1] == '=') continue; 
                    }
                    if(c == "<"){
                        if(it > 0 && word[it-1] == '<') continue;
                        if(it + 1 < word.size() && (word[it+1] == '=' || word[it+1] == '<')) continue;
                    }
                    if(c == ">"){
                        if(it > 0 && word[it-1] == '>') continue; 
                        if(it + 1 < word.size() && (word[it+1] == '=' || word[it+1] == '>')) continue;
                    }
                    if(c == "&"){
                        if(it > 0 && word[it-1] == '&') continue;
                        if(it + 1 < word.size() && (word[it+1] == '&' || word[it+1] == '=')) continue;
                    }
                    if(c == "|"){
                        if(it > 0 && word[it-1] == '|') continue; 
                        if(it + 1 < word.size() && (word[it+1] == '|' || word[it+1] == '=')) continue; 
                    }
                    if(c == "^"){
                        if(it + 1 < word.size() && word[it+1] == '=') continue; 
                    }
                    if(c == "%"){
                        if(it + 1 < word.size() && word[it+1] == '=') continue; 
                    }
                    if(c == "!"){
                        if(it + 1 < word.size() && word[it+1] == '=') continue; 
                    }
                    if(c == "."){
                        if(it > 0 && word[it-1] == '.') continue; 
                        if(it + 1 < word.size() && word[it+1] == '.') continue; 
                    }
                    if(c == "++"){
                        if(it + 2 < word.size() && word[it+2] == '.' && word[it+2] == '+') continue;
                        if(it - 2 >= 0 && word[it-2] == '+') continue;
                    }
                    if(c == "--"){
                        if(it + 2 < word.size() && word[it+2] == '-') continue;
                        if(it - 2 >= 0 && word[it-2] == '-') continue;
                    }
                    if(c == "+++"){
                        st.insert("++");
                        st.insert("+");
                        continue;
                    }
                    if(c == "---"){
                        st.insert("--");
                        st.insert("-");
                        continue;
                    }

                    st.insert(c);
                }
            }
        }
    }
    file.close();
    if(st.size() > 0){
        for(auto &val : st){
            cout << val << " ";
        }
    }
    else cout << "No Operators" << endl;
}


