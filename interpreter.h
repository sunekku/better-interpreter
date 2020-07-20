#include "parser.h"
namespace interpreter {
    class Interpreter {
    public:
        parser::Parser* parser;
        Interpreter(parser::Parser* p);
        int calc(parser::Node* root);
        int interpret();
    };
}

