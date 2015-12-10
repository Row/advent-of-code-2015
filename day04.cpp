//
//  day4.cpp
//  advent-of-code
//
// --- Day 4: The Ideal Stocking Stuffer ---
// Santa needs help mining some AdventCoins (very similar to bitcoins) to use as gifts for all the economically forward-thinking little girls and boys.
// To do this, he needs to find MD5 hashes which, in hexadecimal, start with at least five zeroes. The input to the MD5 hash is some secret key (your puzzle input, given below) followed by a number in decimal. To mine AdventCoins, you must find Santa the lowest positive number (no leading zeroes: 1, 2, 3, ...) that produces such a hash.
// For example:
// If your secret key is abcdef, the answer is 609043, because the MD5 hash of abcdef609043 starts with five zeroes (000001dbbfa...), and it is the lowest such number to do so.
// If your secret key is pqrstuv, the lowest number it combines with to make an MD5 hash starting with five zeroes is 1048970; that is, the MD5 hash of pqrstuv1048970 looks like 000006136ef....
// Your puzzle answer was 346386.

// --- Part Two ---

// Now find one that starts with six zeroes.
#include <iostream>
#include <string>
#include <cassert>
#include "md5.h"

bool isPrefix(std::string const& s1, std::string const&s2)
{
    const char*p = s1.c_str();
    const char*q = s2.c_str();
    while (*p&&*q)
        if (*p++!=*q++)
            return false;
    return true;
}

int findMD5Prefix(const std::string &prefix, const std::string &input)
{
    int i = 0;
    std::string md5res;
    do {
        md5res = md5(input + std::to_string(i++));
    } while(!isPrefix(md5res, prefix));
    return i - 1;
}


int main(int argc, const char * argv[]) {
    assert(findMD5Prefix("00000", "abcdef") == 609043);
    assert(findMD5Prefix("00000", "pqrstuv") == 1048970);
    
    printf("Found match %s for check %d\n\n", "iwrupvqb", findMD5Prefix("00000", "iwrupvqb"));
    printf("Found match %s for check %d\n\n", "iwrupvqb", findMD5Prefix("000000", "iwrupvqb"));
}