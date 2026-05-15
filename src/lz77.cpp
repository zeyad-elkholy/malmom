#include "../include/lz77.h"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

namespace {
const int PROCESSING_BLOCK_SIZE = 256 * 1024;

int compareMatchLength(const std::vector<unsigned char>& data, int left, int right, int maxLength) {
  int length = 0;

  while (length + static_cast<int>(sizeof(std::uint64_t)) <= maxLength) {
    std::uint64_t leftChunk = 0;
    std::uint64_t rightChunk = 0;
    std::memcpy(&leftChunk, &data[left + length], sizeof(leftChunk));
    std::memcpy(&rightChunk, &data[right + length], sizeof(rightChunk));
    if (leftChunk != rightChunk) {
      break;
    }
    length += static_cast<int>(sizeof(std::uint64_t));
  }

  while (length + 4 <= maxLength &&
         data[left + length] == data[right + length] &&
         data[left + length + 1] == data[right + length + 1] &&
         data[left + length + 2] == data[right + length + 2] &&
         data[left + length + 3] == data[right + length + 3]) {
    length += 4;
  }

  while (length < maxLength && data[left + length] == data[right + length]) {
    ++length;
  }

  return length;
}
}

bool LZ77::findLongestMatch(const std::vector<unsigned char>& data, int cursor, int historyStart, int maxLength, int& matchDist, int& matchLen)
{
  if (maxLength < MIN_MATCH_LENGTH || (cursor + MIN_MATCH_LENGTH) > data.size()) {
    return false;
  }
  int limit = std::max(historyStart, cursor - WINDOW_SIZE);
  for (int i = cursor - 1; i >= limit; --i) {
    if (data[i] != data[cursor] ||
        data[i + 1] != data[cursor + 1] ||
        data[i + 2] != data[cursor + 2]) {
      continue;
    }

    int length = MIN_MATCH_LENGTH;
    length += compareMatchLength(data, i + MIN_MATCH_LENGTH, cursor + MIN_MATCH_LENGTH, maxLength - MIN_MATCH_LENGTH);
    if (length >= MIN_MATCH_LENGTH && length > matchLen) {
      matchLen = length;
      matchDist = cursor - i;
      if (matchLen == maxLength) {
        break;
      }
    }
  }
  if (matchLen >= MIN_MATCH_LENGTH) {
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
    int blockStart = cursor;
    int blockEnd = std::min(blockStart + PROCESSING_BLOCK_SIZE, static_cast<int>(inputData.size()));
    int historyStart = std::max(0, blockStart - WINDOW_SIZE);

    while (cursor < blockEnd) {
      LZToken token;
      int matchDist = 0;
      int matchLen = 0;
      int maxLength = std::min(MAX_MATCH_LENGTH, blockEnd - cursor);
      if (findLongestMatch(inputData, cursor, historyStart, maxLength, matchDist, matchLen)){
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

      int i = 0;
      for (; i + 4 <= token.length; i += 4){
        outputData.push_back(outputData[startPos + i]);
        outputData.push_back(outputData[startPos + i + 1]);
        outputData.push_back(outputData[startPos + i + 2]);
        outputData.push_back(outputData[startPos + i + 3]);
      }
      for (; i < token.length; ++i){
        outputData.push_back(outputData[startPos + i]);
      }
    }else{
      outputData.push_back(token.literal);
    }
  }
  return outputData;
}
