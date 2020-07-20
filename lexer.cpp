// lexer.cpp
// lexer written in cpp
// extremely basic algorithm to spit tokens out
// white spaces are ignored 
// next_token returns pointer to Token object instead of Token object
// this is to confuse you

#include <iostream>
#include <string>
#include "lexer.h"
#define INTEGER "INTEGER"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define MUL "MUL"
#define DIV "DIV"
#define LPAR "LPAR"
#define RPAR "RPAR"
#define OP "OP"
#define INT "INT"

std::ostream& lexer::operator<< (std::ostream& out, const lexer::Token& token)
{
    out << "Token type: " << token.type << "\n" << "Token value: " << token.value << "\n";
    return out;
}

lexer::Token::Token(std::string t, char v) {
    type = t;
    value = v;
}

lexer::Lexer::Lexer(std::string scr) {
    position = 0;
    script = scr;
    curr_character = script[position];
}

void lexer::Lexer::error() {
    std::cout << "Error parsing input" << "\n";
    throw;
}

void lexer::Lexer::skip_whitespace() {
    while (curr_character != NULL && curr_character == ' ')
        advance();
}

void lexer::Lexer::advance() {
    position++;
    if (position > script.size() - 1) {
        curr_character = NULL;
    }
    else {
        curr_character = script[position];
    }
}

int lexer::Lexer::integer() {
    std::string number = "";
    while (curr_character != NULL && isdigit(curr_character)) {
        number.push_back(curr_character);
        advance();
    }
    return to_integer(number);
}

int lexer::Lexer::to_integer(std::string number) {
    int result = 0;
    for (int i = 0; i < number.size(); i++) {
        result += (int(number[i]) - 48) * std::pow(10, number.size() - 1 - i);
    }
    return result;
}

lexer::Token* lexer::Lexer::next_token() {
    while (curr_character != NULL) {

        skip_whitespace();

        if (curr_character == '+') {
            Token* token = new Token(PLUS, curr_character);
            advance();
            return token;
        }
        if (curr_character == '-') {
            Token* token = new Token(MINUS, curr_character);
            advance();
            return token;
        }
        if (std::isdigit(curr_character)) {
            Token* token = new Token(INTEGER, integer());

            return token;
        }
        if (curr_character == '/') {
            Token* token = new Token(DIV, curr_character);
            advance();
            return token;
        }
        if (curr_character == '*') {
            Token* token = new Token(MUL, curr_character);
            advance();
            return token;
        }
        if (curr_character == ')') {
            Token* token = new Token(RPAR, curr_character);
            advance();
            return token;
        }
        if (curr_character == '(') {
            Token* token = new Token(LPAR, curr_character);
            advance();
            return token;
        }

        error();
    }
    return nullptr;
}
