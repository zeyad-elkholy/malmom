#include <iostream>
#include <bitset> // A tool to SEE the bits (Crucial for learning)

int main() {
    // 1. The Setup
    unsigned char buffer = 0; // The accumulator
    int bitCount = 0;         // Tracks how full we are

    // 2. The Data: We want to write the code "101" (Value 5, Length 3)
    unsigned int code = 5; 
    int length = 3;

    std::cout << "Starting Buffer: " << std::bitset<8>(buffer) << "\n\n";

    // 3. The Loop (Simulating writeCode)
    // We loop from high bit to low bit (Length-1 down to 0)
    for (int i = length - 1; i >= 0; i--) {
        
        // STEP A: Extract the single bit
        int currentBit = (code >> i) & 1;
        std::cout << "Extracted Bit: " << currentBit << "\n";

        // STEP B: Shove the buffer to make room
        buffer = buffer << 1;

        // STEP C: Stamp the bit in
        buffer = buffer | currentBit;
        
        bitCount++;

        // Visualize what just happened
        std::cout << "Buffer Now:    " << std::bitset<8>(buffer) 
                  << " (Count: " << bitCount << ")\n\n";
    }

    return 0;
}
