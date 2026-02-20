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
    // code here
    if(n == 2) {cout << 2; return;}
    vector<int> primes = sieve(n);
    
    
    
    for(int x: primes){
        // cout << x << " ";
        while(n % x == 0){
            cout << x << " ";
            n /= x;
        }
    }
    
}