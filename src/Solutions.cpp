/*
Implementation of my solutions described in header.

Chami Lamelas
Jan 2023
*/

#include <string>
#include <vector>

bool BuildHalvesSolution(int x) {
    if (x == 0) {
        return true;
    } else if (x < 0) {
        return false;
    }

    /*
    Calculates:
        nDigits - number of digits in x
        tenPower - largest power of 10 < x
    */
    int xCpy = x, nDigits = 0;
    size_t tenPower = 1;
    while (xCpy > 0) {
        xCpy /= 10;
        tenPower *= 10;
        nDigits++;
    }
    // If x = 123, above loop calculates tenPower = 1000 (want 100)
    tenPower /= 10;

    /*
    Calculates:
        reversedFrontHalf - front half (halves don't include middle digit
        if nDigits is odd) of digits of x in reverse order (for x = 12345,
        this would be 21) (tenPowerTwo is used to build it, tenPower is
        used to strip digits from left)
    */
    int reversedFrontHalf = 0, i;
    size_t tenPowerTwo = 1;
    xCpy = x;
    for (i = 0; i < nDigits / 2; i++) {
        reversedFrontHalf += tenPowerTwo * (xCpy / tenPower);
        xCpy %= tenPower;
        tenPower /= 10;
        tenPowerTwo *= 10;
    }

    /*
    Calculates:
        backHalf - back half of digits of x (tenPower is used to build it
        in addition to right stripping digits from x)
    */
    int backHalf = 0;
    tenPower = 1;
    for (i = 0; i < nDigits / 2; i++) {
        backHalf += tenPower * (x % 10);
        tenPower *= 10;
        x /= 10;
    }

    return reversedFrontHalf == backHalf;
}

bool CharArraySolution(int x) {
    if (x == 0) {
        return true;
    } else if (x < 0) {
        return false;
    }

    int nDigits = 0, xBackup = x;
    while (x > 0) {
        nDigits++;
        x /= 10;
    }
    char *digits = new char[nDigits];
    char *forward = digits, *backward = digits + nDigits - 1;
    while (xBackup > 0) {
        *forward = xBackup % 10;
        xBackup /= 10;
        forward++;
    }

    forward = digits;
    int i;
    for (i = 0; i < nDigits / 2; i++) {
        if (*backward != *forward) {
            return false;
        }
        backward--;
        forward++;
    }

    delete[] digits;
    return true;
}

bool FastBuildHalvesSolution(int x) {
    if (x == 0) {
        return true;
    }
    // For x != 0 and ends with 0 then its impossible to be a palindrome b/c
    // number couldn't start with 0
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

bool IntArraySolution(int x) {
    if (x == 0) {
        return true;
    } else if (x < 0) {
        return false;
    }

    int nDigits = 0, xBackup = x;
    while (x > 0) {
        nDigits++;
        x /= 10;
    }
    int *digits = new int[nDigits];
    int *forward = digits, *backward = digits + nDigits - 1;
    while (xBackup > 0) {
        *forward = xBackup % 10;
        xBackup /= 10;
        forward++;
    }

    forward = digits;
    int i;
    for (i = 0; i < nDigits / 2; i++) {
        if (*backward != *forward) {
            return false;
        }
        backward--;
        forward++;
    }

    delete[] digits;
    return true;
}

bool StringSolution(int x) {
    if (x == 0) {
        return true;
    } else if (x < 0) {
        return false;
    }

    std::string s = std::to_string(x);
    size_t i;
    for (i = 0; i < s.size() / 2; i++) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}


bool VectorSolution(int x) {
    if (x == 0) {
        return true;
    } else if (x < 0) {
        return false;
    }

    std::vector<int> digits;
    while (x > 0) {
        digits.push_back(x % 10);
        x /= 10;
    }

    size_t i;
    for (i = 0; i < digits.size() / 2; i++) {
        if (digits[i] != digits[digits.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
