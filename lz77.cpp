#include "lz77.h"
#include <vector>
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

}
std::vector<unsigned char> LZ77::decompress(const std::vector<LZToken>& tokens)
{
}
