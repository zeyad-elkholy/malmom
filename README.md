# Malmom

A lightweight and efficient compression tool implementing the DEFLATE algorithm in C++.

## About

Malmom is a file compression utility that implements the DEFLATE compression algorithm, which combines LZ77 dictionary compression with Huffman coding. This two-stage approach provides excellent compression ratios for a wide variety of file types.

The DEFLATE algorithm is the same compression method used by popular tools like gzip, ZIP, and PNG, making it a proven and reliable choice for data compression.

## Features

- **DEFLATE Algorithm**: Combines LZ77 and Huffman coding for efficient compression
- **Fast Compression**: Optimized C++ implementation for quick processing
- **Lossless Compression**: Guarantees perfect reconstruction of original data
- **Simple CLI Interface**: Easy-to-use command-line interface
- **Portable**: Standard C++ code that compiles on multiple platforms
- **No External Dependencies**: Uses only standard C++ libraries

## Project Structure

```
malmom/
├── include/           # Header files
│   ├── bit_io.h      # Bit-level I/O operations
│   ├── huffman.h     # Huffman coding implementation
│   └── lz77.h        # LZ77 compression algorithm
├── src/              # Source files
│   ├── bit_io.cpp    # Bit-level I/O implementation
│   ├── huffman.cpp   # Huffman coding implementation
│   ├── lz77.cpp      # LZ77 compression implementation
│   └── main.cpp      # Main program and CLI
├── playground/       # Development and testing files
└── README.md         # This file
```

## Building

### Prerequisites

- A C++ compiler with C++11 support (g++, clang++, etc.)
- Make (optional, for automated builds)

### Compilation

To compile the project manually:

```bash
g++ -std=c++11 -I. src/main.cpp src/bit_io.cpp src/huffman.cpp src/lz77.cpp -o malmom
```

For optimized builds, add optimization flags:

```bash
g++ -std=c++11 -O3 -I. src/main.cpp src/bit_io.cpp src/huffman.cpp src/lz77.cpp -o malmom
```

## Usage

Malmom provides two modes of operation: compression and decompression.

### Compress a File

```bash
./malmom -c input_file output_file.compressed
```

Example:
```bash
./malmom -c document.txt document.txt.compressed
```

### Decompress a File

```bash
./malmom -d input_file.compressed output_file
```

Example:
```bash
./malmom -d document.txt.compressed document_restored.txt
```

### Command-Line Options

- `-c` : Compress mode - compresses the input file
- `-d` : Decompress mode - decompresses the input file

## Algorithm

Malmom uses the DEFLATE algorithm, which consists of two main stages:

### 1. LZ77 Compression

The LZ77 algorithm performs dictionary-based compression by:
- Maintaining a sliding window of previously processed data (32 KB)
- Finding repeated sequences in the input data
- Replacing repeated sequences with references to earlier occurrences
- Encoding data as either literals (single bytes) or match tokens (length, distance pairs)

**Key Parameters:**
- Window size: 32,768 bytes (32 KB)
- Maximum match length: 258 bytes
- Minimum match length: 3 bytes

### 2. Huffman Coding

The Huffman coding stage further compresses the LZ77 output by:
- Analyzing the frequency of literals and LZ77 match symbols
- Building optimal prefix-free binary codes
- Using shorter codes for more frequent symbols
- Maintaining separate Huffman trees for literals/lengths and distances

**Features:**
- Dynamic Huffman trees built per file
- Separate trees for literal/length and distance alphabets
- Efficient bit-level encoding and decoding

## Performance

The compression ratio and speed depend on the input data characteristics:
- **Text files**: Typically achieve 50-70% compression
- **Already compressed files**: Little to no additional compression
- **Binary files**: Variable results depending on content patterns

## Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch** (`git checkout -b feature/amazing-feature`)
3. **Make your changes** and test thoroughly
4. **Commit your changes** (`git commit -m 'Add some amazing feature'`)
5. **Push to the branch** (`git push origin feature/amazing-feature`)
6. **Open a Pull Request**

### Development Guidelines

- Follow the existing code style and structure
- Test your changes with various file types
- Update documentation for new features
- Ensure backward compatibility when possible

## License

This project is available as open source. Please check the repository for specific license information.

## Acknowledgments

- The DEFLATE algorithm is described in [RFC 1951](https://tools.ietf.org/html/rfc1951)
- LZ77 algorithm by Abraham Lempel and Jacob Ziv (1977)
- Huffman coding by David A. Huffman (1952)
