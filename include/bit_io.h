#ifndef BITIO_H
#define BITIO_H
#include <fstream>
#include <iostream>
#include <vector>

struct HuffmanCode {
  unsigned int bits;
  int length;
};

class bitReader {
  std::ifstream file;
  unsigned char buffer;
  int bitCount;
  public:
    bitReader(const char* filename);
    bool readHeader(unsigned long long* litLenFreq,unsigned long long* distFreq, unsigned long long& totalBytes);
    int readBit(int bits);
    ~bitReader();
HuffmanCode code;
};

class BitWriter {
  std::vector<unsigned char>& output;
  unsigned int buffer;
  int bitsInBuffer;
  void flush();
  public:
    BitWriter(std::vector<unsigned char>& outVector);
    void headerWriter(const unsigned long long* litLenFreq,const unsigned long long* distFreq, const unsigned long long& totalBytes);
    void writeBits(unsigned int value, int bits);
    ~BitWriter();
};
#endif
