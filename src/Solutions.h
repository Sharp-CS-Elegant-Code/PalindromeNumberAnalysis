/*
My solutions to the problem: given an integer x, determine if it's a palindrome.
See linked LeetCode problem for more information.

Chami Lamelas
Jan 2023
*/

#ifndef _SOLUTIONS_H
#define _SOLUTIONS_H

// Builds 2 halves of x into 2 integers, reverses one of the halves, and
// compares them.
bool BuildHalvesSolution(int x);

// Builds a character array holding the digits of x and checks if its a
// palindrome by moving pointers from the 2 ends.
bool CharArraySolution(int x);

// Improved version of BuildHalvesSolution - splits into halves in just 1 pass
// over x.
bool FastBuildHalvesSolution(int x);

// Same as CharArraySolution but uses an integer array instead. Proof of concept
// - should be worse than CharArraySolution.
bool IntArraySolution(int x);

// Builds a string of the digits and checks if its a palindrome by indexing
// string front and back.
bool StringSolution(int x);

// Same as StringSolution but builds a vector of integers instead of a string.
bool VectorSolution(int x);

#endif