#ifndef BITARRAY_OPERATORS_H
#define BITARRAY_OPERATORS_H

#include "BitArray.h"

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);
BitArray operator&(const BitArray& a, const BitArray& b);
BitArray operator|(const BitArray& a, const BitArray& b);
BitArray operator^(const BitArray& a, const BitArray& b);

#endif