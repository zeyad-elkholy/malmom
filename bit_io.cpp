#include "bit_io.h"

// --- bitReader Implementation ---
bitReader::bitReader(const char* filename){
  file.open(filename, std::ios::binary);
  buffer = 0;
  bitCount = 0;
}

bool bitReader::readHeader(unsigned long long* frequencies, unsigned long long& totalBytes){
  file.read(reinterpret_cast<char*>(frequencies), 256*sizeof(unsigned long long));
  file.read(reinterpret_cast<char*>(&totalBytes), sizeof(unsigned long long));
  return file.good();
}

int bitReader::readBit(){
  if (bitCount == 0) {
    file.read(reinterpret_cast<char*>(&buffer), 1);
    bitCount = 8;
  }
  int bit = (buffer >> (bitCount - 1)) & 1;
  bitCount--;
  return bit;
}

bitReader::~bitReader(){
  if (file.is_open()) {
    file.close();
  }
}

// --- BitWriter Implementation ---
void BitWriter::flush(){
  file.put(buffer);
  buffer = 0;
  bitCount = 0;
}

BitWriter::BitWriter(const char* filename){
  file.open(filename, std::ios::binary);
  buffer  = 0;
  bitCount = 0;
}

void BitWriter::headerWriter(const unsigned long long* frequencies, const unsigned long long& totalBytes){
    file.write(reinterpret_cast<const char*>(frequencies), 256*sizeof(unsigned long long));
    file.write(reinterpret_cast<const char*>(&totalBytes), sizeof(totalBytes));
}

void BitWriter::writeCode(HuffmanCode code){
  for (int i = code.length - 1 ; i >= 0 ; i--) {
    unsigned int bit = (code.bits >> i) & 1;
    buffer = (buffer << 1) | bit;
    bitCount++;
    if (bitCount == 8) {
      flush();
    }
  }
}

BitWriter::~BitWriter(){
  if (bitCount > 0) {
    buffer = buffer << (8 - bitCount);
    flush();
  }
  if (file.is_open()) {
    file.close();
  }
}
