#ifndef BITIO_H
#define BITIO_H
#include <fstream>
#include <iostream>

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
    bool readHeader(unsigned long long* frequencies, unsigned long long& totalBytes);
    int readBit();
    ~bitReader();
};

class BitWriter {
  std::ofstream file;
  unsigned char buffer;
  int bitCount;
  void flush();
  public:
    BitWriter(const char* filename);
    void headerWriter(const unsigned long long* frequencies, const unsigned long long& totalBytes);
    void writeCode(HuffmanCode code);
    ~BitWriter();
};
#endif
