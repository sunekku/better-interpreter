#include <iostream>
#include <string>
#include <vector>

namespace lexer {

    class Token {
    public:
        char value;
        std::string str;
        std::string type;
        Token(std::string t, char v);
        friend std::ostream& operator<< (std::ostream& out, const Token& token);
    };

    class Lexer{
    
        
    public:
        int position;
        std::string script;
        char curr_character;
        std::vector<Token *> reserved_keywords;

        Lexer(std::string scr);
        void error();
        char peek();
        void skip_whitespace();
        void advance();
        int integer();
        int to_integer(std::string number);
        Token* next_token();
        Token* keyword();
        //friend parser::Parser; //magic line of code that somehow solves all my problems
        
    };
}