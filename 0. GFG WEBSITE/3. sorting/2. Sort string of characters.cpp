void sortString(string& s) {
    /*
    Approach:
    1. Count frequency of each character using a frequency array.
    2. Characters are lowercase English letters ('a' to 'z').
    3. Rebuild the string in sorted order using the frequency counts.

    Time: O(n)
    Space: O(1)  // fixed size 26
    */

    vector<int> freq(26, 0);

    // Count frequencies
    for (char c : s) {
        freq[c - 'a']++;
    }

    // Rebuild sorted string
    int idx = 0;
    for (int i = 0; i < 26; i++) {
        while (freq[i]--) {
            s[idx++] = char('a' + i);
        }
    }
}
