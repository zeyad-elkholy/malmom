#include "huffman.h"

// --- Freqcounter Implementation ---
// Helper: Map Length (3-258) to Symbol (257-285)
int getLengthSymbol(int len) {
    if (len == 258) return 285;
    if (len >= 3 && len <= 10) return 257 + (len - 3);
    if (len >= 11 && len <= 18) return 265 + (len - 11) / 2;
    if (len >= 19 && len <= 34) return 269 + (len - 19) / 4;
    if (len >= 35 && len <= 66) return 273 + (len - 35) / 8;
    if (len >= 67 && len <= 130) return 277 + (len - 67) / 16;
    if (len >= 131 && len <= 257) return 281 + (len - 131) / 32;
    return 0; // Error
}

// Helper: Map Distance (1-32768) to Symbol (0-29)
int getDistSymbol(int dist) {
    if (dist <= 4) return dist - 1;
    if (dist <= 8) return 4 + (dist - 5) / 2;
    if (dist <= 16) return 6 + (dist - 9) / 4;
    if (dist <= 32) return 8 + (dist - 17) / 8;
    if (dist <= 64) return 10 + (dist - 33) / 16;
    if (dist <= 128) return 12 + (dist - 65) / 32;
    if (dist <= 256) return 14 + (dist - 129) / 64;
    if (dist <= 512) return 16 + (dist - 257) / 128;
    if (dist <= 1024) return 18 + (dist - 513) / 256;
    if (dist <= 2048) return 20 + (dist - 1025) / 512;
    if (dist <= 4096) return 22 + (dist - 2049) / 1024;
    if (dist <= 8192) return 24 + (dist - 4097) / 2048;
    if (dist <= 16384) return 26 + (dist - 8193) / 4096;
    if (dist <= 32768) return 28 + (dist - 16385) / 8192;
    return 0; 
}

unsigned long long Freqcounter::getTotalBytes() {
  return totalBytes;
}
void Freqcounter::countTokens(const std::vector<LZToken>& tokens)
{
  reset();
  for (const auto& token : tokens) {
    if (token.isMatch) {
      int lenSymbol = getLengthSymbol(token.length);
      litLenCounter[lenSymbol]++;
      int distSymbol = getDistSymbol(token.distance);
      distCounter[distSymbol]++;
    }else {
      litLenCounter[token.literal]++;
    }
  }
  litLenCounter[256]++;
}
// --- HuffmanTree Implementation ---
void HuffmanTree::generateCodes(int nodeIdex, unsigned int path, int length) {
  if (tree[nodeIdex].left == -1 && tree[nodeIdex].right == -1) {
    codes[tree[nodeIdex].symbol] = {path, length};
    return;
  }
  if(tree[nodeIdex].left != -1 ){
    generateCodes(tree[nodeIdex].left, path << 1, length + 1);
  }
  if(tree[nodeIdex].right != -1 )
    generateCodes(tree[nodeIdex].right, (path << 1) | 1, length + 1);
}

bool HuffmanTree::decode(bitReader& reader, unsigned short& outsymbol){
  int currentIndex = rootIndex;
  while (true) {
    int bit = reader.readBit(1);
    if (bit == -1) {
      return false;
    }
    if (bit == 0) {
      currentIndex = tree[currentIndex].left;
    } else {
      currentIndex = tree[currentIndex].right;
    }
    if (tree[currentIndex].left == -1 && tree[currentIndex].right == -1) {
      outsymbol= tree[currentIndex].symbol;
      return true;
    }
  }
}

HuffmanTree::HuffmanTree(const unsigned long long* frequencies,int numSymbols) {
std::priority_queue<
        std::pair<long long, int>, 
        std::vector<std::pair<long long, int>>, 
        std::greater<std::pair<long long, int>>
    > pq;
  for (int i = 0 ; i < numSymbols; i++) {
    if(frequencies[i] > 0){
      Node newNode;
      newNode.symbol= static_cast<unsigned short>(i);
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
    newNode.symbol= 0;
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

HuffmanCode HuffmanTree::getCode(unsigned short symbol) {
  return codes[symbol];
};
