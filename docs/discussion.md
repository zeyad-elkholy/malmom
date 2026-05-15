# Discussion / Viva Prep

## Basic Questions

### 1. Why was blocking added to the LZ77 stage?
Blocking keeps compression work in smaller chunks instead of treating the whole file as one giant pass. In this project it was applied inside `LZ77::compress` so each block still keeps a 32 KB history window, which lowers risk while improving locality.

### 2. Where was multithreading used?
OpenMP was added in `Freqcounter::countTokens` to parallelize token-frequency counting. Each thread counts into local literal/length and distance arrays, then the results are merged safely.

### 3. How was SIMD/vectorization used without redesigning the algorithm?
The hottest byte-compare loop in `LZ77::findLongestMatch` now compares 64-bit chunks before falling back to byte checks. This is a small in-place change that is friendly to compiler auto-vectorization.

## Advanced Questions

### 4. Why was OpenMP not applied to the full LZ77 token search?
Full LZ77 compression is still order-sensitive because a match can advance the cursor by more than one byte. Parallelizing that path would require a bigger redesign around independent block boundaries, so the safer deadline-friendly change was to parallelize frequency counting first and leave larger parallel compression changes for future work.

### 5. What is the tradeoff of block-based compression in this implementation?
The benefit is simpler cache-friendly processing and a cleaner path for future parallel work. The tradeoff is that very long matches are limited to the current processing block, so compression ratio near block boundaries can be slightly worse than a completely unrestricted pass.
