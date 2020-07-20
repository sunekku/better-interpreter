#include <iostream>
#include <string>

namespace lexer {

    class Token {
    public:
        char value;
        std::string type;
        Token(std::string t, char v);
        friend std::ostream& operator<< (std::ostream& out, const Token& token);
    };

    class Lexer{
    
        
    public:
        int position;
        std::string script;
        char curr_character;

        Lexer(std::string scr);
        void error();
        void skip_whitespace();
        void advance();
        int integer();
        int to_integer(std::string number);
        Token* next_token();
        //friend parser::Parser; //magic line of code that somehow solves all my problems
        
    };
}