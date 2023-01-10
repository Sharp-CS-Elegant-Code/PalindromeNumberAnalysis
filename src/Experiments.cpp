/*
File for running experiments.

Chami Lamelas
Jan 2023
*/

#include <limits.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "Solutions.h"

// Experiments configuration
const unsigned SEED = 1;
const int MAX_TRIALS_RUNTIME = 1000000;

// Set lower than runtime trials 
const int MAX_TRIALS_MEMORY = 1000;
const std::string SOLUTION_NAMES[] = {
    "BuildHalvesSolution", "CharArraySolution", "FastBuildHalvesSolution",
    "IntArraySolution",    "StringSolution",    "VectorSolution"};
const double KB_TO_MB_CONV = 1024.0;

// Gets minimum of 2 values assuming operator< is defined - left as macro to
// allow comparison between not the same type (e.g. double and int)
#define min(value1, value2) value1 < value2 ? value1 : value2

// Comparator that compares pairs by second member (i.e. value in context of
// maps)
template <typename ValueType>
struct PairValueComparator {
    bool operator()(const std::pair<std::string, ValueType> &pair1,
                    const std::pair<std::string, ValueType> &pair2) {
        return pair1.second < pair2.second;
    }
};

// Gets random number in [intervalMin, intervalMax] like Python's
// random.randint()
inline int getRandomNumber(int intervalMin, int intervalMax) {
    return (rand() % (intervalMax - intervalMin + 1)) + intervalMin;
}

// Gets smallest integer with ndigits digits
inline int getSmallest(int ndigits) { return pow(10, ndigits - 1); }

// Gets largest integer with ndigits digits if possible, else INT_MAX
inline int getLargest(int ndigits) {
    return min(pow(10, ndigits) - 1, INT_MAX);
}

// Gets the number of trials to be done for tests of ndigits digit numbers
// (capped off by MAX_NDIGITS_TRIALS)
inline int getNumTrials(int ndigits, int maxTrials) {
    return min(getLargest(ndigits) - getSmallest(ndigits) + 1, maxTrials);
}

// Gets random number with ndigits (defaults to positive)
int getRandomNDigitNumber(int ndigits, bool negative = false) {
    int number = getRandomNumber(getSmallest(ndigits), getLargest(ndigits));
    return negative ? -number : number;
}

// Load a bunch of numbers to trial for 1-10 digit numbers (simulate LeetCode
// test case range). No attempt is made to be biased toward palindrome v.
// non-palindrome numbers. Non-palindrome numbers will constitute a large
// majority.
void getTrials(std::list<int> &trials, int maxTrials) {
    int ndigits, trial;
    for (ndigits = 1; ndigits <= 10; ndigits++) {
        trials.push_back(getRandomNDigitNumber(ndigits, true));
        for (trial = 0; trial < getNumTrials(ndigits, maxTrials); trial++) {
            trials.push_back(getRandomNDigitNumber(ndigits));
        }
    }
}

// Turns difference between time points into a int64_t time in milliseconds
inline int64_t getRuntime(const std::chrono::steady_clock::time_point &begin,
                          const std::chrono::steady_clock::time_point &end) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
        .count();
}

void tryToOpen(std::ofstream &file, const std::string &fp) {
    file.open(fp);
    if (not file.is_open()) {
        std::cerr << fp << " cannot be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void getRuntimes(const std::list<int> &trials,
                 std::unordered_map<std::string, int64_t> &runtimes) {
    std::chrono::steady_clock::time_point begin, end;

    begin = std::chrono::steady_clock::now();
    for (int trial : trials) {
        BuildHalvesSolution(trial);
    }
    end = std::chrono::steady_clock::now();
    runtimes["BuildHalvesSolution"] = getRuntime(begin, end);

    begin = std::chrono::steady_clock::now();
    for (int trial : trials) {
        CharArraySolution(trial);
    }
    end = std::chrono::steady_clock::now();
    runtimes["CharArraySolution"] = getRuntime(begin, end);

    begin = std::chrono::steady_clock::now();
    for (int trial : trials) {
        FastBuildHalvesSolution(trial);
    }
    end = std::chrono::steady_clock::now();
    runtimes["FastBuildHalvesSolution"] = getRuntime(begin, end);

    begin = std::chrono::steady_clock::now();
    for (int trial : trials) {
        IntArraySolution(trial);
    }
    end = std::chrono::steady_clock::now();
    runtimes["IntArraySolution"] = getRuntime(begin, end);

    begin = std::chrono::steady_clock::now();
    for (int trial : trials) {
        StringSolution(trial);
    }
    end = std::chrono::steady_clock::now();
    runtimes["StringSolution"] = getRuntime(begin, end);

    begin = std::chrono::steady_clock::now();
    for (int trial : trials) {
        VectorSolution(trial);
    }
    end = std::chrono::steady_clock::now();
    runtimes["VectorSolution"] = getRuntime(begin, end);
}

double getMemory(const std::string &solution, int x) {
    // %M formats just the max RAM usage, 2>&1 collects stderr (where
    // /usr/bin/time dumps to)
    std::string command = "/usr/bin/time -f %M ./" + solution + ".out " +
                          std::to_string(x) + " 2>&1";
    FILE *pipe = popen(command.c_str(), "r");
    const unsigned BUFFER_READ_SIZE = 255;
    char buffer[BUFFER_READ_SIZE];
    fgets(buffer, BUFFER_READ_SIZE, pipe);
    pclose(pipe);
    // Convert char * to string and strip trailing newline
    std::string kbstr = buffer;
    int kb = std::stoi(kbstr.substr(0, kbstr.size() - 1));
    return kb / KB_TO_MB_CONV;
}

double calculateMean(const std::list<double> &values) {
    double sum = 0;
    for (double v : values) {
        sum += v;
    }
    return sum / values.size();
}

void getMemories(const std::list<int> &trials,
                 std::unordered_map<std::string, double> &memories) {
    std::unordered_map<std::string, std::list<double>> byTrialMemories;

    // Initialize empty list
    std::list<double> emptyList;
    for (const auto &p : memories) {
        byTrialMemories[p.first] = emptyList;
    }

    for (int trial : trials) {
        for (const std::string &name : SOLUTION_NAMES) {
            byTrialMemories[name].push_back(getMemory(name, trial));
        }
    }

    for (const std::string &name : SOLUTION_NAMES) {
        memories[name] = calculateMean(byTrialMemories.at(name));
    }
}

void saveStatistics(const std::unordered_map<std::string, int64_t> &runtimes,
                    const std::unordered_map<std::string, double> &memories) {
    std::vector<std::pair<std::string, int64_t>> runtimePairs;
    for (const auto &p : runtimes) {
        runtimePairs.push_back(std::make_pair(p.first, p.second));
    }
    PairValueComparator<int64_t> runtimeComparator;
    std::sort(runtimePairs.begin(), runtimePairs.end(), runtimeComparator);

    std::ofstream file;
    tryToOpen(file, "../results/my_runtime.csv");
    file << "Solution,Runtime (ms),Rank\n";
    size_t i;
    for (i = 0; i < runtimePairs.size(); i++) {
        file << runtimePairs[i].first << ',' << runtimePairs[i].second << ','
             << (i + 1) << '\n';
    }
    file.close();

    std::vector<std::pair<std::string, double>> memoryPairs;
    for (const auto &p : memories) {
        memoryPairs.push_back(std::make_pair(p.first, p.second));
    }
    PairValueComparator<double> memoryComparator;
    std::sort(memoryPairs.begin(), memoryPairs.end(), memoryComparator);

    tryToOpen(file, "../results/my_memory.csv");
    file << "Solution,Memory (MB),Rank\n";
    for (i = 0; i < memoryPairs.size(); i++) {
        file << memoryPairs[i].first << ',' << memoryPairs[i].second << ','
             << (i + 1) << '\n';
    }
    file.close();
}

int main() {
    srand(SEED);

    std::list<int> runtimeTrials, memoryTrials;
    getTrials(runtimeTrials, MAX_TRIALS_RUNTIME);
    getTrials(memoryTrials, MAX_TRIALS_MEMORY);

    std::unordered_map<std::string, int64_t> runtimes;
    getRuntimes(runtimeTrials, runtimes);
    std::cerr << "Finished " << runtimeTrials.size() << " runtime trials." << std::endl;

    std::unordered_map<std::string, double> memories;
    getMemories(memoryTrials, memories);
    std::cerr << "Finished " << memoryTrials.size() << " memory trials." << std::endl;
    
    saveStatistics(runtimes, memories);
    return EXIT_SUCCESS;
}