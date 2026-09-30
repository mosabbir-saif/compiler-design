#include<bits/stdc++.h>
#define ll long long    
using namespace std;

signed main(){

    ifstream file("inputf.in");
    string s;
    vector<string>operators = {"+", "-", "/", "%", "++", "--", "*=", "+=", "-=", "=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "==", "!=", "<", ">", "<=", ">=", "<=>", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "?:", ".", "->", "->", "::", "[]", "()", ",", "&", "*", "**", "+++", "---"};
    //cout << "Valid operators: ";
    set<string>st;
    ll op_cnt = 0;
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
                        op_cnt += 2;
                        continue;
                    }
                    if(c == "---"){
                        st.insert("--");
                        st.insert("-");
                        op_cnt += 2;
                        continue;
                    }

                    st.insert(c);
                    op_cnt++;
                }
            }
        }
    }
    file.close();
    cout << "Total operators: " << op_cnt << endl;

}


