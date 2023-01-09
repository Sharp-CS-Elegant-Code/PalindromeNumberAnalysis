#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    (void)argc;
    int x = std::stoi(argv[0]);
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
