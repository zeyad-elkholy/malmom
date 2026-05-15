#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace {
std::size_t getFileSize(const std::string& path) {
    std::ifstream input(path.c_str(), std::ios::binary | std::ios::ate);
    return input ? static_cast<std::size_t>(input.tellg()) : 0U;
}

bool filesEqual(const std::string& first, const std::string& second) {
    std::ifstream lhs(first.c_str(), std::ios::binary);
    std::ifstream rhs(second.c_str(), std::ios::binary);
    if (!lhs || !rhs) {
        return false;
    }

    std::istreambuf_iterator<char> leftIt(lhs);
    std::istreambuf_iterator<char> rightIt(rhs);
    std::istreambuf_iterator<char> end;
    while (leftIt != end && rightIt != end) {
        if (*leftIt != *rightIt) {
            return false;
        }
        ++leftIt;
        ++rightIt;
    }

    return leftIt == end && rightIt == end;
}

bool generateInputFile(const std::string& path, std::size_t bytes) {
    std::ofstream output(path.c_str(), std::ios::binary);
    if (!output) {
        return false;
    }

    std::mt19937 generator(1337U);
    std::uniform_int_distribution<int> randomByte(0, 255);
    const std::string pattern = "MALMOM-BENCHMARK-PATTERN-1234567890";

    for (std::size_t i = 0; i < bytes; ++i) {
        unsigned char value = 0;
        if ((i % 4096) < 3072) {
            value = static_cast<unsigned char>(pattern[i % pattern.size()]);
        } else {
            value = static_cast<unsigned char>(randomByte(generator));
        }
        output.put(static_cast<char>(value));
    }

    return output.good();
}

int runCommand(const std::string& command) {
    return std::system(command.c_str());
}
}

int main(int argc, char* argv[]) {
    const std::string malmomBinary = argc > 1 ? argv[1] : "./malmom";
    const std::size_t inputBytes = argc > 2 ? static_cast<std::size_t>(std::strtoull(argv[2], NULL, 10)) : (2U * 1024U * 1024U);
    const std::string inputPath = "benchmark_input.bin";
    const std::string compressedPath = "benchmark_output.mlm";
    const std::string restoredPath = "benchmark_restored.bin";

    if (!generateInputFile(inputPath, inputBytes)) {
        std::cerr << "Failed to generate benchmark input file." << std::endl;
        return 1;
    }

    std::ostringstream compressCommand;
    compressCommand << malmomBinary << " -c " << inputPath << " " << compressedPath;

    std::ostringstream decompressCommand;
    decompressCommand << malmomBinary << " -d " << compressedPath << " " << restoredPath;

    const std::chrono::steady_clock::time_point compressStart = std::chrono::steady_clock::now();
    if (runCommand(compressCommand.str()) != 0) {
        std::cerr << "Compression command failed." << std::endl;
        return 1;
    }
    const std::chrono::steady_clock::time_point compressEnd = std::chrono::steady_clock::now();

    const std::chrono::steady_clock::time_point decompressStart = std::chrono::steady_clock::now();
    if (runCommand(decompressCommand.str()) != 0) {
        std::cerr << "Decompression command failed." << std::endl;
        return 1;
    }
    const std::chrono::steady_clock::time_point decompressEnd = std::chrono::steady_clock::now();

    if (!filesEqual(inputPath, restoredPath)) {
        std::cerr << "Round-trip verification failed." << std::endl;
        return 1;
    }

    const std::size_t sourceSize = getFileSize(inputPath);
    const std::size_t compressedSize = getFileSize(compressedPath);
    const double ratio = sourceSize == 0 ? 0.0 : static_cast<double>(compressedSize) / static_cast<double>(sourceSize);
    const double compressionMs = std::chrono::duration_cast<std::chrono::duration<double, std::milli> >(compressEnd - compressStart).count();
    const double decompressionMs = std::chrono::duration_cast<std::chrono::duration<double, std::milli> >(decompressEnd - decompressStart).count();

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Input size: " << sourceSize << " bytes" << std::endl;
    std::cout << "Output size: " << compressedSize << " bytes" << std::endl;
    std::cout << "Compression ratio: " << ratio << std::endl;
    std::cout << "Compression time: " << compressionMs << " ms" << std::endl;
    std::cout << "Decompression time: " << decompressionMs << " ms" << std::endl;
    std::cout << "Round-trip verified: yes" << std::endl;

    return 0;
}
