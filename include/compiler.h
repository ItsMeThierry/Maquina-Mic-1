#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <vector>
#include "lexic.h"
#include "syntax.h"
#include "data_types.h"

class Compiler{
    public:
        Compiler();

        std::vector<bits_32> check_line(std::string line);
    
    private:
        Lexic lexic;
        Syntax syntax;
        int l;
};

#endif