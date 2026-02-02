#include <iostream>
#include"huffman.h"
#include <string> 

void compress(const char* inputFile, const char* outputFile) {
    std::cout << "Scanning input file..." << std::endl;
    Freqcounter fc;
    fc.scanFile(inputFile);
    
    unsigned long long totalBytes = fc.getTotalBytes();
    if (totalBytes == 0) {
        std::cerr << "Error: Input file is empty or missing." << std::endl;
        return;
    }

    std::cout << "Building Huffman Tree..." << std::endl;
    HuffmanTree tree(fc.getFreq());

    BitWriter writer(outputFile);
    
    std::cout << "Writing header..." << std::endl;
    writer.headerWriter(fc.getFreq(), totalBytes);

    std::cout << "Compressing data..." << std::endl;
    std::ifstream input(inputFile, std::ios::binary);
    char buffer[4096];
    
    while (input.read(buffer, 4096) || input.gcount() > 0) {
        std::streamsize count = input.gcount();
        for (int i = 0; i < count; ++i) {
            unsigned char byte = reinterpret_cast<unsigned char&>(buffer[i]);
            writer.writeCode(tree.getCode(byte));
        }
        if (input.eof()) break;
    }
    input.close();
    std::cout << "Done! Compressed to: " << outputFile << std::endl;
}

void decompress(const char* inputFile, const char* outputFile) {
    // 1. Open Input
    bitReader reader(inputFile);
    
    std::cout << "Reading header..." << std::endl;
    unsigned long long frequencies[256];
    unsigned long long totalBytes;
    
    if (!reader.readHeader(frequencies, totalBytes)) {
        std::cerr << "Error: Could not read file header." << std::endl;
        return;
    }

    std::cout << "Rebuilding Tree..." << std::endl;
    HuffmanTree tree(frequencies);

    std::cout << "Decompressing " << totalBytes << " bytes..." << std::endl;
    std::ofstream output(outputFile, std::ios::binary);
    
    unsigned char byte;
    for (unsigned long long i = 0; i < totalBytes; i++) {
        if (tree.decode(reader, byte)) {
            output.put(byte);
        } else {
            std::cerr << "Error: Unexpected end of file or corruption." << std::endl;
            break;
        }
    }
    output.close();
    std::cout << "Done! Decompressed to: " << outputFile << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Huffman CLI Tool" << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "  Compress:   " << argv[0] << " -c <input_file> <output_file>" << std::endl;
        std::cout << "  Decompress: " << argv[0] << " -d <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    if (mode == "-c") {
        compress(argv[2], argv[3]);
    } else if (mode == "-d") {
        decompress(argv[2], argv[3]);
    } else {
        std::cerr << "Unknown mode: " << mode << std::endl;
        return 1;
    }

    return 0;
}
