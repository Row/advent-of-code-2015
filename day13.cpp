//
//  day13.cpp
//  advent-of-code
//
/*
--- Day 13: Knights of the Dinner Table ---

In years past, the holiday feast with your family hasn't gone so well. Not everyone gets along! This year, you resolve, will be different. You're going to find the optimal seating arrangement and avoid all those awkward conversations.

You start by writing up a list of everyone invited and the amount their happiness would increase or decrease if they were to find themselves sitting next to each other person. You have a circular table that will be just big enough to fit everyone comfortably, and so each person will have exactly two neighbors.

For example, suppose you have only four attendees planned, and you calculate their potential happiness as follows:

Alice would gain 54 happiness units by sitting next to Bob.
Alice would lose 79 happiness units by sitting next to Carol.
Alice would lose 2 happiness units by sitting next to David.
Bob would gain 83 happiness units by sitting next to Alice.
Bob would lose 7 happiness units by sitting next to Carol.
Bob would lose 63 happiness units by sitting next to David.
Carol would lose 62 happiness units by sitting next to Alice.
Carol would gain 60 happiness units by sitting next to Bob.
Carol would gain 55 happiness units by sitting next to David.
David would gain 46 happiness units by sitting next to Alice.
David would lose 7 happiness units by sitting next to Bob.
David would gain 41 happiness units by sitting next to Carol.
Then, if you seat Alice next to David, Alice would lose 2 happiness units (because David talks so much), but David would gain 46 happiness units (because Alice is such a good listener), for a total change of 44.

If you continue around the table, you could then seat Bob next to Alice (Bob gains 83, Alice gains 54). Finally, seat Carol, who sits next to Bob (Carol gains 60, Bob loses 7) and David (Carol gains 55, David gains 41). The arrangement looks like this:

     +41 +46
+55   David    -2
Carol       Alice
+60    Bob    +54
     -7  +83
After trying every other seating arrangement in this hypothetical scenario, you find that this one is the most optimal, with a total change in happiness of 330.

What is the total change in happiness for the optimal seating arrangement of the actual guest list?
*/
#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>
#include <fstream>
#include <map>
#include <algorithm>
using Guests = std::map<std::string, int>;

short GetGuestId(Guests &guests, std::string city)
{
    if (guests.find(city) == guests.end()) {
        short id = guests.size();
        guests[city] = id;
        return id;
    }
    return guests[city];
}

void printMatrix(short relations[], short numberOfGuests) {
    for (short i = 0; i < numberOfGuests; ++i) {
        for (short j = 0; j < numberOfGuests; ++j) {
            short index = i * numberOfGuests + j;
            printf("%9d (%4d)", relations[index], index);
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[])
{
    // Parse
    std::string filePath = "day13.txt";
    
    std::ifstream file(filePath);
    std::string str;

    std::regex exprReg("(.*) would (.*) ([0-9]+) happiness units by sitting next to (.+)\\.");
    assert(std::regex_match("Alice would lose 2 happiness units by sitting next to Bob.", exprReg));

    Guests guestList;
    std::vector<short> parsedData;
    while (std::getline(file, str)) {
        std::smatch match;
        std::map<std::string, std::string>dest;
        if (std::regex_search(str, match, exprReg)) {
            const std::string left = match[1];
            const std::string right = match[4];
            const short id1 = GetGuestId(guestList, left);
            const short id2 = GetGuestId(guestList, right);
            const std::string positive = match[2];
            const short happiness = (positive.compare("lose") == 0 ? -1 : 1 ) * std::stoi(match[3]);
            parsedData.push_back(id1);
            parsedData.push_back(id2);
            parsedData.push_back(happiness);
        } else {
            assert(false);
        }
    }
    
    // +1 for part two
    short l = guestList.size() + 1;
    auto relations = new short[l * l];
    
    for (short i = 0; i < l * l; ++i) {
        relations[i] = 0;
    }
    
    for (auto it = parsedData.begin(); it != parsedData.end(); it++) {
        const short id1 = *it++;
        const short id2 = *it++;
        const short happiness = *it;
        const short index  = id1 * l + id2;
        relations[index] = happiness;
    }
    
    printMatrix(relations, l);
    
    auto tableSetting = new short[l];
    for (short i = 0; i < l; ++i)
        tableSetting[i] = i;
    
    short happiest = -1;

    do {
        short happiness = 0;
        for (short i = 0; i < l; ++i) {
            short tableIndex1 = (((i - 1) % l) + l) % l;
            short tableIndex2 = (i + 1) % l;
            short indexLeft = tableSetting[i] * l + tableSetting[tableIndex1];
            short indexRight = tableSetting[i] * l + tableSetting[tableIndex2];
            happiness += relations[indexLeft] + relations[indexRight];
        }
        happiest = happiest < happiness ? happiness : happiest;
    } while (std::next_permutation(tableSetting, tableSetting+l));

    printf("Max happiness is %d.\n", happiest);
}
