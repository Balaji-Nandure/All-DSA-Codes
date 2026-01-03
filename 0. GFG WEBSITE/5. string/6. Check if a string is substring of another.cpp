class Solution {
    public:
      int firstOccurence(string& str, string& sub) {
          // code here
          auto ans = str.find(sub);
          
          if(ans == string::npos) return -1;
          return ans;
      }
  };