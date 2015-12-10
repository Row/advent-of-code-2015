//
//  day10.cpp
//  advent-of-code
//
/*
--- Day 10: Elves Look, Elves Say ---

Today, the Elves are playing a game called look-and-say. They take turns making sequences by reading aloud the previous sequence and using that reading as the next sequence. For example, 211 is read as "one two, two ones", which becomes 1221 (1 2, 2 1s).

Look-and-say sequences are generated iteratively, using the previous value as input for the next step. For each step, take the previous value, and replace each run of digits (like 111) with the number of digits (3) followed by the digit itself (1).

For example:

1 becomes 11 (1 copy of digit 1).
11 becomes 21 (2 copies of digit 1).
21 becomes 1211 (one 2 followed by one 1).
1211 becomes 111221 (one 1, one 2, and two 1s).
111221 becomes 312211 (three 1s, two 2s, and one 1).
Starting with the digits in your puzzle input, apply this process 40 times. What is the length of the result?

Your puzzle input is 3113322113.
 
 Your puzzle answer was 329356.

--- Part Two ---

Neat, right? You might also enjoy hearing John Conway talking about this sequence (that's Conway of Conway's Game of Life fame).

Now, starting again with the digits in your puzzle input, apply this process 50 times. What is the length of the new result?

Your puzzle answer was 4666278.
*/
#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>
#include <fstream>
#include <map>
#include <algorithm>

std::string lookAndSay(const std::string &str) 
{
    std::string out = "";
    auto prevCount = 1;
    int i = 1;
    for (; i < str.size(); ++i) {
        if (str[i - 1] == str[i]) {
            ++prevCount;
        } else {
            out += std::to_string(prevCount);
            out += str[i - 1];
            prevCount = 1;
        }
    }
    out += std::to_string(prevCount);
    out += str[i - 1];
    return out;
}

int main(int argc, const char * argv[])
{   
    assert(lookAndSay("1").compare("11") == 0);
    assert(lookAndSay("11").compare("21") == 0);
    assert(lookAndSay("1211").compare("111221") == 0);
    assert(lookAndSay("21").compare("1211") == 0);
    assert(lookAndSay("111221").compare("312211") == 0);

    std::string input = "3113322113";
    for (int i = 0; i < 50; ++i) {
        input = lookAndSay(input);
    }
    
    printf("Part one: length is %lu\n", input.length());
}
