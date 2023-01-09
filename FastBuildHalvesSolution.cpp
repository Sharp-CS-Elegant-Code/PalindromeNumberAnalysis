class Solution {
public:
    bool isPalindrome(int x) {
        if (x == 0) {
            return true;
        }
        // For x != 0 and ends with 0 then its impossible to be a palindrome b/c number couldn't start with 0
        else if (x < 0 || x % 10 == 0) {
            return false;
        }
        
        /*
        Case where x has 2 digits and 1st digit > 2nd digit (e.g. x = 21):
            backHalf stores the whole number x and x becomes 0
        Else:
            backHalf stores the back half of x including the middle digit if x 
            has an odd number of digits and x holds the remaining front digits
        */
        int backHalf = 0;
        while (x > backHalf) {
            backHalf = (10 * backHalf) + (x % 10);
            x /= 10;
        }

        return (x == backHalf) || (x == (backHalf / 10));
    }
};
