//
//  day15.cpp
//  advent-of-code
//
// --- Day 15: Science for Hungry People ---
// Today, you set out on the task of perfecting your milk-dunking cookie recipe. All you have to do is find the right balance of ingredients.
// Your recipe leaves room for exactly 100 teaspoons of ingredients. You make a list of the remaining ingredients you could use to finish the recipe (your puzzle input) and their properties per teaspoon:
// capacity (how well it helps the cookie absorb milk)
// durability (how well it keeps the cookie intact when full of milk)
// flavor (how tasty it makes the cookie)
// texture (how it improves the feel of the cookie)
// calories (how many calories it adds to the cookie)
// You can only measure ingredients in whole-teaspoon amounts accurately, and you have to be accurate so you can reproduce your results in the future. The total score of a cookie can be found by adding up each of the properties (negative totals become 0) and then multiplying together everything except calories.
// For instance, suppose you have these two ingredients:
// Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
// Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3
// Then, choosing to use 44 teaspoons of butterscotch and 56 teaspoons of cinnamon (because the amounts of each ingredient must add up to 100) would result in a cookie with the following properties:
// A capacity of 44*-1 + 56*2 = 68
// A durability of 44*-2 + 56*3 = 80
// A flavor of 44*6 + 56*-2 = 152
// A texture of 44*3 + 56*-1 = 76
// Multiplying these together (68 * 80 * 152 * 76, ignoring calories for now) results in a total score of 62842880, which happens to be the best score possible given these ingredients. If any properties had produced a negative total, it would have instead become zero, causing the whole score to multiply to zero.
// Given the ingredients in your kitchen and their properties, what is the total score of the highest-scoring cookie you can make?
// Your puzzle answer was 18965440.

// --- Part Two ---
// Your cookie recipe becomes wildly popular! Someone asks if you can make another recipe that has exactly 500 calories per cookie (so they can use it as a meal replacement). Keep the rest of your award-winning process the same (100 teaspoons, same ingredients, same scoring system).
// For example, given the ingredients above, if you had instead selected 40 teaspoons of butterscotch and 60 teaspoons of cinnamon (which still adds to 100), the total calorie count would be 40*8 + 60*3 = 500. The total score would go down, though: only 57600000, the best you can do in such trying circumstances.
// Given the ingredients in your kitchen and their properties, what is the total score of the highest-scoring cookie you can make with a calorie total of 500?
// Your puzzle answer was 15862900.

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>

class Cookie 
{
private:
    int bestCookieScore = 0;

public:    
    std::vector<short> capacityList;
    std::vector<short> duarabilityList;
    std::vector<short> flavorList;
    std::vector<short> textureList;
    std::vector<short> caloriesList;
    
    int getCookieScore()
    {
        return bestCookieScore;
    }
    
    void evaluate(std::vector<int> numbers)
    {
        int capacitySum = 0;
        int durabilitySum = 0;
        int flavorSum = 0;
        int textureSum = 0;
        int caloriesSum = 0;
        for (int i = 0; i < numbers.size(); ++i) {
            capacitySum += numbers[i] * capacityList[i];
            durabilitySum += numbers[i] * duarabilityList[i];
            flavorSum += numbers[i] * flavorList[i];
            textureSum += numbers[i] * textureList[i];
            caloriesSum += numbers[i] * caloriesList[i];
        }
        
        int product = 1;
        if (capacitySum < 0 || durabilitySum < 0 || flavorSum < 0 || textureSum < 0) {
            product = 0;
        } else {
            product = capacitySum * durabilitySum * flavorSum * textureSum;
        }
        
        if(product > bestCookieScore && caloriesSum == 500) {
            bestCookieScore = product;    
        }
    }

    void beatTheDough(std::vector<int> numbers, int max, int index) 
    {
        for (int ppp = 0; ppp <= max; ++ppp) {
            numbers[index] = ppp;    
            int sum = 0;
            for (int i = 0; i < numbers.size(); ++i) {
                sum += numbers[i];
            }
            if (sum == 100) {
                evaluate(numbers);
            }
            if (sum < max && index < numbers.size() - 1) {
                beatTheDough(numbers, max, index + 1);
            }
        }  
    }

    void bake() 
    {
        short numberOfIngredients = capacityList.size();
        short numberOfSpoons = 100;
        std::vector<int> ingredients(numberOfIngredients);
        beatTheDough(ingredients, numberOfSpoons, 0);
    }
};

int main()
{
    std::ifstream file("day15.txt");
    std::string str;
    
    std::regex reg(".*: capacity (-?\\d+), durability (-?\\d+), flavor (-?\\d+), texture (-?\\d+), calories (-?\\d+)");
    assert(std::regex_match("Frosting: capacity 4, durability -2, flavor 0, texture 0, calories 5", reg));
    
    Cookie cookie;
    while (std::getline(file, str))
    {
        std::smatch m;
        if (std::regex_search(str, m, reg)) {
            cookie.capacityList.push_back(std::stoi(m[1]));
            cookie.duarabilityList.push_back(std::stoi(m[2]));
            cookie.flavorList.push_back(std::stoi(m[3]));
            cookie.textureList.push_back(std::stoi(m[4]));
            cookie.caloriesList.push_back(std::stoi(m[5]));
        } else {
            assert(false);
        }
    }

    cookie.bake();

    printf("The perfect cookie score: %d\n", cookie.getCookieScore());
}
