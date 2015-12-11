//
//  day10.cpp
//  advent-of-code
//
/*
--- Day 11: Corporate Policy ---

Santa's previous password expired, and he needs help choosing a new one.

To help him remember his new password after the old one expires, Santa has devised a method of coming up with a password based on the previous one. Corporate policy dictates that passwords must be exactly eight lowercase letters (for security reasons), so he finds his new password by incrementing his old password string repeatedly until it is valid.

Incrementing is just like counting with numbers: xx, xy, xz, ya, yb, and so on. Increase the rightmost letter one step; if it was z, it wraps around to a, and repeat with the next letter to the left until one doesn't wrap around.

Unfortunately for Santa, a new Security-Elf recently started, and he has imposed some additional password requirements:

Passwords must include one increasing straight of at least three letters, like abc, bcd, cde, and so on, up to xyz. They cannot skip letters; abd doesn't count.
Passwords may not contain the letters i, o, or l, as these letters can be mistaken for other characters and are therefore confusing.
Passwords must contain at least two different, non-overlapping pairs of letters, like aa, bb, or zz.
For example:

hijklmmn meets the first requirement (because it contains the straight hij) but fails the second requirement requirement (because it contains i and l).
abbceffg meets the third requirement (because it repeats bb and ff) but fails the first requirement.
abbcegjk fails the third requirement, because it only has one double letter (bb).
The next password after abcdefgh is abcdffaa.
The next password after ghijklmn is ghjaabcc, because you eventually skip all the passwords that start with ghi..., since i is not allowed.
Given Santa's current password (your puzzle input), what should his next password be?

Your puzzle input is cqjxjnds.
*/
#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>
#include <fstream>
#include <map>
#include <algorithm>


const char kFirst = 'a';
const char kLast = 'z';
const char kDomain = kLast + 1;

void increment(std::string &str) {
    short i = (short)str.size() - 1;
    bool remainder = false;
    do {
        remainder = false;
        str[i] = (str[i] + 1) % kDomain;
        if (!str[i]) {
            str[i] = kFirst;
            remainder = true;
            i--;
        }
        assert(i > -1);
    } while(remainder);
}

bool isValid(const std::string &str) {
    int doublePos = -1;
    bool hasTwoDouble = false;
    bool lastTwoStraight = false;
    bool hasThreeStraight = false;
    if (str[0] == 'i' || str[0] == 'o' || str[0] == 'l')
        return false;

    for(int i = 1; i < (int)str.size(); ++i) {
        if (str[i] == 'i' || str[i] == 'o' || str[i] == 'l')
            return false;
        
        if (str[i - 1] == str[i]) {
            if (doublePos == -1) {
                doublePos = i;
            } else if(doublePos != i - 1) {
                hasTwoDouble = true;
            }
        }
        
        if (str[i - 1] == str[i] - 1) {
            if (lastTwoStraight)
                hasThreeStraight = true;
            lastTwoStraight = true;
        } else {
            lastTwoStraight = false;
        }
        
        if (hasTwoDouble && hasThreeStraight) {
            return true;
        }
    }
    return hasTwoDouble && hasThreeStraight;
}


void findNext(std::string &str) 
{
    do {
        increment(str);
    } while(!isValid(str));
}

int main(int argc, const char * argv[])
{   
    // First some tests
    assert('z' == (('z' % kDomain)));
    assert('b' == (('a' + 1)));
    assert('a' == ('z' + 1 + kFirst) % kDomain);
    assert('b' == ('a' + 1 - kFirst) % kDomain + kFirst);

    std::string t("abc");
    increment(t);
    assert("abd" == t);
    t = "azz";
    increment(t);
    assert("baa" == t);
    assert(isValid("abcdffaa"));
    assert(!isValid("abdffaa"));
    assert(!isValid("abdffaa"));
    t = "abcdefgh";
    findNext(t);
    assert(t == "abcdffaa");
    t = "ghijklmn";
    findNext(t);
    assert(t == "ghjaabcc");
    
    std::string input = "cqjxjnds";
    findNext(input);
    printf("Part one: Santas new password is: %s\n", input.c_str());
    findNext(input);
    printf("Part two: Santas next new password is: %s\n", input.c_str());
}
