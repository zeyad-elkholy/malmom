#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include "bit_io.h"
#include "lz77.h"

struct Node{
  unsigned short symbol;
  unsigned long long freq;
  int left;
  int right;
};

class Freqcounter {
  private:
    unsigned long long litLenCounter[286]={0};
    unsigned long long distCounter[30]={0};
    unsigned long long totalBytes = 0;
  public:
    void countTokens(const std::vector<LZToken>& tokens);
    const unsigned long long* getlitLenCounter()const { return litLenCounter; }
    const unsigned long long* getdistCounter()const { return distCounter; }
    void reset() {
       std::fill(std::begin(litLenCounter), std::end(litLenCounter), 0);
       std::fill(std::begin(distCounter), std::end(distCounter), 0);
    }
    unsigned long long getTotalBytes();
};

class HuffmanTree {
  private:
    std::vector<Node> tree;
    HuffmanCode codes[286];
    int rootIndex;
    void generateCodes(int nodeIdex, unsigned int path, int length);
  public:
    bool decode(bitReader& reader, unsigned short& outsymbol);
    HuffmanTree(const unsigned long long* frequencies, int numSymbols);
    HuffmanCode getCode(unsigned short symbol);
};
#endif
