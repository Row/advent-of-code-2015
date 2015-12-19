//
//  day18.cpp
//  advent-of-code
// 
// --- Day 18: Like a GIF For Your Yard ---
// After the million lights incident, the fire code has gotten stricter: now, at most ten thousand lights are allowed. You arrange them in a 100x100 grid.
// Never one to let you down, Santa again mails you instructions on the ideal lighting configuration. With so few lights, he says, you'll have to resort to animation.
// Start by setting your lights to the included initial configuration (your puzzle input). A # means "on", and a . means "off".
// Then, animate your grid in steps, where each step decides the next configuration based on the current one. Each light's next state (either on or off) depends on its current state and the current states of the eight lights adjacent to it (including diagonals). Lights on the edge of the grid might have fewer than eight neighbors; the missing ones always count as "off".
// For example, in a simplified 6x6 grid, the light marked A has the neighbors numbered 1 through 8, and the light marked B, which is on an edge, only has the neighbors marked 1 through 5:
//
// 1B5...
// 234...
// ......
// ..123.
// ..8A4.
// ..765.
//
// The state a light should have next is based on its current state (on or off) plus the number of neighbors that are on:
// A light which is on stays on when 2 or 3 neighbors are on, and turns off otherwise.
// A light which is off turns on if exactly 3 neighbors are on, and stays off otherwise.
// All of the lights update simultaneously; they all consider the same current state before moving to the next.
// Here's a few steps from an example configuration of another 6x6 grid:
//
// Initial state:
// .#.#.#
// ...##.
// #....#
// ..#...
// #.#..#
// ####..
//
// After 1 step:
// ..##..
// ..##.#
// ...##.
// ......
// #.....
// #.##..
//
// After 2 steps:
// ..###.
// ......
// ..###.
// ......
// .#....
// .#....
//
// After 3 steps:
// ...#..
// ......
// ...#..
// ..##..
// ......
// ......
//
// After 4 steps:
// ......
// ......
// ..##..
// ..##..
// ......
// ......
//
// After 4 steps, this example has four lights on.
// In your grid of 100x100 lights, given your initial configuration, how many lights are on after 100 steps?
//
// Your puzzle answer was 814.
//
// --- Part Two ---
//
// You flip the instructions over; Santa goes on to point out that this is all just an implementation of Conway's Game of Life. At least, it was, until you notice that something's wrong with the grid of lights you bought: four lights, one in each corner, are stuck on and can't be turned off. The example above will actually run like this:
//
// Initial state:
// ##.#.#
// ...##.
// #....#
// ..#...
// #.#..#
// ####.#
//
// After 1 step:
// #.##.#
// ####.#
// ...##.
// ......
// #...#.
// #.####
//
// After 2 steps:
// #..#.#
// #....#
// .#.##.
// ...##.
// .#..##
// ##.###
//
// After 3 steps:
// #...##
// ####.#
// ..##.#
// ......
// ##....
// ####.#
//
// After 4 steps:
// #.####
// #....#
// ...#..
// .##...
// #.....
// #.#..#
//
// After 5 steps:
// ##.###
// .##..#
// .##...
// .##...
// #.#...
// ##...#

// After 5 steps, this example now has 17 lights on.
// In your grid of 100x100 lights, given your initial configuration, but with the four corners always in the on state, how many lights are on after 100 steps?
// Your puzzle answer was 924.
#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>
#include <fstream>

class Lights
{
public: 
    int lightsRow = 100;
    int arrLength = lightsRow * lightsRow;
    bool *lights = new bool[arrLength];
    bool *lightsPrevious = new bool[arrLength];
    static const char On = '#';
    static const char Off = '.';

    void swapMatrixStates()
    {
        auto tmp = lightsPrevious;
        lightsPrevious = lights;
        lights = tmp;
    }


    int getMatrixIndex(int x, int y)
    {
        return y * lightsRow + x;
    }

    int getMatrixValue(int x, int y)
    {
        return lightsPrevious[getMatrixIndex(x, y)];
    }

    bool isLightOnCordinate(int x, int y) 
    {
        if (x < 0 || x >= lightsRow || y < 0 || y >= lightsRow)
            return false;

        // Part two broken corner lights (always on).
        if ((x == 0 && y == 0) ||
            (x == 0 && y == lightsRow - 1) ||
            (x == lightsRow - 1 && y == 0) ||
            (x == lightsRow - 1 && y == lightsRow - 1)) {
            return true;
        }
        return getMatrixValue(x, y);
    }

    int countNeighboursLights(const int x, const int y)
    {
        int sum = 0;
        for (int j = y - 1; j < y + 2; ++j) {
            for (int i = x - 1; i < x + 2; ++i) {
                sum += isLightOnCordinate(i, j);
            }
        }
        return sum -= isLightOnCordinate(x, y);
    }

    // A light which is on stays on when 2 or 3 neighbors are on, and turns off otherwise.
    // A light which is off turns on if exactly 3 neighbors are on, and stays off otherwise.
    bool shouldLightBeOn(int x, int y) 
    {
        bool thisLightIsOn = isLightOnCordinate(x, y);
        int numberOfNeighbours = countNeighboursLights(x, y);
        assert(numberOfNeighbours < 9);
        return (thisLightIsOn && (numberOfNeighbours == 2 || numberOfNeighbours == 3)) ||
               (!thisLightIsOn && numberOfNeighbours == 3);
    }

    void processLight(int x, int y)
    {
        auto lightIndex = getMatrixIndex(x, y);
        lights[lightIndex] = shouldLightBeOn(x, y);
    }

    int sumNumberOfLights()
    {
        // Sum up the result
        int numberOfLightsOn = 0;
        for (int x = 0; x < lightsRow; ++x) {
            for (int y = 0; y < lightsRow; ++y) {
                numberOfLightsOn += (short)isLightOnCordinate(x, y);
            }
        }
        return numberOfLightsOn;
    }

    void print() 
    {
        for (int y = 0; y < lightsRow; ++y) {
            for (int x = 0; x < lightsRow; ++x) {
                    printf("%c", isLightOnCordinate(x, y) ? On : Off);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    void animate(int states)
    {
        for (int i = 0; i <= states; ++i) {
            swapMatrixStates();
            for (int y = 0; y < lightsRow; ++y) {
                for (int x = 0; x < lightsRow; ++x ) {
                    processLight(x, y);
                }
            }
        }
    }
    
};

int main(int argc, const char * argv[])
{
    // Parse
    std::ifstream file("day18.txt");
    char ch;
    short i = 0;
    Lights lights;
    while (file >> std::noskipws >> ch) {
        if (Lights::On == ch || Lights::Off == ch) {
            lights.lightsPrevious[i] = lights.lights[i] = Lights::On == ch;
            i++;
        }
    }    
    lights.animate(100);
    lights.print();
    printf("Part one: %d lights are on.\n", lights.sumNumberOfLights());
}