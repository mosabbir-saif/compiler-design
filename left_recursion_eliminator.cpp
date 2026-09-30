#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    string production;
    cin >> production;
    string left = "";
    string right = "";
    int pos = production.find("->");
    left = production.substr(0, pos);
    right = production.substr(pos + 2);
    vector<string> rules;
    string temp = "";
    for(char c : right){
        if(c == '|'){
            rules.push_back(temp);
            temp = "";
        }
        else temp += c;
    }
    rules.push_back(temp);
    vector<string> alpha; 
    vector<string> beta; 
    for(string s : rules){
        if(s[0] == left[0]) alpha.push_back(s.substr(1));
        else beta.push_back(s);
    }
    if(alpha.empty()){
        cout << "No Left Recursion Found" << endl;
        return 0;
    }
    cout << left << "->";
    for(int i = 0; i < beta.size(); i++){
        cout << beta[i] << left << "'";
        if(i != beta.size() - 1) cout << "|";
    }
    cout << endl;
    cout << left << "'->";
    for(int i = 0; i < alpha.size(); i++) cout << alpha[i] << left << "'|";
    cout << "e" << endl;

}