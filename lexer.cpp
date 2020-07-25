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
#define OP "OP"
#define INT "INT"
#define BEGIN "BEGIN"
#define END "END"
#define DOT "DOT"
#define ASSIGN "ASSSIGN"
#define SEMI "SEMI"
#define ID "ID"


std::ostream& lexer::operator<< (std::ostream& out, const lexer::Token& token)
{
    out << "Token type: " << token.type << "\n" << "Token value: " << token.value << "\n";
    return out;
}

lexer::Token::Token(std::string t, char v) {
    type = t;
    value = v;
    str = nullptr;
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

char lexer::Lexer::peek() {
    int peek_pos = position + 1;
    if (peek_pos > script.size() - 1)
        return 0;
    else
        return script[peek_pos];
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

lexer::Token* lexer::Lexer::keyword() {
    std::string keyword = "";
    while (curr_character != NULL && isdigit(curr_character)) {
        keyword.push_back(curr_character);
        advance();
    }
    if (keyword.size() == 1) {
        for (int i = 0; i < reserved_keywords.size(); i++) {
            if (keyword[0] == reserved_keywords[i]->value)
                return reserved_keywords[i];
        }
    }
    else if (keyword.size() > 1) {
        for (int i = 0; i < reserved_keywords.size(); i++) {
            if (!(keyword.compare(reserved_keywords[i]->str)))
                return reserved_keywords[i];
        }
    }
    if (keyword.size() == 1) {
        lexer::Token* token = new Token(ID, keyword[0]);
        return token;
    }
    else {
        lexer::Token* token = new Token(ID, 0);
        token->str = keyword;
        return token;
    }
}

lexer::Token* lexer::Lexer::next_token() {
    while (curr_character != NULL) {

        skip_whitespace();

        if (curr_character == ':' && lexer::Lexer::peek() == '=') {
            Token* token = new Token(SEMI, 0);
            token->str = ":=";
            advance();
            advance();
            return token;
        }
        if (curr_character == ';') {
            Token* token = new Token(SEMI, curr_character);
            advance();
            return token;
        }
        if (curr_character == '.') {
            Token* token = new Token(DOT, curr_character);
            advance();
            return token;
        }
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
