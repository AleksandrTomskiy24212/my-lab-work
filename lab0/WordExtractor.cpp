#include "WordExtractor.h"
#include <cctype>

std::vector<std::string> WordExtractor::extractWords(std::string line) {
    std::vector<std::string> words;
    std::string currentWord;
    
    for (char c : line) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            currentWord += c;
        } else {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
    }
    
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }
    
    return words;
}