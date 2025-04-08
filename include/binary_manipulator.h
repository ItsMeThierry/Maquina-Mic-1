#ifndef BINARY_MANIPULATOR_H
#define BINARY_MANIPULATOR_H

#include <string>
#include "data_types.h"

bits_32 string_to_binary(std::string string);

std::string binary_to_string(bits_8 b);
std::string binary_to_string(bits_32 b);
std::string binary_to_string(bits_32 b, int size);

#endif