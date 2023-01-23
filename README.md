# Palindrome Number Analysis

Jan 2023

## Description

In this repository, I did some runtime and memory analysis of various solutions on [Palindrome Number LeetCode problem](https://leetcode.com/problems/palindrome-number/description/) after getting some unexpected performance results on LeetCode. The solutions are provided in `src/Solutions.cpp`. It turns out, as seen on various discussions [[1]](https://leetcode.com/discuss/general-discussion/136683/different-run-time-with-same-code)[[2]](https://leetcode.com/discuss/feedback/1539664/is-leetcode-runtime-and-memory-measure-consistent)[[3]](https://stackoverflow.com/questions/51131257/difference-in-running-time-on-leet-code), that LeetCode's metrics are not very consistent. My experiment script does two things: 

1. It runs each of six solutions on a series of around five million numbers and [measures the total runtime](https://stackoverflow.com/a/27739925).
2. It then runs the same six solutions on a series of around eight thousand numbers drawn from the same distribution and measures the average peak memory usage. 

These were the same six solutions I submitted on LeetCode. LeetCode's reported metrics are also given in `results/`.

## Discussion

The LeetCode memory report overall makes sense except that it ranks my solution that converts a number into a string as 2nd lowest memory. This does not seem correct for a couple reasons.

* The string solution should be using more memory than both solutions that use no external data structures (that build halves of the number into other integers).
* If the string solution is using less memory than one of the build halves solutions, so should using a character array. A character array should have less memory than a C++ string which most likely tracks additional variables.
* My experiment demonstrates that the string solution ranks fourth after both build halves solutions as well as the character array solution. These make more sense.

The LeetCode runtime report overall makes sense except that it ranks my improved build halves solution as 3rd slowest. This does not seem correct for two reasons. 

* My worse build halves solution performs the best, so the improved version that makes fewer passes should be even better. 
* My experiment clearly places the improved build halves solution as the best.

Unlike my memory experiments, my runtime experiments yielded a quite different ranking.

* First, my integer array solution performs much better than the vector solution. This makes sense as vector most likely has to make multiple internal array reallocations. LeetCode reports these two solutions performing similarly.
* One odd thing about my runtime experiment is that the string solution outperforms my worse build halves solution which does not do additional memory allocations. 

## Prerequisites (Linux)

* Install `gcc`, and `make`.
* Ensure `run_experiments.sh` has execute permission.

## Installation

* Download or clone the repository.

## Running

* Open `results` and `./run_experiments.sh`. The results will appear there.

## Authors

[Chami Lamelas](https://github.com/ChamiLamelas/)
