#include "lexer.h"
#include <iostream>
#include <string>

namespace parser {

    class AST {

    };

    class Num : AST {
    public:
        lexer::Token* integer;
        int val;
        Num(lexer::Token* num, int val);
    };

    class Op : AST {
    public:
        lexer::Token* op;
        Op(lexer::Token* ope);
    };

    class Node {
    public:
        std::string type;
        Num* num;
        Op* op;
        Node* right;
        Node* left;
        Node(std::string t, Num* n, Op* o);
    };

    class Parser {
    public:
        lexer::Lexer* lexer;
        lexer::Token* curr_token;
        Parser(lexer::Lexer* lex);
        Node* factor();
        Node* term();
        void process(std::string expected_type);
        Node* expression();
        Node* parse();
        //friend interpreter::Interpreter;
    };
}
