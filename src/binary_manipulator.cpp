#include "binary_manipulator.h"

bits_32 string_to_binary(std::string string){
    bits_32 result = 0;

    for(char c : string){
        result <<= 1;

        if(c == '1'){
            result |= 1;
        }
    }

    return result;
}

std::string binary_to_string(bits_8 b){
    std::string out;

    for(int i = 7; i >= 0; i--){
        int bit = (b >> i) & 1;

        if(bit){
            out += '1';
            continue;
        }

        out += '0';
    }

    return out;
}

std::string binary_to_string(bits_32 b){
    std::string out;

    for(int i = 31; i >= 0; i--){
        int bit = (b >> i) & 1;

        if(bit){
            out += '1';
            continue;
        }

        out += '0';
    }

    return out;
}

std::string binary_to_string(bits_32 b, int size){
    std::string out;

    for(int i = size-1; i >= 0; i--){
        int bit = (b >> i) & 1;

        if(bit){
            out += '1';
            continue;
        }

        out += '0';
    }

    return out;
}