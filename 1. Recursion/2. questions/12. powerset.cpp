/*
Question: Print the power set (all subsets) of a string (distinct or not), using recursion and backtracking.

For example, for input string "abc":
Output (order may vary): "", "a", "b", "c", "ab", "ac", "bc", "abc"

Approach:
- For each character, either include or exclude it.
- Use recursion to try both possibilities for each character.
- Use backtracking to build and undo the current subset string in-place.
*/

// Print all subsets (powerset) of input string 'str' using recursion & backtracking
void powerSet(string &str, int idx, string &curr) {
    if (idx == str.length()) {
        cout << "\"" << curr << "\"" << endl;
        return;
    }
    // Exclude current char
    powerSet(str, idx + 1, curr);

    // Include current char (backtracking in-place)
    curr.push_back(str[idx]);
    powerSet(str, idx + 1, curr);
    curr.pop_back();
}

int main() {
    string str = "abc";
    cout << "All subsets (power set) of \"" << str << "\":" << endl;
    string curr = "";
    powerSet(str, 0, curr);
    return 0;
}
