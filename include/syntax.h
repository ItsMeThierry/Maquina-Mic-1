#ifndef SYNTAX_H
#define SYNTAX_H

#include <vector>
#include <iostream>
#include "data_types.h"
#include "structs.h"

class Syntax{
    public:
        void program(std::vector<token> &table);
        void execute();
        void start();

        token get_current_token(int i);

    private:
        std::vector<token> *table;
        int i;
        int table_size;
};

#endif