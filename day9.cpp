//
//  day7.cpp
//  advent-of-code
//
/*
--- Day 9: All in a Single Night ---
Every year, Santa manages to deliver all of his presents in a single night.
This year, however, he has some new locations to visit; his elves have provided him the distances between every pair of locations. He can start and end at any two (different) locations he wants, but he must visit each location exactly once. What is the shortest distance he can travel to achieve this?
For example, given the following distances:

London to Dublin = 464
London to Belfast = 518
Dublin to Belfast = 141
The possible routes are therefore:

Dublin -> London -> Belfast = 982
London -> Dublin -> Belfast = 605
London -> Belfast -> Dublin = 659
Dublin -> Belfast -> London = 659
Belfast -> Dublin -> London = 605
Belfast -> London -> Dublin = 982
The shortest of these is London -> Dublin -> Belfast = 605, and so the answer is 605 in this example.

What is the distance of the shortest route?

--- Part Two ---

The next year, just to show off, Santa decides to take the route with the longest distance instead.
He can still start and end at any two (different) locations he wants, and he still must visit each location exactly once.
For example, given the distances above, the longest route would be 982 via (for example) Dublin -> London -> Belfast.
What is the distance of the longest route?
Your puzzle answer was 898.
*/
#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>
#include <fstream>
#include <map>
#include <algorithm>
using CityMap = std::map<std::string, int>;

short GetCityId(CityMap &map, std::string city)
{
    if (map.find(city) == map.end()) {
        short id = map.size();
        map[city] = id;
        return id;
    }
    return map[city];
}

void printDistanceMatrix(short distances[], short numDest) {
    for (short i = 0; i < numDest; ++i) {
        for (short j = 0; j < numDest; ++j) {
            short index = i * numDest + j;
            printf("%9d (%4d)", distances[index], index);
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[])
{
    // Parse
    std::string filePath = "/Users/jon/Documents/advent-of-code/advent-of-code/day9.txt";
    
    std::ifstream file(filePath);
    std::string str;

    std::regex exprReg("(.*) to (.*) = ([0-9]+)");
    assert(std::regex_match("Tristram to AlphaCentauri = 34", exprReg));

    CityMap cities;
    std::vector<short> parsedData;
    while (std::getline(file, str)) {
        std::smatch match;
        std::map<std::string, std::string>dest;
        if (std::regex_search(str, match, exprReg)) {
            const std::string from = match[1];
            const std::string dest = match[2];
            const short id1 = GetCityId(cities, from);
            const short id2 = GetCityId(cities, dest);
            const short distance = std::stoi(match[3]);
            parsedData.push_back(id1);
            parsedData.push_back(id2);
            parsedData.push_back(distance);
            printf("%d to %d = %d\n", id1, id2, distance);
        } else {
            assert(false);
        }
    }
    
    short l = cities.size();
    auto distances = new short[l * l];
    for (short i = 0; i < l; ++i) {
        distances[i * l + i] = 0;
    }
    
    for (auto it = parsedData.begin(); it != parsedData.end(); it++) {
        const short id1 = *it++;
        const short id2 = *it++;
        const short distance = *it;
        short pos1 = id1 * l + id2;
        short pos2 = id2 * l + id1;
        distances[pos1] = distances[pos2] = distance;
    }
    
    printDistanceMatrix(distances, l);
    
    auto path = new short[l];
    for (short i = 0; i < l; ++i)
        path[i] = i;
    
    short shortest = 5000;
    short longest = -1;

    do {
        int distance = 0;
        for (short i = 1; i < l; ++i) {
            int index = path[i] * l + path[i-1];
            distance += distances[index];
        }
        shortest = shortest > distance ? distance : shortest;
        longest = longest < distance ? distance : longest;
    } while (std::next_permutation(path, path+l));

    printf("Part one: the shortest path is %d.\n", shortest);
    printf("Part two: the longest path is %d.\n", longest);

}
