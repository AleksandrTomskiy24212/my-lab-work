#include "CSVWriter.h"
#include <fstream>
#include <iomanip>

void CSVWriter::write(std::vector<std::pair<std::string, int>> words, int totalWords, std::string filename) {
    std::ofstream outputFile(filename);
    outputFile << "Word,Frequency,%" << std::endl;
    for (auto item : words) {
        double percentage = (static_cast<double>(item.second) / totalWords) * 100;
        outputFile << item.first << "," << item.second << ","
                   << std::fixed << std::setprecision(2) << percentage << std::endl;
    }
}