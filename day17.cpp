//
//  day9.cpp
//  advent-of-code
//
// --- Day 17: No Such Thing as Too Much ---
// The elves bought too much eggnog again - 150 liters this time. To fit it all into your refrigerator, you'll need to move it into smaller containers. You take an inventory of the capacities of the available containers.
// For example, suppose you have containers of size 20, 15, 10, 5, and 5 liters. If you need to store 25 liters, there are four ways to do it:
// 15 and 10
// 20 and 5 (the first 5)
// 20 and 5 (the second 5)
// 15, 5, and 5
// Filling all containers entirely, how many different combinations of containers can exactly fit all 150 liters of eggnog?
// Your puzzle answer was 4372.
// --- Part Two ---
// While playing with all the containers in the kitchen, another load of eggnog arrives! The shipping and receiving department is requesting as many containers as you can spare.
// Find the minimum number of containers that can exactly fit all 150 liters of eggnog. How many different ways can you fill that number of containers and still hold exactly 150 litres?
// In the example above, the minimum number of containers was two. There were three ways to use that many containers, and so the answer there would be 3.
// Your puzzle answer was 4.


#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>
#include <fstream>
#include <map>
#include <algorithm>

class EggnodKitchen 
{
private:
    std::vector<short> containerStats;

public:
    short litersOfEggnod = 150;
    std::vector<short> containers;
    short combinations;
    void findCombos(int startIndex, int sum, short numberOfContainers)
    {
        if (sum == litersOfEggnod) {
            containerStats.push_back(numberOfContainers);
            return;
        }
        if (sum > litersOfEggnod) {
            return;
        }
        for (int i = startIndex; i < containers.size(); ++i) {
            findCombos(i + 1, sum + containers[i], numberOfContainers + 1);
        }
    }

    void StartMix()
    {
        containerStats.clear();
        findCombos(0, 0, 0);
    }

    short getTotalNumberOfCombos()
    {
        return containerStats.size();
    }
    
    short getNumberOfMinimumCombos()
    {
        std::sort(containerStats.begin(), containerStats.end());
        short num;
        for (num = 1; num < containerStats.size(); ++num) {
            if (containerStats[num - 1] != containerStats[num]) {
                break;
            }
        }
        return num;
    }
};

int main(int argc, const char * argv[])
{
    // Parse
    std::string filePath = "day17.txt";
    
    std::ifstream file(filePath);
    std::string str;
    EggnodKitchen santasKitchen;
    while (std::getline(file, str)) {
        santasKitchen.containers.push_back(std::stoi(str));
    }
    santasKitchen.StartMix();
    printf("Part One: Total number of matched combinations: %d.\n", santasKitchen.getTotalNumberOfCombos());
    printf("Part Two: Number of combinations to fill the minimum number of containers: %d.\n", santasKitchen.getNumberOfMinimumCombos());
}
