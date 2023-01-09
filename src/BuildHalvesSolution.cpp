#include <string>

int main(int argc, char *argv[]) {
    (void)argc;
    int x = std::stoi(argv[0]);

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