#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include "lexic.h"
#include "syntax.h"

class Interpreter{
    public:
        Interpreter();

        void check_line(std::string line);
    
    private:
        Lexic lexic;
        Syntax syntax;
        int l;
};

#endif