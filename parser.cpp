#include "parser.h"
#include <iostream>
#include <string>

#define INTEGER "INTEGER"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define MUL "MUL"
#define DIV "DIV"
#define LPAR "LPAR"
#define RPAR "RPAR"
#define OP "OP"
#define INT "INT"

parser::Num::Num(lexer::Token* num, int value) {
    val = value;
    integer = num;
}

parser::Op::Op(lexer::Token* ope) {
    op = ope;
}

parser::Unop::Unop(lexer::Token* ope) {
    op = ope;
}

parser::Node::Node(std::string t, Num* n, Op* o, Unop *uno) {
    type = t;
    num = n;
    op = o;
    unop = uno;
    right = nullptr;
    left = nullptr;
    next = nullptr;
}

parser::Parser::Parser(lexer::Lexer * lex) {
    lexer = lex;
    curr_token = lexer->next_token();
}

parser::Node* parser::Parser::factor() {
    Node* node;
    if (curr_token->type == INTEGER) {
        lexer::Token* token = curr_token;
        process(INTEGER);
        Num* num = new Num(token, token->value);
        node = new Node(INT, num, nullptr, nullptr);
        return node;
    }
    else if (curr_token->type == PLUS) {
        lexer::Token* token = curr_token;
        process(PLUS);
        Unop* unop = new Unop(token);
        node = new Node(PLUS, nullptr, nullptr, unop);
        node->next = factor();
        return node;
    }
    else if (curr_token->type == MINUS) {
        lexer::Token* token = curr_token;
        process(MINUS);
        Unop* unop = new Unop(token);
        node = new Node(MINUS, nullptr, nullptr, unop);
        node->next = factor();
        return node;
    }
    else {
        process(LPAR);
        node = expression();
        process(RPAR);
        return node;
    }

}

parser::Node* parser::Parser::term() {

    Node* node = factor();

    while (curr_token && (curr_token->type == DIV || curr_token->type == MUL)) {
        lexer::Token* token = curr_token;
        if (curr_token->type == DIV) {
            process(DIV);
        }
        else if (curr_token->type == MUL) {
            process(MUL);
        }
        Op* op = new Op(token);
        Node* new_node = new Node(OP, nullptr, op, nullptr);
        new_node->left = node;
        new_node->right = factor();
        node = new_node;
    }
    return node;
}

void parser::Parser::process(std::string expected_type) {
    if (curr_token->type == expected_type) {
        curr_token = lexer -> next_token();
    }
    else {
        lexer -> error();
    }
}

parser::Node* parser::Parser::expression() {

    Node* node = term();

    while (curr_token && (curr_token->type == PLUS || curr_token->type == MINUS)) {
        lexer::Token* token = curr_token;
        if (curr_token->type == PLUS) {
            process(PLUS);
        }
        else if (curr_token->type == MINUS) {
            process(MINUS);
        }
        Op* op = new Op(token);
        Node* new_node = new Node(OP, nullptr, op, nullptr);
        new_node->left = node;
        new_node->right = term();
        node = new_node;
    }
    return node;
}

parser::Node* parser::Parser::parse() {
    return expression();
}