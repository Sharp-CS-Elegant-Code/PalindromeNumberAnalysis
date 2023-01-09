class Solution {
public:
    bool isPalindrome(int x) {
        if (x == 0) {
            return true;
        }
        else if (x < 0) {
            return false;
        }

        std::string s = std::to_string(x);
        int i;
        for (i = 0; i < s.size() / 2; i++) {
            if (s[i] != s[s.size() - i - 1]) {
                return false;
            }
        }
        return true;
    }
};
