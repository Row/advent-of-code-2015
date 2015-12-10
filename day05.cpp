//
//  day5.cpp
//  advent-of-code
//
// --- Day 5: Doesn't He Have Intern-Elves For This? ---

// Santa needs help figuring out which strings in his text file are naughty or nice.

// A nice string is one with all of the following properties:

// It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
// It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
// It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.
// For example:

// ugknbfddgicrmopn is nice because it has at least three vowels (u...i...o...), a double letter (...dd...), and none of the disallowed substrings.
// aaa is nice because it has at least three vowels and a double letter, even though the letters used by different rules overlap.
// jchzalrnumimnmhp is naughty because it has no double letter.
// haegwjzuvuyypxyu is naughty because it contains the string xy.
// dvszwmarrgswjxmb is naughty because it contains only one vowel.
// How many strings are nice?

// Your puzzle answer was 236.

// --- Part Two ---

// Realizing the error of his ways, Santa has switched to a better model of determining whether a string is naughty or nice. None of the old rules apply, as they are all clearly ridiculous.

// Now, a nice string is one with all of the following properties:

// It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
// It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
// For example:

// qjhvhtzxzqqjkmpb is nice because is has a pair that appears twice (qj) and a letter that repeats with exactly one letter between them (zxz).
// xxyxx is nice because it has a pair that appears twice and a letter that repeats with one between, even though the letters used by each rule overlap.
// uurcxstgmygtbstg is naughty because it has a pair (tg) but no repeat with a single letter between them.
// ieodomkazucvgmuy is naughty because it has a repeating letter with one between (odo), but no pair that appears twice.
// How many strings are nice under these new rules?

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>

void day5PartOne() {
    std::ifstream file("day5.txt");
    std::string str;
    
    std::regex threeVowels(".*[aeiou].*[aeiou].*[aeiou].*");
    assert(std::regex_match("dadudid", threeVowels));
    std::regex doubleLetter(".*(.)\\1.*");
    assert(std::regex_match("abbd", doubleLetter));
    std::regex doNotMatch(".*(ab|cd|pq|xy).*");
    assert(std::regex_match("abcdpqxy", doNotMatch));

    int numberOfGoodStrings = 0;
    while (std::getline(file, str))
    {
        if (std::regex_match(str, threeVowels) &&
            std::regex_match(str, doubleLetter) &&
            !std::regex_match(str, doNotMatch)) {
            ++numberOfGoodStrings;
        }
    }
    printf("1. Found %d good strings.\n", numberOfGoodStrings);
}

void day5PartTwo() {
    std::ifstream file("day5.txt");
    std::string str;
    
    std::regex twoLetterAppearAgain(".*(..).*\\1.*");
    assert(std::regex_match("dadudad", twoLetterAppearAgain));
    std::regex doubleLetterOneBetween(".*(.).\\1.*");
    assert(std::regex_match("ababd", doubleLetterOneBetween));

    int numberOfGoodStrings = 0;
    while (std::getline(file, str))
    {
        if (std::regex_match(str, twoLetterAppearAgain) &&
            std::regex_match(str, doubleLetterOneBetween)) {
            ++numberOfGoodStrings;
        }
    }
    printf("2. Found %d good strings.\n", numberOfGoodStrings);
}

int main()
{
    day5PartOne();
    day5PartTwo();
}