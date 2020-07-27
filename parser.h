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

    class Unop : AST {
    public: 
        lexer::Token* op;
        Unop(lexer::Token* ope);
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
        Unop* unop;
        Noop* noop;
        Compound* compound;
        Assign* assign;
        Var* var;
        Node* right;
        Node* left;
        Node* next;
        Node(std::string t, Num* n, Op* o, Unop* unop, Noop* no, Compound* c, Assign* a, Var *v);
    };

    class Noop : AST {

    };

    class Compound : AST {
    public:
        std::vector<Node *> children;
    };

    class Assign : AST {
        lexer::Token* op;
        Assign(lexer::Token* ope);
    };

    class Var : AST {
        lexer::Token* token;
        std::string val1;
        char val2;
        Var(lexer::Token* token);
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
        Node* program();
        Node* statement();
        Node* compound_statement();
        Node* assignment_statement();
        std::vector<parser::Node*> statement_list();
        
        //friend interpreter::Interpreter;
    };
}
