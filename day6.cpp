//
//  day6.cpp
//  advent-of-code
// --- Day 6: Probably a Fire Hazard ---

// Because your neighbors keep defeating you in the holiday house decorating contest year after year, you've decided to deploy one million lights in a 1000x1000 grid.
// Furthermore, because you've been especially nice this year, Santa has mailed you instructions on how to display the ideal lighting configuration.
// Lights in your grid are numbered from 0 to 999 in each direction; the lights at each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions include whether to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs. Each coordinate pair represents opposite corners of a rectangle, inclusive; a coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. The lights all start turned off.
// To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions Santa sent you in order.
// For example:
// turn on 0,0 through 999,999 would turn on (or leave on) every light.
// toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
// turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.
// After following the instructions, how many lights are lit?
// --- Part Two ---
// You just finish implementing your winning light pattern when you realize you mistranslated Santa's message from Ancient Nordic Elvish.
// The light grid you bought actually has individual brightness controls; each light can have a brightness of zero or more. The lights all start at zero.
// The phrase turn on actually means that you should increase the brightness of those lights by 1.
// The phrase turn off actually means that you should decrease the brightness of those lights by 1, to a minimum of zero.
// The phrase toggle actually means that you should increase the brightness of those lights by 2.
// What is the total brightness of all lights combined after following Santa's instructions?
// For example:
// turn on 0,0 through 0,0 would increase the total brightness by 1.
// toggle 0,0 through 999,999 would increase the total brightness by 2000000.

#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>
#include <fstream>

int main(int argc, const char * argv[]) {
    //
    auto lightsRow = 1000;
    auto numberOfLightsOn = 0;
    auto totalBrightness = 0;
    auto arrLength = lightsRow * lightsRow;
    auto lights = new bool[arrLength];
    auto lightBrightness = new int[arrLength];
    // Parse
    std::ifstream file("day6.txt");
    std::string str;
    
    std::regex instructionRegex("(.*) ([0-9]+),([0-9]+) through ([0-9]+),([0-9]+).*");
    assert(std::regex_match("turn on 887,9 through 959,629", instructionRegex));

    while (std::getline(file, str)) {
        std::smatch match;

        if (std::regex_search(str, match, instructionRegex))
        {
            std::string action = match[1];
            int x1 = std::stoi(match[2]);
            int y1 = std::stoi(match[3]);

            int x2 = std::stoi(match[4]);
            int y2 = std::stoi(match[5]);
            assert(x1 <= x2);
            assert(y1 <= y2);
            for (int x = x1; x <= x2; ++x) {
                for (int y = y1; y <= y2; ++y) {
                    auto index = y * lightsRow + x;
                    if (action.compare("turn on") == 0) {
                        lights[index] = true;
                        lightBrightness[index] += 1;
                    } else if (action.compare("turn off") == 0) {
                        lights[index] = false;
                        lightBrightness[index] -= 1;
                        if (lightBrightness[index] < 0)
                            lightBrightness[index] = 0;
                    } else if (action.compare("toggle") == 0) {
                        lights[index] = !lights[index] ;
                        lightBrightness[index] += 2;
                    }
                }
            }
        }
    }

    // Sum up the result
    for (int x = 0; x <= 999; ++x) {
        for (int y = 0; y <= 999; ++y) {
            auto index = y * lightsRow + x;
            numberOfLightsOn += lights[index] ? 1 : 0;
            totalBrightness += lightBrightness[index];
        }
    }

    printf("Part one: %d lights are on.\n", numberOfLightsOn);
    printf("Part two: Total brighness %d.\n", totalBrightness);

}