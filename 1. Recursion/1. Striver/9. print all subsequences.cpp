#include <bits/stdc++.h>
using namespace std;

void printSubsequences(int i, string &ans, string &s){
    if(i == s.size()){
        if(ans.size() == 0) {
            // just to see empty string also printed
            cout << "NULL" << endl;
            return;
        }else{
            cout << ans << endl;
            return;
        }
    }
    // take
    ans.push_back(s[i]);
    printSubsequences(i+1, ans, s);
    // restore the state
    ans.pop_back();

    // not take
    printSubsequences(i+1, ans, s);
}

// reverse order. 
// do not take condition first then take condition
void printSubsequences2(int i, string &ans, string &s){
    if(i == s.size()){
        if(ans.size() == 0) {
            // just to see empty string also printed
            cout << "NULL" << endl;
            return;
        }else{
            cout << ans << endl;
            return;
        }
    }

    // not take
    printSubsequences2(i+1, ans, s);

    // take
    ans.push_back(s[i]);
    printSubsequences2(i+1, ans, s);
    // restore the state
    ans.pop_back();
}

int main() {

    string s = "abc";
    string ans = "";

    printSubsequences2(0, ans, s);
}