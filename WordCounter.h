#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <map>
#include <string>
#include <vector>
#include <utility>
#include "WordExtractor.h"

class WordCounter {
private:
    std::map<std::string, int> wordCount;
    int totalWords = 0;
    WordExtractor extractor;

    static bool compareWordFrequency(std::pair<std::string, int> a,
                                     std::pair<std::string, int> b);

public:
    void processFile(std::string inputFilename);
    std::vector<std::pair<std::string, int>> getSortedWords();
    int getTotalWords() const;
};

#endif
