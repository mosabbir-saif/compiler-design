#include <bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> grammar;
vector<string> inputTokens;
vector<vector<string>> sententialForms;
vector<string> usedProduction;
map<string, int> minLen;
const int SEARCH_LIMIT = 200000;
int attempts = 0;

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

// the leading terminals of a sentential form must already match the input
bool matchesPrefix(vector<string>& form){
    int i = 0;
    while(i < form.size() && isTerminal(form[i])){
        if(i >= inputTokens.size() || form[i] != inputTokens[i]) return false;
        i++;
    }
    return true;
}

bool isDone(vector<string>& form){
    for(string s : form)
        if(!isTerminal(s)) return false;
    return form.size() == inputTokens.size();
}

// fewest terminals each nonterminal can produce, used to cut off branches
// whose sentential form can no longer shrink to the given input length
void computeMinLen(){
    const int INF = 1000000;
    for(auto g : grammar) minLen[g.first] = INF;
    bool changed = true;
    while(changed){
        changed = false;
        for(auto g : grammar){
            for(vector<string> production : g.second){
                int cost = 0;
                for(string s : production)
                    cost += isTerminal(s) ? 1 : minLen[s];
                if(cost < minLen[g.first]){
                    minLen[g.first] = cost;
                    changed = true;
                }
            }
        }
    }
}

int formMinLen(vector<string>& form){
    const int INF = 1000000;
    int total = 0;
    for(string s : form){
        if(isTerminal(s)) total++;
        else{
            if(!minLen.count(s)) return INF;
            total += minLen[s];
        }
    }
    return total;
}

bool leftMostDerivation(vector<string> form){
    if(++attempts > SEARCH_LIMIT) return false;
    sententialForms.push_back(form);
    if(isDone(form)) return true;
    int index = -1;
    for(int i = 0; i < form.size(); i++)
        if(!isTerminal(form[i])){ index = i; break; }
    if(index == -1) return false;
    string symbol = form[index];
    for(vector<string> production : grammar[symbol]){
        vector<string> next;
        for(int i = 0; i < index; i++) next.push_back(form[i]);
        for(string s : production) next.push_back(s);
        for(int i = index + 1; i < form.size(); i++) next.push_back(form[i]);
        if(!matchesPrefix(next) || formMinLen(next) > (int)inputTokens.size()) continue;
        usedProduction.push_back(symbol + " -> " + join(production));
        if(leftMostDerivation(next)) return true;
        usedProduction.pop_back();
    }
    sententialForms.pop_back();
    return false;
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
    computeMinLen();

    // the start symbol is the lhs of the first rule, unless exactly one
    // nonterminal never appears on the rhs of any production
    vector<string> roots;
    for(auto g : grammar)
        if(!isTerminal(g.first) && !appearOnRhs.count(g.first)) roots.push_back(g.first);
    string startSymbol = roots.size() == 1 ? roots[0] : firstLhs;

    string inputLine;
    cout << "Enter the input string: ";
    getline(cin, inputLine);
    inputTokens = tokenize(inputLine);
    for(string s : inputTokens)
        if(!isTerminal(s)){
            cout << "Input must contain terminals only: " << s << endl;
            return 0;
        }

    vector<string> start = {startSymbol};
    if(!leftMostDerivation(start)){
        if(attempts > SEARCH_LIMIT)
            cout << "Search limit reached, no derivation found" << endl;
        else
            cout << "No leftmost derivation exists for this input" << endl;
        return 0;
    }
    cout << "\nLeftmost derivation of " << inputLine << ":\n";
    for(int i = 0; i < sententialForms.size(); i++){
        cout << join(sententialForms[i]);
        if(i > 0) cout << "   [" << usedProduction[i - 1] << "]";
        cout << endl;
    }
}
