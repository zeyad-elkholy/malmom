#include <iostream>
#include <fstream>
#include <vector>
#include "huffman.h"
#include "lz77.h"
#include "bit_io.h"
const int length_base[] = {
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
    35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258
};
const int length_extra_bits[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0
};

// Distance Codes (Symbols 0-29)
const int dist_base[] = {
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
    257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577
};
const int dist_extra_bits[] = {
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
    7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13
};
void compress(const char* input_file, const char* output_file) {
  std::cout << "reading input file..."<< std::endl;
  std::ifstream input(input_file, std::ios::binary);
  if (!input) {
    std::cerr << "Error opening input file: " << input_file << std::endl;
    return;
  }
  std::ofstream output(output_file, std::ios::binary);
  if (!output) {
    std::cerr << "Error opening output file: " << output_file << std::endl;
    return;
  }
  std::vector<unsigned char> rawData((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  if (rawData.empty()) {
    std::cerr << "Input file is empty." << std::endl;
    return;
  }
  std::cout << "performing LZ77 compression..."<< std::endl;
  LZ77 lz;
  std::vector<LZToken> lz77Data = lz.compress(rawData);
  Freqcounter fc;
  fc.countTokens(lz77Data);
  std::cout << "building Huffman trees..."<< std::endl;
  HuffmanTree litTree(fc.getdistCounter(),286);
  HuffmanTree disTree(fc.getdistCounter(),30);
  std::vector<unsigned char> compressedBuffer;
  BitWriter Writer(compressedBuffer);
  std::cout << "Writing header..."<< std::endl;
  unsigned long long totalbytes = rawData.size();
  Writer.headerWriter(fc.getlitLenCounter(),fc.getdistCounter(),totalbytes);
  std::cout << "Encoding data..."<< std::endl;
  for (const auto& token : lz77Data) {
    if (!token.isMatch) {
      HuffmanCode h = litTree.getCode(token.literal);
      Writer.writeBits(h.bits, h.length);
//x
    }else{
      int lenSymbol = getLenthSymbol(token.length);
      HuffmanCode lencode = litTree.getCode(lenSymbol);
      Writer.writeBits(lencode.bits, lencode.length);
      int extraLenBits = length_extra_bits[lenSymbol-257];
      if (extraLenBits > 0) {
        int lenbase = length_base[lenSymbol-257];
        Writer.writeBits(token.length - lenbase, extraLenBits);
      }
      int distSym = getDistSymbol(token.distance);
      HuffmanCode distCode = disTree.getCode(distSym);
      Writer.writeBits(distCode.bits, distCode.length); // Write Symbol
      
      int distBits = dist_extra_bits[distSym];
      if (distBits > 0) {
          int distBase = dist_base[distSym];
          // Write Extra Bits (Raw value)
          Writer.writeBits(token.distance - distBase, distBits);

      }
    }
  }
  HuffmanCode endCode = litTree.getCode(256); // End of block Symbol
  Writer.writeBits(endCode.bits, endCode.length);
  Writer.~BitWriter();
  std::ofstream finalOutput(output_file, std::ios::binary);
  finalOutput.write(reinterpret_cast<const char*>(compressedBuffer.data()), compressedBuffer.size());
  output.close();
  std::cout << "Compression completed. Output file: " << output_file << std::endl;
}
void decompress(const char* inputFile, const char* outputFile) {
  bitReader reader(inputFile);
  unsigned long long totalBytes;
  unsigned long long litLenFreq[286] = {0};
  unsigned long long distFreq[30] = {0};
  std::cout << "Reading header..." << std::endl;
  if (!reader.readHeader(litLenFreq, distFreq, totalBytes)) {
    std::cerr << "Error reading header from input file: " << inputFile << std::endl;
    return;
  }
  std::cout << "Building Huffman trees..." << std::endl;
  HuffmanTree litTree(litLenFreq, 286);
  HuffmanTree distTree(distFreq, 30);
  std::cout << "Decompressing data..." << std::endl;
  std::vector<LZToken> tokens;
  bool endOfBlock = false;
  while (!endOfBlock) {
    unsigned short sym;
    if (!litTree.decode(reader, sym)) break;
  }
}

