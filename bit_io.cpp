#include "bit_io.h"

// --- bitReader Implementation ---
bool bitReader::readHeader(unsigned long long* litLenFreq,unsigned long long* distFreq, unsigned long long& totalBytes)
{
  file.read(reinterpret_cast<char*>(litLenFreq), 286*sizeof(unsigned long long));
  file.read(reinterpret_cast<char*>(distFreq), 30*sizeof(unsigned long long));
  file.read(reinterpret_cast<char*>(&totalBytes), sizeof(unsigned long long));
  return file.good();
}
bitReader::bitReader(const char* filename){
  file.open(filename, std::ios::binary);
  buffer = 0;
  bitCount = 0;
}

// x
int bitReader::readBit(int bits){
  int value = 0;
  for (int i = 0; i < bits; i++) {
    if (bitCount == 0) {
      char temp;
      if (!file.get(temp)) {
        return -1; // End of file or error
      }
      buffer = static_cast<unsigned char>(temp);
      bitCount = 8;
    }
    int bit = (buffer >> (bitCount - 1)) & 1;
    bitCount--;
    value = (value << 1) | bit;
  }
  return value;

}

bitReader::~bitReader(){
  if (file.is_open()) {
    file.close();
  }
}

// --- BitWriter Implementation ---
void BitWriter::flush()
{
  if (bitsInBuffer > 0) {
    buffer =buffer << (8 - bitsInBuffer); // Shift to fill the byte
    output.push_back(static_cast<unsigned char>(buffer));
    buffer = 0;
    bitsInBuffer = 0;
  }
}
BitWriter::BitWriter(std::vector<unsigned char>& outVector)
: output(outVector){
  buffer = 0;
  bitsInBuffer= 0;
}
void BitWriter::headerWriter(const unsigned long long* litLenFreq,const unsigned long long* distFreq, const unsigned long long& totalBytes)
{
  const char* pLit = reinterpret_cast<const char*>(litLenFreq);
    for (size_t i = 0; i < 286 * sizeof(unsigned long long); i++) {
        output.push_back(pLit[i]);
    }
  const char* Pdist = reinterpret_cast<const char*>(distFreq);
    for (size_t i = 0; i < 30 * sizeof(unsigned long long); i++) {
        output.push_back(Pdist[i]);
    }
  const char* pTotal= reinterpret_cast<const char*>(&totalBytes);
    for (size_t i = 0; i < sizeof(unsigned long long); i++) {
        output.push_back(pTotal[i]);
    }
}
void BitWriter::writeBits(unsigned int value, int bits)
{
  for(int i = bits - 1; i >= 0; --i) {
    unsigned int bit = (value >> i) & 1;
    buffer = (buffer << 1) | bit;
    bitsInBuffer++;
    if (bitsInBuffer == 8) {
      output.push_back(static_cast<unsigned char>(buffer));
      buffer = 0;
      bitsInBuffer = 0;
    }
  }
}
BitWriter::~BitWriter()
{
  flush();
}

