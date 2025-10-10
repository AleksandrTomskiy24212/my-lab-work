#ifndef WORD_EXTRACTOR_H
#define WORD_EXTRACTOR_H

#include <vector>
#include <string>

class WordExtractor {
public:
    std::vector<std::string> extractWords(std::string line);
};

#endif