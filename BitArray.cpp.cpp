#include "BitArray.h"

int BitArray::block_index(int i) const { return i / BITS_PER_BLOCK; }
int BitArray::bit_offset(int i) const { return i % BITS_PER_BLOCK; }

BitArray::BitArray() : sz(0) {}

BitArray::BitArray(int num_bits, unsigned long value) {
    if (num_bits < 0) throw std::out_of_range("num_bits must be >= 0");
    sz = num_bits;
    if (sz == 0) return;
    int blocks = (sz + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK;
    data.resize(blocks, 0);
    if (blocks > 0) {
        data[0] = value;
        if (sz % BITS_PER_BLOCK != 0) {
            unsigned long mask = (1UL << (sz % BITS_PER_BLOCK)) - 1;
            data.back() &= mask;
        }
    }
}

BitArray::BitArray(const BitArray& b) : data(b.data), sz(b.sz) {}

BitArray::~BitArray() {}

void BitArray::swap(BitArray& b) {
    data.swap(b.data);
    int tmp = sz;
    sz = b.sz;
    b.sz = tmp;
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        BitArray tmp(b);
        swap(tmp);
    }
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits < 0) throw std::out_of_range("Negative size");
    int old_sz = sz;
    sz = num_bits;
    int blocks = (sz + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK;
    data.resize(blocks, 0);

    if (value && sz > old_sz) {
        for (int i = old_sz; i < sz; ++i) {
            set(i, true);
        }
    }

    if (sz > 0 && sz % BITS_PER_BLOCK != 0) {
        unsigned long mask = (1UL << (sz % BITS_PER_BLOCK)) - 1;
        data.back() &= mask;
    }
}

void BitArray::clear() {
    data.clear();
    sz = 0;
}

void BitArray::push_back(bool bit) {
    resize(sz + 1);
    set(sz - 1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (sz != b.sz) throw std::invalid_argument("Sizes must be equal");
    for (size_t i = 0; i < data.size(); ++i)
        data[i] &= b.data[i];
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (sz != b.sz) throw std::invalid_argument("Sizes must be equal");
    for (size_t i = 0; i < data.size(); ++i)
        data[i] |= b.data[i];
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (sz != b.sz) throw std::invalid_argument("Sizes must be equal");
    for (size_t i = 0; i < data.size(); ++i)
        data[i] ^= b.data[i];
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n <= 0) return *this;
    if (n >= sz) {
        std::fill(data.begin(), data.end(), 0UL);
        return *this;
    }

    int block_shift = n / BITS_PER_BLOCK;
    int bit_shift = n % BITS_PER_BLOCK;

    if (block_shift > 0) {
        for (int i = (int)data.size() - 1; i >= block_shift; --i)
            data[i] = data[i - block_shift];
        for (int i = 0; i < block_shift; ++i)
            data[i] = 0;
    }

    if (bit_shift > 0) {
        for (int i = (int)data.size() - 1; i > 0; --i) {
            data[i] = (data[i] << bit_shift) | (data[i - 1] >> (BITS_PER_BLOCK - bit_shift));
        }
        data[0] <<= bit_shift;
    }

    if (sz % BITS_PER_BLOCK != 0) {
        unsigned long mask = (1UL << (sz % BITS_PER_BLOCK)) - 1;
        data.back() &= mask;
    }

    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n <= 0) return *this;
    if (n >= sz) {
        std::fill(data.begin(), data.end(), 0UL);
        return *this;
    }

    int block_shift = n / BITS_PER_BLOCK;
    int bit_shift = n % BITS_PER_BLOCK;

    if (block_shift > 0) {
        for (size_t i = 0; i < data.size() - block_shift; ++i)
            data[i] = data[i + block_shift];
        for (size_t i = data.size() - block_shift; i < data.size(); ++i)
            data[i] = 0;
    }

    if (bit_shift > 0) {
        for (size_t i = 0; i < data.size() - 1; ++i) {
            data[i] = (data[i] >> bit_shift) | (data[i + 1] << (BITS_PER_BLOCK - bit_shift));
        }
        data.back() >>= bit_shift;
    }

    if (sz % BITS_PER_BLOCK != 0) {
        unsigned long mask = (1UL << (sz % BITS_PER_BLOCK)) - 1;
        data.back() &= mask;
    }

    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray tmp(*this);
    tmp <<= n;
    return tmp;
}

BitArray BitArray::operator>>(int n) const {
    BitArray tmp(*this);
    tmp >>= n;
    return tmp;
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= sz) throw std::out_of_range("Index out of range");
    if (val)
        data[block_index(n)] |= (1UL << bit_offset(n));
    else
        data[block_index(n)] &= ~(1UL << bit_offset(n));
    return *this;
}

BitArray& BitArray::set() {
    std::fill(data.begin(), data.end(), ~0UL);
    if (sz % BITS_PER_BLOCK != 0) {
        unsigned long mask = (1UL << (sz % BITS_PER_BLOCK)) - 1;
        data.back() &= mask;
    }
    return *this;
}

BitArray& BitArray::reset(int n) {
    return set(n, false);
}

BitArray& BitArray::reset() {
    std::fill(data.begin(), data.end(), 0UL);
    return *this;
}

bool BitArray::any() const {
    for (unsigned long x : data)
        if (x != 0) return true;
    return false;
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray res(*this);
    for (unsigned long& x : res.data)
        x = ~x;
    if (res.sz % BITS_PER_BLOCK != 0) {
        unsigned long mask = (1UL << (res.sz % BITS_PER_BLOCK)) - 1;
        res.data.back() &= mask;
    }
    return res;
}

int BitArray::count() const {
    int c = 0;
    for (unsigned long x : data) {
        c += __builtin_popcountl(x);
    }
    return c;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= sz) throw std::out_of_range("Index out of range");
    return (data[block_index(i)] >> bit_offset(i)) & 1UL;
}

int BitArray::size() const {
    return sz;
}

bool BitArray::empty() const {
    return sz == 0;
}

std::string BitArray::to_string() const {
    std::string s;
    for (int i = sz - 1; i >= 0; --i) {
        s += ((*this)[i] ? '1' : '0');
    }
    return s;
}