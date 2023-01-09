class Solution {
public:
    bool isPalindrome(int x) {
        if (x == 0) {
            return true;
        }
        else if (x < 0) {
            return false;
        }

        std::vector<int> digits;
        while (x > 0) {
            digits.push_back(x % 10);
            x /= 10;
        }

        int i;
        for (i = 0; i < digits.size() / 2; i++) {
            if (digits[i] != digits[digits.size() - i - 1]) {
                return false;
            }
        }
        return true;
    }
};
