#include "WordCounter.h"
#include "WordExtractor.h"
#include <fstream>
#include <algorithm>

bool WordCounter::compareWordFrequency(std::pair<std::string, int> a,
                                       std::pair<std::string, int> b) {
    return a.second > b.second;
}

void WordCounter::processLine(std::string line) {
    std::vector<std::string> words = extractor.extractWords(line);
    for (std::string word : words) {
        wordCount[word]++;
        totalWords++;
    }
}

void WordCounter::processFile(std::string inputFilename) {
    std::ifstream inputFile(inputFilename);
    std::string line;
    while (std::getline(inputFile, line)) {
        processLine(line);
    }
}

std::vector<std::pair<std::string, int>> WordCounter::getSortedWords() {
    std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
    std::sort(sortedWords.begin(), sortedWords.end(), compareWordFrequency);
    return sortedWords;
}

int WordCounter::getTotalWords() const {
    return totalWords;
}
