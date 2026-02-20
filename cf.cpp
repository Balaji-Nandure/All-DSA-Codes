#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tc; 
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }

        int sum = 0;
        int i = 0;

        while(i < n){
            int maxVal = a[i];
            bool isPositive = a[i] > 0;
            while(i < n && (a[i] > 0) == isPositive) {
                maxVal = max(maxVal, a[i]);
                i++;
            }
            sum += maxVal;
        }

        cout << sum << endl;
    }
}