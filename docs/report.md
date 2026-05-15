# Architecture Optimization Report

## Project Overview

Malmom is a C++ DEFLATE-style compression tool that combines an LZ77 front-end with Huffman coding. The goal of this update was to apply computer-architecture-oriented optimizations with minimal risk and without major algorithm redesign.

## Screenshot References

<img width="732" height="387" alt="Screenshot_15-ماي_20-12-19_28019" src="https://github.com/user-attachments/assets/cbc6d35a-c380-43af-a253-8c9970c168bf" />

## Optimizations Applied

Line numbers below refer to the updated `arch-opt-v1` branch state.

- **Blocking**
  - `src/lz77.cpp:76-106` — `LZ77::compress`
  - Processing is now organized in 256 KB blocks while preserving a 32 KB history window for low-risk in-place changes.

- **Multithreading (OpenMP)**
  - `src/huffman.cpp:41-85` — `Freqcounter::countTokens`
  - Frequency counting now uses per-thread local counters and a final merge when compiled with OpenMP support.

- **SIMD / Vectorization**
  - `src/lz77.cpp:11-37` — `compareMatchLength`
  - `src/lz77.cpp:41-63` — `LZ77::findLongestMatch`
  - The inner match-length comparison now checks 64-bit chunks first, which is friendly to compiler vectorization and reduces byte-by-byte work.

- **Loop Interchange / Memory Access Reshaping**
  - `src/bit_io.cpp:3-7` — `appendRawBytes`
  - `src/bit_io.cpp:65-69` — `BitWriter::headerWriter`
  - Header serialization now appends contiguous byte ranges directly instead of pushing one byte at a time in three separate loops.

- **Loop Unrolling**
  - `src/lz77.cpp:120-128` — `LZ77::decompress`
  - Match-copy expansion now uses a 4-byte unrolled copy path before the scalar tail loop.

## Performance Measurements

Use `tools/benchmark.cpp:67-118` after building `malmom` to collect:

- input size
- output size
- compression ratio
- compression time
- decompression time

The benchmark also validates that decompression reproduces the generated input exactly.

### Sample Measurement

Sample local run:

```bash
./benchmark ./malmom 524288
```

Observed output from the verification run on this branch:

- input size: `524288 bytes`
- output size: `136496 bytes`
- compression ratio: `0.260`
- compression time: `2656.810 ms`
- decompression time: `11.926 ms`

## Future Improvements

- Replace the brute-force LZ77 match search with a hash chain or dictionary-based search.
- Move to a truly independent block format if block-level compression and decompression parallelism become a priority.
- Add explicit SIMD intrinsics for AVX2/NEON instead of relying only on chunk compares and compiler vectorization.
