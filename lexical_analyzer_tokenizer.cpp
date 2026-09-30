#include<bits/stdc++.h>
using namespace std;
bool isOperator(char ch){
    string op="+-*/%=<>!&|^";
    return op.find(ch)!=string::npos;
}
bool isSpecialSymbol(char ch){
    string sym="(){}[];,.:#";
    return sym.find(ch)!=string::npos;
}
bool isKeyword(string s){
    set<string> kw={
        "int","float","double","char","string","if","else","for","while","do",
        "return","break","continue","void","switch","case","default","bool",
        "long","short","signed","unsigned","include","using","namespace","std"
    };
    return kw.count(s);
}
int main(){
    ifstream file("inputf.in");
    if(!file){
        cout<<"Cannot open file!"<<endl;
        return 0;
    }
    char ch;
    while(file.get(ch)){
        if(ch==' '||ch=='\t'||ch=='\n')
            continue;
        if(ch=='/'){
            char next=file.peek();
            if(next=='/'){
                while(file.get(ch)&&ch!='\n');
                continue;
            }
            else if(next=='*'){
                file.get(ch);
                char prev=0;
                while(file.get(ch)){
                    if(prev=='*'&&ch=='/')
                        break;
                    prev=ch;
                }
                continue;
            }
        }
        if(isalpha(ch)||ch=='_'){
            string token;
            token+=ch;
            while(file.peek()!=EOF&&(isalnum(file.peek())||file.peek()=='_')){
                file.get(ch);
                token+=ch;
            }
            if(isKeyword(token))
                cout<<token<<endl;
            else
                cout<<token<<endl;
        }
        else if(isdigit(ch)){
            string token;
            token+=ch;
            while(file.peek()!=EOF&&isdigit(file.peek())){
                file.get(ch);
                token+=ch;
            }
            cout<<token<<endl;
        }
        else if(isOperator(ch)){
            string token;
            token+=ch;
            char next=file.peek();
            if((ch=='+'&&next=='+')||
               (ch=='-'&&next=='-')||
               (ch=='='&&next=='=')||
               (ch=='!'&&next=='=')||
               (ch=='<'&&next=='=')||
               (ch=='>'&&next=='=')||
               (ch=='&'&&next=='&')||
               (ch=='|'&&next=='|')){
                file.get(ch);
                token+=ch;
            }
            cout<<token<<endl;
        }
        else if(isSpecialSymbol(ch)){
            cout<<ch<<endl;
        }
        else{
            cout<<ch<<endl;
        }
    }
    file.close();
}