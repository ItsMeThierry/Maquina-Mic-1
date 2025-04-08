#ifndef SYNTAX_H
#define SYNTAX_H

#include <vector>
#include <iostream>
#include "data_types.h"
#include "structs.h"
#include "binary_manipulator.h"

class Syntax{
    public:
        std::vector<bits_32> program(std::vector<token> &table);
        void execute();
        void start();

        token get_current_token(int i);

    private:
        std::vector<token> *table;
        std::vector<bits_32> binaries;
        int i;
        int table_size;
};

#endif