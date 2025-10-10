#include "WordCounter.h"
#include "CSVWriter.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }
    WordCounter counter;
    counter.processFile(argv[1]);

    CSVWriter writer;
    writer.write(counter.getSortedWordsPublic(), counter.getTotalWords(), argv[2]);
    
    return 0;
}