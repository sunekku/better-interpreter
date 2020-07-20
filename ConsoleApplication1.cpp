// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "interpreter.h"

int main() {
    std::string input;
    std::getline(std::cin, input);
    lexer::Lexer lex = lexer::Lexer(input);
    lexer::Lexer* lexer = &lex;
    parser::Parser par = parser::Parser(lexer);
    parser::Parser* parser = &par;
    interpreter::Interpreter inter = interpreter::Interpreter(parser);
    std::cout << inter.interpret();
    return 0;
}