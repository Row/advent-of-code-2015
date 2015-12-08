//
//  day7.cpp
//  advent-of-code
//
/*
--- Day 7: Some Assembly Required ---

This year, Santa brought little Bobby Tables a set of wires and bitwise logic gates! Unfortunately, little Bobby is a little under the recommended age range, and he needs help assembling the circuit.

Each wire has an identifier (some lowercase letters) and can carry a 16-bit signal (a number from 0 to 65535). A signal is provided to each wire by a gate, another wire, or some specific value. Each wire can only get a signal from one source, but can provide its signal to multiple destinations. A gate provides no signal until all of its inputs have a signal.

The included instructions booklet describes how to connect the parts together: x AND y -> z means to connect wires x and y to an AND gate, and then connect its output to wire z.

For example:

123 -> x means that the signal 123 is provided to wire x.
x AND y -> z means that the bitwise AND of wire x and wire y is provided to wire z.
p LSHIFT 2 -> q means that the value from wire p is left-shifted by 2 and then provided to wire q.
NOT e -> f means that the bitwise complement of the value from wire e is provided to wire f.
Other possible gates include OR (bitwise OR) and RSHIFT (right-shift). If, for some reason, you'd like to emulate the circuit instead, almost all programming languages (for example, C, JavaScript, or Python) provide operators for these gates.

For example, here is a simple circuit:

123 -> x
456 -> y
x AND y -> d
x OR y -> e
x LSHIFT 2 -> f
y RSHIFT 2 -> g
NOT x -> h
NOT y -> i
After it is run, these are the signals on the wires:

d: 72
e: 507
f: 492
g: 114
h: 65412
i: 65079
x: 123
y: 456
In little Bobby's kit's instructions booklet (provided as your puzzle input), what signal is ultimately provided to wire a?

Your puzzle answer was 3176.

--- Part Two ---

Now, take the signal you got on wire a, override wire b to that signal, and reset the other wires (including wire a). What new signal is ultimately provided to wire a?

Your puzzle answer was 14710.
*/
#include <iostream>
#include <string>
#include <cassert>
#include <regex>
#include <iterator>
#include <fstream>
#include <map>

std::regex exprReg("(.*) -> (.*)");
std::regex exprNum("[0-9]+");
std::regex exprVar("[a-z]+");
std::regex exprBinary("(.*) (.*) (.*)");
std::regex exprNegation("NOT (.*)");

std::map<std::string, std::string> expressions;


unsigned short int resolveExpression(std::string expression) {
    std::smatch m;
    if (std::regex_match(expression, exprNum)) {
        unsigned short int r = std::stoi(expression);
        return r;
    } else if (std::regex_match(expression, exprVar)) {
        //assert(expressions.);
        unsigned int r = resolveExpression(expressions[expression]);
        expressions[expression] = std::to_string(r);
        return resolveExpression(expressions[expression]);
    } else if (std::regex_search(expression, m, exprNegation)) {
        return ~ resolveExpression(m[1]);
    } else if (std::regex_search(expression, m, exprBinary)) {
        std::string op = m[2];
        unsigned short int a = resolveExpression(m[1]);
        unsigned short int b = resolveExpression(m[3]);
        if (op.compare("OR") == 0) {
            return a | b;
        } else if (op.compare("AND") == 0) {
            return a & b;
        } else if (op.compare("RSHIFT") == 0) {
            return a >> b;
        } else if (op.compare("LSHIFT") == 0) {
            return a << b;
        } else  {
            assert(false);
        }
    }
    assert(false);
    return 0;
}


void resetWires(std::string filePath) {
    std::ifstream file(filePath);
    std::string str;
    while (std::getline(file, str)) {
        std::smatch match;
        if (std::regex_search(str, match, exprReg)) {
            const std::string vari = match[2];
            std::string expr = match[1];
            expressions[vari] = expr;
        }
    }
}


int main(int argc, const char * argv[]) {

    // Parse
    //std::string filePath = "/Users/jon/Documents/advent-of-code/advent-of-code/day7test.txt";
    std::string filePath = "/Users/jon/Documents/advent-of-code/advent-of-code/day7.txt";
    
    assert(std::regex_match("jp OR ka -> kb", exprReg));
    assert(std::regex_match("199", exprNum));
    assert(!std::regex_match("ab", exprNum));
    assert(!std::regex_match("199", exprVar));
    assert(std::regex_match("ab", exprVar));
    assert(std::regex_match("y RSHIFT 2", exprBinary));
    assert(std::regex_match("NOT x", exprNegation));

    resetWires(filePath);
    
    if (filePath.compare("/Users/jon/Documents/advent-of-code/advent-of-code/day7test.txt") == 0) {
        assert(resolveExpression("d") == 72);
        assert(resolveExpression("e") == 507);
        assert(resolveExpression("f") == 492);
        assert(resolveExpression("g") == 114);
        assert(resolveExpression("h") == 65412);
        assert(resolveExpression("i") == 65079);
        assert(resolveExpression("x") == 123);
        assert(resolveExpression("y") == 456);
    } else {
        // Part One
        printf("Part one: %d.\n", resolveExpression("a"));
        
        // Part Two
        resetWires(filePath);
        expressions["b"] = "3176";
        printf("Part two: %d.\n", resolveExpression("a"));

    }
    
}