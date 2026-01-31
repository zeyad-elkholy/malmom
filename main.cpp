#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <queue>
struct Node{
  unsigned char byte;
  unsigned long long freq;
  int left;
  int right;
};

struct HuffmanCode {
  unsigned int bits;
  int length;
};

class Freqcounter {
  private:
    unsigned long long freq[256]={0};
    unsigned long long totalBytes = 0;
  public:
    void scanFile(const char* filename) {
      std::ifstream file;
      file.open(filename,std::ios::binary);
      char buffer[4096];
      if (!file) {
          std::cerr << "Error: File could not be opened." << std::endl;
          return;
      }
      while (file.read(buffer, 4096) || file.gcount() >0) {
        std::streamsize count = file.gcount();
        totalBytes += count;
        for (int i = 0 ; i < count ; i++) {
          unsigned char byte = reinterpret_cast<unsigned char&>(buffer[i]);
          freq[byte]++;
        }
        if(file.eof())break;
      }
      file.close();
    }
    const unsigned long long* getFreq() {
      return freq;
    }
    unsigned long long getTotalBytes() {
      return totalBytes;
    }
};

class bitReader{
  std::ifstream file;
  unsigned char buffer;
  int bitCount;
  public:
  bitReader(const char* filename){
    file.open(filename, std::ios::binary);
    buffer = 0;
    bitCount = 0;
  }
  bool readHeader(unsigned long long* frequencies, unsigned long long& totalBytes){
    file.read(reinterpret_cast<char*>(frequencies), 256*sizeof(unsigned long long));
    file.read(reinterpret_cast<char*>(&totalBytes), sizeof(unsigned long long));
    return file.good();
  }
  int readBit(){
    if (bitCount == 0) {
      file.read(reinterpret_cast<char*>(&buffer), 1);
      bitCount = 8;
    }
    int bit = (buffer >> (bitCount - 1)) & 1;
    bitCount--;
    return bit;
  }
  ~bitReader(){
    if (file.is_open()) {
      file.close();
    }
  };
};
class HuffmanTree{
  private:
    std::vector<Node> tree;
    HuffmanCode codes[256];
    int rootIndex;
    void generateCodes(int nodeIdex, unsigned int path, int length) {
      if (tree[nodeIdex].left == -1 && tree[nodeIdex].right == -1) {
        codes[tree[nodeIdex].byte] = {path, length};
        return;
      }
      if(tree[nodeIdex].left != -1 ){
        generateCodes(tree[nodeIdex].left, path << 1, length + 1);
      }
      if(tree[nodeIdex].right != -1 )
        generateCodes(tree[nodeIdex].right, (path << 1) | 1, length + 1);
    }
  public:
    bool decode(bitReader& reader, unsigned char& outbyte){
      int currentIndex = rootIndex;
      while (true) {
        int bit = reader.readBit();
        if (bit == -1) {
          return false;
        }
        if (bit == 0) {
          currentIndex = tree[currentIndex].left;
        } else {
          currentIndex = tree[currentIndex].right;
        }
        if (tree[currentIndex].left == -1 && tree[currentIndex].right == -1) {
          outbyte = tree[currentIndex].byte;
          return true;
        }
      }
    }
    HuffmanTree(const unsigned long long* frequencies){
    std::priority_queue<
            std::pair<long long, int>, 
            std::vector<std::pair<long long, int>>, 
            std::greater<std::pair<long long, int>>
        > pq;
      for (int i = 0 ; i < 256 ; i++) {
        if(frequencies[i] > 0){
          Node newNode;
          newNode.byte = static_cast<unsigned char>(i);
          newNode.freq = frequencies[i];
          newNode.left = -1;
          newNode.right = -1;
          tree.push_back(newNode);
          pq.push(std::make_pair(frequencies[i],tree.size() - 1));
        }
      }
      while (pq.size() > 1) {
        auto first = pq.top(); pq.pop();
        auto second = pq.top(); pq.pop();
        Node newNode;
        newNode.byte = 0;
        newNode.freq = first.first + second.first;
        newNode.left = first.second;
        newNode.right = second.second;
        int newIndex = tree.size();
        tree.push_back(newNode);
        pq.push(std::make_pair(newNode.freq,newIndex));
      }
      rootIndex = pq.top().second;
      generateCodes(rootIndex,0,0);
    }
    HuffmanCode getCode(unsigned char byte){
      return codes[byte];
    };
};

class BitWriter{
  std::ofstream file;
  unsigned char buffer;
  int bitCount;
  void flush(){
    file.put(buffer);
    buffer = 0;
    bitCount = 0;
  };
  public:
  BitWriter(const char* filename){
    file.open(filename, std::ios::binary);
    buffer  = 0;
    bitCount = 0;
  }
  void headerWriter(const unsigned long long* frequencies, const unsigned long long& totalBytes){
      file.write(reinterpret_cast<const char*>(frequencies), 256*sizeof(unsigned long long));
      file.write(reinterpret_cast<const char*>(&totalBytes), sizeof(totalBytes));
    
  }
  void writeCode(HuffmanCode code){
    for (int i = code.length - 1 ; i >= 0 ; i--) {
      unsigned int bit = (code.bits >> i) & 1;
      buffer = (buffer << 1) | bit;
      bitCount++;
      if (bitCount == 8) {
        flush();
      }
    }
  }
  ~BitWriter(){
    if (bitCount > 0) {
      buffer = buffer << (8 - bitCount);
      flush();
    }
    if (file.is_open()) {
      file.close();
    }
  };
};
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
