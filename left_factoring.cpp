#include <bits/stdc++.h>
using namespace std;
vector<string> split(string s){
    vector<string> v;
    string temp="";
    for(char c:s){
        if(c=='|'){
            v.push_back(temp);
            temp="";
        }
        else temp+=c;
    }
    v.push_back(temp);
    return v;
}
string lcp(vector<string>& v){
    string prefix=v[0];
    for(int i=1;i<v.size();i++){
        int len=min(prefix.size(),v[i].size());
        int j=0;
        while(j<len && prefix[j]==v[i][j]) j++;
        prefix=prefix.substr(0,j);
        if(prefix=="") break;
    }
    return prefix;
}
int main(){
    string input;
    cin>>input;
    int pos=input.find("->");
    string A=input.substr(0,pos);
    string rhs=input.substr(pos+2);
    vector<string> prod=split(rhs);
    unordered_map<char, vector<string>> groups;
    for(auto &p:prod)
        groups[p[0]].push_back(p);
    bool changed=false;
    for(auto &g:groups){
        if(g.second.size()>1){
            string prefix=lcp(g.second);
            if(prefix!=""){
                changed=true;
                string A1=A+"'";
                cout<<A<<" -> "<<prefix<<A1;
                for(auto &p:groups){
                    if(p.first!=g.first){
                        for(auto &x:p.second)
                            cout<<" | "<<x;
                    }
                }
                cout<<endl;
                cout<<A1<<" -> ";
                for(int i=0;i<g.second.size();i++){
                    string rem=g.second[i].substr(prefix.size());
                    if(rem=="") rem="ε";
                    cout<<rem;
                    if(i!=g.second.size()-1) cout<<" | ";
                }
                cout<<endl;
                return 0;
            }
        }
    }
    cout<<"No Left Factoring Needed"<<endl;
}