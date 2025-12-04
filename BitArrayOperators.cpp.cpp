#include "BitArrayOperators.h"

bool operator==(const BitArray& a, const BitArray& b) {
    return a.size() == b.size() && a.data == b.data;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& a, const BitArray& b) {
    BitArray res(a);
    res &= b;
    return res;
}

BitArray operator|(const BitArray& a, const BitArray& b) {
    BitArray res(a);
    res |= b;
    return res;
}

BitArray operator^(const BitArray& a, const BitArray& b) {
    BitArray res(a);
    res ^= b;
    return res;
}