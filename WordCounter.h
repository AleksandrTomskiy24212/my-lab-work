#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <map>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include "WordExtractor.h" 

class WordCounter {
private:
    std::map<std::string, int> wordCount;
    int totalWords = 0;
    WordExtractor extractor; 
    std::list<std::string> lines;

    static bool compareWordFrequency(std::pair<std::string, int> a,
                                     std::pair<std::string, int> b);

    std::vector<std::pair<std::string, int>> getSortedWords();

public:
    void processLine(std::string line);
    void processFile(std::string inputFilename);
    std::vector<std::pair<std::string, int>> getSortedWordsPublic();
    int getTotalWords() const;
};

#endif