#ifndef LEXIC_H
#define LEXIC_H

#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include "data_types.h"
#include "structs.h"

class Lexic{
    public:
        std::vector<token> table;
        
        void transition(char c);
        void insert_token(std::string classifier);
        void print_table();
        void start();
        void end();

    private:
        int state;
        std::string symbol;
};

#endif