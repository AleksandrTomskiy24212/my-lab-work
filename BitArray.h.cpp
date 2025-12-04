#ifndef BITARRAY_H
#define BITARRAY_H

#include <vector>
#include <string>
#include <stdexcept>

class BitArray {
private:
    std::vector<unsigned long> data;
    int sz;

    static constexpr int BITS_PER_BLOCK = sizeof(unsigned long) * 8;

    int block_index(int i) const;
    int bit_offset(int i) const;

public:
    BitArray();
    explicit BitArray(int num_bits, unsigned long value = 0);
    BitArray(const BitArray& b);
    ~BitArray();

    void swap(BitArray& b);
    BitArray& operator=(const BitArray& b);

    void resize(int num_bits, bool value = false);
    void clear();
    void push_back(bool bit);

    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    BitArray& set(int n, bool val = true);
    BitArray& set();
    BitArray& reset(int n);
    BitArray& reset();

    bool any() const;
    bool none() const;
    BitArray operator~() const;
    int count() const;
    bool operator[](int i) const;
    int size() const;
    bool empty() const;
    std::string to_string() const;
};

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);
BitArray operator&(const BitArray& a, const BitArray& b);
BitArray operator|(const BitArray& a, const BitArray& b);
BitArray operator^(const BitArray& a, const BitArray& b);

#endif