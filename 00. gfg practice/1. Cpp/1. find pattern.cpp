/*
Question:
Given a string s, and a pattern p. You need to find if p exists in s or not 
and return the starting index of p in s. If p does not exist in s then -1 
will be returned.

Here p and s both are case-sensitive.

Examples:

Input: s = "Hello", p = "llo"
Output: 2
Explanation: llo starts from the second index in Hello.

Input: s = "World", p = "Doodle"
Output: -1
Explanation: Both are different.
*/

#include <iostream>
#include <string>
using namespace std;

int findPattern(string s, string p) {
    int n = s.length();
    int m = p.length();
    
    if (m > n) return -1;
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (s[i + j] != p[j]) {
                break;
            }
        }
        if (j == m) {
            return i;
        }
    }
    return -1;
}

int main() {
    string s1 = "Hello";
    string p1 = "llo";
    cout << "Input: s = \"" << s1 << "\", p = \"" << p1 << "\"" << endl;
    cout << "Output: " << findPattern(s1, p1) << endl;
    
    string s2 = "World";
    string p2 = "Doodle";
    cout << "Input: s = \"" << s2 << "\", p = \"" << p2 << "\"" << endl;
    cout << "Output: " << findPattern(s2, p2) << endl;
    
    return 0;
}


/*
Prime Factorization

Difficulty: Easy
Accuracy: 56.33%
Submissions: 50K+
Points: 2

Given a number n find the prime factorization of the number.
Note: Print the prime factors in non-decreasing order.

Examples:

Input: n = 100
Output: 2 2 5 5
Explanation: 100 = 2 * 2 * 5 * 5

Input: n = 27
Output: 3 3 3
Explanation: 27 = 3 * 3 * 3
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> sieve(int n) {
    vector<int> result;
    vector<bool> sv(n + 1, true);
    
    for(int i = 2; i <= n; i++){
        if(sv[i]){
            result.push_back(i);
            for(int j = i * i; j <= n; j += i){
                sv[j] = false;
            }
        }
    }
    
    return result;
}

void printPrimeFactorization(int n) {
    if(n == 1) return;
    if(n == 2) {cout << 2; return;}
    vector<int> primes = sieve(n);
    
    bool first = true;
    for(int x: primes){
        while(n % x == 0){
            if(!first) cout << " ";
            cout << x;
            first = false;
            n /= x;
        }
        if(n == 1) break;
    }
}

int main() {
    int n1 = 100;
    cout << "Input: n = " << n1 << endl;
    cout << "Output: ";
    printPrimeFactorization(n1);
    cout << endl;
    
    int n2 = 27;
    cout << "Input: n = " << n2 << endl;
    cout << "Output: ";
    printPrimeFactorization(n2);
    cout << endl;
    
    return 0;
}













