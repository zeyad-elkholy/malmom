#include "huffman.h"

// --- Freqcounter Implementation ---
void Freqcounter::scanFile(const char* filename) {
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

const unsigned long long* Freqcounter::getFreq() {
  return freq;
}

unsigned long long Freqcounter::getTotalBytes() {
  return totalBytes;
}

// --- HuffmanTree Implementation ---
void HuffmanTree::generateCodes(int nodeIdex, unsigned int path, int length) {
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

bool HuffmanTree::decode(bitReader& reader, unsigned char& outbyte){
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

HuffmanTree::HuffmanTree(const unsigned long long* frequencies){
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

HuffmanCode HuffmanTree::getCode(unsigned char byte){
  return codes[byte];
};
