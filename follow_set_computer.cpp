#include <bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> grammar;
map<string, set<string>> firstSet;
map<string, set<string>> followSet;

bool isTerminal(string s){
    return s.empty() || !isupper(s[0]);
}

void findFirst(){
    bool changed = true;
    while(changed){
        changed = false;
        for(auto g : grammar){
            string symbol = g.first;
            int oldSize = firstSet[symbol].size();
            for(vector<string> production : g.second){
                bool epsilonPossible = true;
                for(string currentSymbol : production){
                    if(isTerminal(currentSymbol)){
                        firstSet[symbol].insert(currentSymbol);
                        epsilonPossible = false;
                        break;
                    }
                    else{
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
            if(firstSet[symbol].size() != oldSize) changed = true;
        }
    }
}

vector<string> tokenize(string production){
    vector<string> symbols;
    for(int i = 0; i < production.length();){
        if(production[i] == ' '){
            i++;
            continue;
        }
        if(i + 1 < production.length() && production[i] == 'i' && production[i + 1] == 'd'
           && !isalpha(production[i + 2])){
            symbols.push_back("id");
            i += 2;
        }
        else if (i + 1 < production.length() && production[i + 1] == '\''){
            symbols.push_back(production.substr(i, 2));
            i += 2;
        }
        else{
            symbols.push_back(string(1, production[i]));
            i++;
        }
    }
    return symbols;
}

set<string> firstOfTail(vector<string>& symbols, int i, bool& epsilonPossible){
    set<string> result;
    epsilonPossible = true;
    for(int k = i; k < symbols.size(); k++){
        if(isTerminal(symbols[k])){
            result.insert(symbols[k]);
            epsilonPossible = false;
            break;
        }
        bool hasEpsilon = false;
        for(string f : firstSet[symbols[k]]){
            if(f == "e")
                hasEpsilon = true;
            else
                result.insert(f);
        }
        if(!hasEpsilon){
            epsilonPossible = false;
            break;
        }
    }
    return result;
}

int main(){
    ifstream file("inputf.in");
    string line, firstLhs;
    set<string> appearOnRhs;
    while(getline(file, line)){
        stringstream ss(line);
        string lhs, eq, token, rhs;
        if(!(ss >> lhs >> eq)) continue;
        while(ss >> token) rhs += token;
        // a lone "e" on the rhs marks an epsilon production, not the terminal e
        vector<string> symbols = rhs == "e" ? vector<string>() : tokenize(rhs);
        for(string s : symbols)
            if(!isTerminal(s)) appearOnRhs.insert(s);
        grammar[lhs].push_back(symbols);
        if(firstLhs.empty()) firstLhs = lhs;
    }
    file.close();
    findFirst();

    // the start symbol is the lhs of the first rule, unless exactly one
    // nonterminal never appears on the rhs of any production
    vector<string> roots;
    for(auto g : grammar)
        if(!isTerminal(g.first) && !appearOnRhs.count(g.first)) roots.push_back(g.first);
    followSet[roots.size() == 1 ? roots[0] : firstLhs].insert("$");

    bool changed = true;
    while(changed){
        changed = false;
        for(auto g : grammar){
            for(vector<string> symbols : g.second){
                for(int i = 0; i < symbols.size(); i++){
                    if(isTerminal(symbols[i])) continue;
                    int oldSize = followSet[symbols[i]].size();
                    bool epsilonPossible;
                    set<string> tailFirst = firstOfTail(symbols, i + 1, epsilonPossible);
                    for(string f : tailFirst)
                        followSet[symbols[i]].insert(f);
                    if(epsilonPossible)
                        followSet[symbols[i]].insert(followSet[g.first].begin(), followSet[g.first].end());
                    if(followSet[symbols[i]].size() != oldSize) changed = true;
                }
            }
        }
    }

    cout << "FOLLOW sets:\n";
    for(auto g : grammar){
        cout << "FOLLOW(" << g.first << ") = { ";
        for(string c : followSet[g.first])
            cout << c << " ";
        cout << "}" << endl;
    }
}
