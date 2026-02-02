#ifndef LZ77_H
#define LZ77_H
#include <vector>
#include <string>
#include <cstdint>

// This struct represents a single piece of compressed data.
// It can be either a LITERAL (a single byte) or a MATCH (copy command).
struct LZToken {
    bool isMatch;           // false = Literal, true = Match
    unsigned char literal;  // Valid only if isMatch == false
    int length;             // Valid only if isMatch == true (3 to 258)
    int distance;           // Valid only if isMatch == true (1 to 32768)
};

class LZ77 {
private:
    // Standard Deflate Window Size (32 KB)
    static const int WINDOW_SIZE = 32768;
    
    // Lookahead Buffer Size (Max Match Length)
    static const int MAX_MATCH_LENGTH = 258;
    static const int MIN_MATCH_LENGTH = 3;

    // Sliding Window Buffer
    // We keep a history of the data we've processed
    std::vector<unsigned char> window;

    // Helper: Finds the longest match for the data starting at 'cursor'
    // Returns true if a match >= 3 bytes is found.
    // updates 'matchDist' and 'matchLen' by reference.
    bool findLongestMatch(const std::vector<unsigned char>& data, int cursor, int& matchDist, int& matchLen);

public:
    LZ77();
    ~LZ77();

    // Main Function: Takes raw data, returns a vector of tokens
    std::vector<LZToken> compress(const std::vector<unsigned char>& inputData);
    
    // Reverse Function: Takes tokens, returns raw data (useful for debugging)
    std::vector<unsigned char> decompress(const std::vector<LZToken>& tokens);
};

#endif
