#include <bits/stdc++.h>
using namespace std;

bool isPalindrome1(string &s, int l, int r){
    if (l >= r) return true;
    if (s[l] != s[r]) return false;
    return isPalindrome1(s, l+1, r-1);
} 

bool isPalindrome2(string &s, int i){
    if (i >= s.size()/2) return true;
    if (s[i] != s[s.size()-i-1]) return false;
    return isPalindrome2(s, i+1);
}

signed main() {
    string s = "madam";
    cout << isPalindrome1(s, 0, s.size()-1) << endl;

    cout << isPalindrome2(s, 0) << endl;
    return 0;
}