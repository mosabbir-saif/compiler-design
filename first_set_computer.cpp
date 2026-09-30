#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> grammar;
map<string, set<string>> firstSet;

bool isTerminal(string s){ 
    return !isupper(s[0]);
}

void findFirst(string symbol){ 
    if(!firstSet[symbol].empty()) return; 
    for(string production : grammar[symbol]){
        cout << "P = " << production << endl;
        bool epsilonPossible = true;
        for(int i = 0; i < production.length();){ 
            string currentSymbol;
            if(i + 1 < production.length() && production[i] == 'i' && production[i + 1] == 'd'){
                currentSymbol = "id";
                i += 2;
            }
            else if (i + 1 < production.length() && production[i + 1] == '\''){
                currentSymbol = production.substr(i, 2);
                i += 2;
            }
            else{
                currentSymbol = string(1, production[i]);
                i++;
            }
            if(isTerminal(currentSymbol)){
                firstSet[symbol].insert(currentSymbol);
                epsilonPossible = false;
                break;
            }
            else{
                findFirst(currentSymbol);
                bool hasEpsilon = false;
                for(string f : firstSet[currentSymbol]){
                    if(f == "e")
                        hasEpsilon = true;
                    else
                        firstSet[symbol].insert(f);
                }
                if(!hasEpsilon){
                    epsilonPossible = false;
                    break;
                }
            }
        }
        if(epsilonPossible) firstSet[symbol].insert("e");
    }
}

int main(){
    ifstream file("inputf.in");
    int n;
    file >> n;
    file.ignore(); 
    for(int i = 0; i < n; i++){
        string line;
        getline(file, line);
        stringstream ss(line);
        string lhs, rhs, eq;
        ss >> lhs >> eq >> rhs;
        grammar[lhs].push_back(rhs);
    }
    file.close();
    for(auto g : grammar) findFirst(g.first);
    cout << "FIRST sets:\n";
    for(auto g : firstSet){
        cout << "FIRST(" << g.first << ") = { ";
        for(string c : g.second)
            cout << c << " ";
        cout << "}" << endl;
    }
}