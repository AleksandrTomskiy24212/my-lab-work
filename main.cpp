#include "WordCounter.h"
#include "CSVWriter.h"
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    WordCounter counter;
    counter.processFile(inputFilename);

    CSVWriter writer;
    writer.write(counter.getSortedWords(), counter.getTotalWords(), outputFilename);

    return 0;
}
