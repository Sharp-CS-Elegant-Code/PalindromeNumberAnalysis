#include <string>

int main(int argc, char *argv[]) {
    (void)argc;
    int x = std::stoi(argv[0]);
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
