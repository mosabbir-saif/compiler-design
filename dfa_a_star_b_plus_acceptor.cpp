#include <bits/stdc++.h>
using namespace std;
bool check_a_star_b_plus(string s){
    int i = 0;
    int n = s.size();
    while(i < n && s[i] == 'a') i++;
    int b_count = 0;
    while(i < n && s[i] == 'b'){
        i++;
        b_count++;
    }
    return (b_count > 0 && i == n);
}
signed main(){
    string s; cin >> s;
    if(s == "a") cout << "Accepted (pattern: a)" << endl;
    else if(s == "abb") cout << "Accepted (pattern: abb)" << endl;
    else if(check_a_star_b_plus(s)) cout << "Accepted (pattern: a*b+)" << endl;
    else cout << "Rejected" << endl;
}