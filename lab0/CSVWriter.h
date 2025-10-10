#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <string>
#include <vector>
#include <utility> 

class CSVWriter {
public:
    void write(std::vector<std::pair<std::string, int>> words, int totalWords, std::string filename);
};

#endif