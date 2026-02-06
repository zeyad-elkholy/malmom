#include "lz77.h"
#include <vector>
#include <iostream>
bool LZ77::findLongestMatch(const std::vector<unsigned char>& data, int cursor, int& matchDist, int& matchLen)
{
  if ((cursor + 3)>= data.size()) {
    return false;
  }
  int limit = std::max(0, cursor - WINDOW_SIZE);
  // maybe optimize with hash chain later
  for (int i = cursor - 1; i >= limit; --i) {
    int length = 0;
    while (length < MAX_MATCH_LENGTH &&
           cursor + length < data.size() &&
           data[i + length] == data[cursor + length]) {
      ++length;
    }
    if (length >= 3 && length > matchLen) {
      matchLen = length;
      matchDist = cursor - i;
      if (matchLen == MAX_MATCH_LENGTH) {
        break;
      }
    }
  }
  if (matchLen >= 3) {
    return true;
  }else{
    return false;
  }
}
LZ77::LZ77()
{
}
LZ77::~LZ77()
{
}
std::vector<LZToken> LZ77::compress(const std::vector<unsigned char>& inputData)
{
  std::vector<LZToken> tokens;
  int cursor = 0;
  while (cursor < inputData.size()) {
    LZToken token;
    int matchDist = 0;
    int matchLen = 0;
    if (findLongestMatch(inputData , cursor , matchDist , matchLen)){
      token.isMatch = true;
      token.literal = 0;
      token.length = matchLen;
      token.distance = matchDist;
      tokens.push_back(token);
      cursor += matchLen;
    }else{
      token.isMatch = false;
      token.literal = inputData[cursor];
      token.length = 0;
      token.distance = 0;
      tokens.push_back(token);
      cursor += 1;

    }
  }
  return tokens;
}
std::vector<unsigned char> LZ77::decompress(const std::vector<LZToken>& tokens)
{
  std::vector<unsigned char> outputData; 
  outputData.reserve(tokens.size()* 2); 
  for (const auto& token : tokens){
    if (token.isMatch){
      int startPos = outputData.size() - token.distance;
      if (startPos < 0){
        continue;
      }

      for (int i = 0; i < token.length; ++i){
        outputData.push_back(outputData[startPos + i]);
      }
    }else{
      outputData.push_back(token.literal);
    }
  }
  return outputData;
}
