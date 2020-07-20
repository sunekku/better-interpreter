
#include "interpreter.h"

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


int interpreter::Interpreter::calc(parser::Node* root) {
    if (!(root->left) && !(root->right))
        return root->num->val;
    if (root->op->op->type == MINUS)
        return calc(root->left) - calc(root->right);
    if (root->op->op->type == PLUS)
        return calc(root->left) + calc(root->right);
    if (root->op->op->type == DIV)
        return calc(root->left) / calc(root->right);
    if (root->op->op->type == MUL)
        return calc(root->left) * calc(root->right);
}

interpreter::Interpreter::Interpreter(parser::Parser* p) {
    parser = p;
}

int interpreter::Interpreter::interpret() {
    parser::Node* node = parser->parse();
    return calc(node);
}
