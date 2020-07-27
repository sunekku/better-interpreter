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
#define BEGIN "BEGIN"
#define END "END"
#define DOT "DOT"
#define ASSIGN "ASSSIGN"
#define SEMI "SEMI"
#define ID "ID"
#define COMPOUND "COMPOUND"

parser::Num::Num(lexer::Token* num, int value) {
    val = value;
    integer = num;
}

parser::Op::Op(lexer::Token* ope) {
    op = ope;
}

parser::Assign::Assign(lexer::Token* ope) {
    op = ope;
}

parser::Unop::Unop(lexer::Token* ope) {
    op = ope;
}

parser::Var::Var(lexer::Token* tok) {
    token = tok;
}

parser::Node::Node(std::string t, Num* n, Op* o, Unop *uno, Noop* no, Compound* c, Assign* a, Var* v) {
    type = t;
    num = n;
    op = o;
    unop = uno;
    right = nullptr;
    left = nullptr;
    next = nullptr;
    noop = no;
    compound = c;
    assign = a;
    var = v;
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
        node = new Node(INT, num, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        return node;
    }
    else if (curr_token->type == PLUS) {
        lexer::Token* token = curr_token;
        process(PLUS);
        Unop* unop = new Unop(token);
        node = new Node(PLUS, nullptr, nullptr, unop, nullptr, nullptr, nullptr, nullptr);
        node->next = factor();
        return node;
    }
    else if (curr_token->type == MINUS) {
        lexer::Token* token = curr_token;
        process(MINUS);
        Unop* unop = new Unop(token);
        node = new Node(MINUS, nullptr, nullptr, unop, nullptr, nullptr, nullptr, nullptr);
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
        Node* new_node = new Node(OP, nullptr, op, nullptr, nullptr, nullptr, nullptr, nullptr);
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
        Node* new_node = new Node(OP, nullptr, op, nullptr, nullptr, nullptr, nullptr, nullptr);
        new_node->left = node;
        new_node->right = term();
        node = new_node;
    }
    return node;
}

parser::Node* parser::Parser::factor() {
    parser::Node* node = parser::Parser::compound_statement();
    process(DOT);
    return node;
}

parser::Node* parser::Parser::compound_statement() {
    process(BEGIN);
    std::vector<parser::Node*> nodes = parser::Parser::statement_list();
    process(END);
    parser::Compound* root = new Compound;
    for (int i = 0; i < nodes.size(); i++) {
        (root->children).push_back(nodes[i]);
    }
    Node* node = new Node(COMPOUND, nullptr, nullptr, nullptr, nullptr, root, nullptr, nullptr);
    return node;
 
}

std::vector<parser::Node*> parser::Parser::statement_list() {
    parser::Node* node = parser::Parser::statement();
    std::vector<parser::Node*> results = { node };
    while (curr_token->type == SEMI) {
        process(SEMI);
        results.push_back(parser::Parser::statement());
    }
    if (curr_token->type == ID)
        lexer -> error();
    return results;
}

parser::Node* parser::Parser::statement() {
    parser::Node* node;
    if (curr_token->type == BEGIN)
        node = compound_statement();
    else if (curr_token->type == ID)
        node = assignment_statement();
    else
        node = empty();
    return node;
}

parser::Node* parser::Parser::assignment_statement() {
    Node* left = variable();
    lexer::Token* token = curr_token;
    process(ASSIGN);
    Node* right = expression();
    Assign* assign = new Assign(token);
    Node* node = new Node(ASSIGN, nullptr, nullptr, nullptr, nullptr, nullptr, assign, nullptr);
    node->left = left;
    node->right = right;
    return node;
}

parser::Node* parser::Parser::variable() {
    Var* var = new Var(curr_token);
    if ((curr_token->str).empty()) {
        var->val1 == curr_token->str;
    }
    else
        var->val2 == curr_token->value;
    Node* node = new Node(ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, var);
    process(ID);
    return node;
}

parser::Node* parser::Parser::empty() {
    Noop* noop = new Noop;
    Node* node = new Node("", nullptr, nullptr, nullptr, noop, nullptr, nullptr, nullptr);
    return node;
}

parser::Node* parser::Parser::parse() {
    return expression();
}