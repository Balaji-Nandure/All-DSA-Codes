// This greedy strategy works because pairing the smallest 
// elements of a[] with the largest elements of b[] ensures 
// that each sum is as large as possible,
//  giving the best chance for all pairs to meet or exceed k.

bool isPossible(vector<int>& a, vector<int>& b, int k) {
    
    // Sort a[] in ascending order
    sort(a.begin(), a.end());
    
    // Sort b[] in descending order
    sort(b.begin(), b.end(), greater<int>());

    // Check if every pair sum >= k
    for (int i = 0; i < a.size(); i++) {
        if (a[i] + b[i] < k)
            return false;
    }

    return true;
}