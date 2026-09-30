#include <bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> grammar;
map<string, set<string>> firstSet;
map<string, set<string>> followSet;
map<string, map<string, vector<int>>> parseTable;
set<string> terminals;
set<string> nonTerminals;
string startSymbol;

bool isTerminal(string s){
    return s.empty() || !isupper(s[0]);
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

string join(vector<string>& symbols){
    string result;
    if(symbols.empty()) return "e";
    for(string s : symbols) result += s;
    return result;
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

void findFollow(){
    followSet[startSymbol].insert("$");
    bool changed = true;
    while(changed){
        changed = false;
        for(auto g : grammar){
            for(vector<string> symbols : g.second){
                for(int i = 0; i < symbols.size(); i++){
                    if(isTerminal(symbols[i])) continue;
                    int oldSize = followSet[symbols[i]].size();
                    bool epsilonPossible = true;
                    for(int k = i + 1; k < symbols.size(); k++){
                        if(isTerminal(symbols[k])){
                            followSet[symbols[i]].insert(symbols[k]);
                            epsilonPossible = false;
                            break;
                        }
                        bool hasEpsilon = false;
                        for(string f : firstSet[symbols[k]]){
                            if(f == "e")
                                hasEpsilon = true;
                            else
                                followSet[symbols[i]].insert(f);
                        }
                        if(!hasEpsilon){
                            epsilonPossible = false;
                            break;
                        }
                    }
                    if(epsilonPossible)
                        followSet[symbols[i]].insert(followSet[g.first].begin(), followSet[g.first].end());
                    if(followSet[symbols[i]].size() != oldSize) changed = true;
                }
            }
        }
    }
}

void buildParseTable(){
    for(auto g : grammar){
        string lhs = g.first;
        for(int p = 0; p < g.second.size(); p++){
            vector<string> rhs = g.second[p];
            bool epsilonPossible = true;
            for(string s : rhs){
                if(isTerminal(s)){
                    parseTable[lhs][s].push_back(p);
                    epsilonPossible = false;
                    break;
                }
                bool hasEpsilon = false;
                for(string f : firstSet[s]){
                    if(f == "e")
                        hasEpsilon = true;
                    else
                        parseTable[lhs][f].push_back(p);
                }
                if(!hasEpsilon){
                    epsilonPossible = false;
                    break;
                }
            }
            if(epsilonPossible)
                for(string f : followSet[lhs])
                    parseTable[lhs][f].push_back(p);
        }
    }
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
        for(string s : symbols){
            if(isTerminal(s)) terminals.insert(s);
            else appearOnRhs.insert(s);
        }
        if(!isTerminal(lhs)) nonTerminals.insert(lhs);
        grammar[lhs].push_back(symbols);
        if(firstLhs.empty()) firstLhs = lhs;
    }
    file.close();

    vector<string> roots;
    for(string nt : nonTerminals)
        if(!appearOnRhs.count(nt)) roots.push_back(nt);
    startSymbol = roots.size() == 1 ? roots[0] : firstLhs;

    findFirst();
    findFollow();
    buildParseTable();
    terminals.insert("$");

    vector<string> terminalList(terminals.begin(), terminals.end());
    vector<string> nonTerminalList(nonTerminals.begin(), nonTerminals.end());

    bool isLL1 = true;
    for(string nt : nonTerminalList)
        for(auto cell : parseTable[nt])
            if(cell.second.size() > 1) isLL1 = false;

    int width = 4;
    for(string t : terminalList) width = max(width, (int)t.length() + 1);
    for(string nt : nonTerminalList) width = max(width, (int)nt.length() + 1);
    for(string nt : nonTerminalList)
        for(string t : terminalList)
            if(parseTable[nt].count(t) && !parseTable[nt][t].empty())
                width = max(width, (int)(nt + " -> " + join(grammar[nt][parseTable[nt][t][0]])).length() + 1);

    cout << "\nLL(1) parse table:\n";
    cout << setw(width);
    for(string t : terminalList) cout << setw(width) << t;
    cout << "\n";
    for(string nt : nonTerminalList){
        cout << setw(width) << nt;
        for(string t : terminalList){
            string entry;
            if(parseTable[nt].count(t) && !parseTable[nt][t].empty())
                entry = nt + " -> " + join(grammar[nt][parseTable[nt][t][0]]);
            cout << setw(width) << entry;
        }
        cout << "\n";
    }
    if(!isLL1){
        cout << "Grammar is NOT LL(1): some cells hold more than one production\n";
        return 0;
    }
    cout << "Grammar is LL(1)\n";

    string inputLine;
    cout << "\nEnter the input string: ";
    getline(cin, inputLine);
    vector<string> input = tokenize(inputLine);
    for(string s : input)
        if(!isTerminal(s)){
            cout << "Input must contain terminals only: " << s << endl;
            return 0;
        }
    input.push_back("$");

    vector<string> stack;
    stack.push_back("$");
    stack.push_back(startSymbol);

    cout << "\nStep | Stack | Input | Action\n";
    int step = 0, ip = 0;
    bool accepted = false;
    while(step < 1000){
        step++;
        string top = stack.back();
        string current = input[ip];
        string stackText, inputText;
        for(string s : stack) stackText += s;
        for(int i = ip; i < input.size(); i++) inputText += input[i];
        if(top == "$" && current == "$"){
            cout << step << " | " << stackText << " | " << inputText << " | Accept\n";
            accepted = true;
            break;
        }
        if(isTerminal(top)){
            if(top == current){
                cout << step << " | " << stackText << " | " << inputText << " | Match " << top << "\n";
                stack.pop_back();
                ip++;
            }
            else{
                cout << step << " | " << stackText << " | " << inputText << " | Error: expected " << top << " found " << current << "\n";
                break;
            }
        }
        else{
            if(!parseTable[top].count(current) || parseTable[top][current].empty()){
                cout << step << " | " << stackText << " | " << inputText << " | Error: no entry for (" << top << ", " << current << ")\n";
                break;
            }
            vector<string> rhs = grammar[top][parseTable[top][current][0]];
            cout << step << " | " << stackText << " | " << inputText << " | " << top << " -> " << join(rhs) << "\n";
            stack.pop_back();
            for(int i = rhs.size() - 1; i >= 0; i--) stack.push_back(rhs[i]);
        }
    }
    cout << (accepted ? "\nInput accepted\n" : "\nInput rejected\n");
}
