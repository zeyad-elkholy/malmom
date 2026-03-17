# Open-Source Contribution Recommendations for zeyad-elkholy

> **Analysis date:** 2026-03-17  
> **Profile:** [github.com/zeyad-elkholy](https://github.com/zeyad-elkholy)  
> **Evidence base:** 17 public repos · DOTs config files · shell scripts · commit history

---

## A) Interest Profile (ranked by confidence)

| Rank | Interest Area | Confidence | Evidence |
|------|---------------|------------|---------|
| 1 | **C++ systems / algorithms** | ★★★★★ | 11 of 17 repos use C++; malmom, CP archive, PRODIGY series, GameOfLife |
| 2 | **Compression algorithms** | ★★★★★ | malmom implements full DEFLATE (LZ77 + Huffman) in C++ with 4 stars |
| 3 | **Media / video downloading** | ★★★★★ | Z-youtube-downloader repo; `yth.sh` / `ytm.sh` yt-dlp wrappers in DOTs/scripts |
| 4 | **MPV media player** | ★★★★★ | DOTs/mpv/ with `mpv.conf`, `input.conf`, Lua script-opts, custom scripts |
| 5 | **Video processing / time-calc** | ★★★★☆ | `time_video_calc.sh` in DOTs/scripts; pipesv script; Youtube folder |
| 6 | **Python scripting / GUI** | ★★★★☆ | Z-youtube-downloader (Python), ZYTgui (Python GUI), PRODIGY_SD_04 |
| 7 | **Subtitles / media metadata** | ★★★☆☆ | mpv config implies subtitle rendering (libass); yt-dlp downloads subtitles |
| 8 | **Linux desktop / dotfiles** | ★★★☆☆ | DOTs: zsh, sxhkd, zathura, rclone, sioyek configs |
| 9 | **Competitive programming** | ★★★☆☆ | CP repo with many solved problems |
| 10 | **Lua scripting** | ★★★☆☆ | DOTs Lua classified as primary language; mpv uses Lua scripts |

---

## B) Top 10 Organizations to Contribute To

### Summary Table

| # | Organization | Repo | Why it matches you | Difficulty | Stack |
|---|-------------|------|--------------------|------------|-------|
| 1 | yt-dlp | [yt-dlp/yt-dlp](https://github.com/yt-dlp/yt-dlp) | You built a YouTube downloader; use yt-dlp scripts daily | Easy–Medium | Python |
| 2 | mpv-player | [mpv-player/mpv](https://github.com/mpv-player/mpv) | You have custom mpv configs, Lua scripts, keybindings in DOTs | Medium–Hard | C / Lua |
| 3 | FFmpeg | [FFmpeg/FFmpeg](https://github.com/FFmpeg/FFmpeg) | Powers both mpv and yt-dlp; underpins all your media tooling | Hard | C |
| 4 | libass | [libass/libass](https://github.com/libass/libass) | Subtitle renderer used by mpv; C library matching your skill level | Medium | C |
| 5 | Aegisub | [Aegisub/Aegisub](https://github.com/Aegisub/Aegisub) | Subtitle editor; C++ matches malmom background | Medium | C++ |
| 6 | facebook/zstd | [facebook/zstd](https://github.com/facebook/zstd) | Zstandard compression; directly extends malmom's DEFLATE work | Medium | C / C++ |
| 7 | google/brotli | [google/brotli](https://github.com/google/brotli) | Brotli compression; C++ with Huffman (you already implemented it) | Medium | C++ |
| 8 | HandBrake | [HandBrake/HandBrake](https://github.com/HandBrake/HandBrake) | Video transcoding GUI; Python CLI + C backend | Medium | C / Python |
| 9 | subliminal | [Diaoul/subliminal](https://github.com/Diaoul/subliminal) | Python subtitle downloader; you already use yt-dlp's subtitle flags | Easy | Python |
| 10 | zlib-ng | [zlib-ng/zlib-ng](https://github.com/zlib-ng/zlib-ng) | Modern zlib; DEFLATE is your exact domain from malmom | Medium | C |

---

### Detailed Notes

#### 1. yt-dlp · [github.com/yt-dlp/yt-dlp](https://github.com/yt-dlp/yt-dlp)

**Why it matches you:**  
- You wrote a YouTube downloader in Python (`Z-youtube-downloader`).  
- Your DOTs repo contains `scripts/yth.sh` and `scripts/ytm.sh` — both yt-dlp wrappers you use daily.  
- Python is your secondary language; the codebase is well-structured.

**Newcomer path:**
- Contributing guide: https://github.com/yt-dlp/yt-dlp/blob/master/CONTRIBUTING.md  
- Good first issues: https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- Help wanted: https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3A%22help+wanted%22

**Difficulty:** Easy–Medium  
**Stack:** Python 3

---

#### 2. mpv-player · [github.com/mpv-player/mpv](https://github.com/mpv-player/mpv)

**Why it matches you:**  
- Your DOTs repo has a complete `mpv/` directory with `mpv.conf`, `input.conf`, `script-opts/`, and Lua `scripts/`.  
- You actively customize mpv keybindings and scripts, meaning you already understand the codebase at the user level.

**Newcomer path:**
- Contributing guide: https://github.com/mpv-player/mpv/blob/master/DOCS/contribute.md  
- Open issues: https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3A%22help+wanted%22  
- Good first issues: https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3A%22good+first+issue%22

**Difficulty:** Medium–Hard  
**Stack:** C, Lua

---

#### 3. FFmpeg · [github.com/FFmpeg/FFmpeg](https://ffmpeg.org/developer.html)

**Why it matches you:**  
- FFmpeg is the backbone of mpv (which you use) and yt-dlp (which you script around).  
- The DEFLATE/zlib codec in FFmpeg maps directly to your malmom knowledge.

**Newcomer path:**
- Contributing guide: https://ffmpeg.org/developer.html  
- Ticket system: https://trac.ffmpeg.org/report/16 (open easy tickets)  
- GitHub mirror issues: https://github.com/FFmpeg/FFmpeg/issues

**Difficulty:** Hard  
**Stack:** C

---

#### 4. libass · [github.com/libass/libass](https://github.com/libass/libass)

**Why it matches you:**  
- libass is the subtitle rendering library used by mpv (which is in your DOTs).  
- It is a focused C library — smaller scope than FFmpeg, easier entry point.  
- Subtitle work is one of your requested focus areas.

**Newcomer path:**
- Issues: https://github.com/libass/libass/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- All open issues: https://github.com/libass/libass/issues

**Difficulty:** Medium  
**Stack:** C

---

#### 5. Aegisub · [github.com/Aegisub/Aegisub](https://github.com/Aegisub/Aegisub)

**Why it matches you:**  
- Aegisub is the industry-standard subtitle editor, written in C++ — your primary language.  
- It uses Lua for automation scripts (which you already write for mpv).  
- Directly hits both subtitle and C++ interests.

**Newcomer path:**
- Issues: https://github.com/Aegisub/Aegisub/issues?q=is%3Aopen+label%3A%22help+wanted%22  
- All open issues: https://github.com/Aegisub/Aegisub/issues

**Difficulty:** Medium  
**Stack:** C++, Lua

---

#### 6. facebook/zstd · [github.com/facebook/zstd](https://github.com/facebook/zstd)

**Why it matches you:**  
- Zstandard (zstd) is a modern compression library — exactly what malmom implements at a lower level.  
- Your DEFLATE work (LZ77 + Huffman in malmom) gives you the mental model for zstd's FSE entropy coder.  
- They welcome documentation, testing, and platform-specific improvements.

**Newcomer path:**
- Contributing guide: https://github.com/facebook/zstd/blob/dev/CONTRIBUTING.md  
- Good first issues: https://github.com/facebook/zstd/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- Help wanted: https://github.com/facebook/zstd/issues?q=is%3Aopen+label%3A%22help+wanted%22

**Difficulty:** Medium  
**Stack:** C, C++

---

#### 7. google/brotli · [github.com/google/brotli](https://github.com/google/brotli)

**Why it matches you:**  
- Brotli uses Huffman coding (which you implemented from scratch in malmom/src/huffman.cpp).  
- C++ and some Python bindings — both in your toolset.  
- RFC 7932 is the natural next step after RFC 1951 (DEFLATE, which malmom implements).

**Newcomer path:**
- Issues: https://github.com/google/brotli/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- All issues: https://github.com/google/brotli/issues

**Difficulty:** Medium  
**Stack:** C, C++, Python

---

#### 8. HandBrake · [github.com/HandBrake/HandBrake](https://github.com/HandBrake/HandBrake)

**Why it matches you:**  
- HandBrake is an open video transcoder; its CLI is Python-scriptable and its core is C.  
- Your `time_video_calc.sh` script and mpv usage show hands-on video processing interest.  
- The project actively seeks contributors for documentation, new format support, and bug fixes.

**Newcomer path:**
- Contributing guide: https://github.com/HandBrake/HandBrake/blob/master/CONTRIBUTING.md  
- Good first issues: https://github.com/HandBrake/HandBrake/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- Help wanted: https://github.com/HandBrake/HandBrake/issues?q=is%3Aopen+label%3A%22help+wanted%22

**Difficulty:** Medium  
**Stack:** C, Python

---

#### 9. subliminal · [github.com/Diaoul/subliminal](https://github.com/Diaoul/subliminal)

**Why it matches you:**  
- Subliminal is a Python library for downloading subtitles — the subtitle equivalent of your youtube downloader.  
- Pure Python, easy contribution path, well-tested codebase.  
- Fills your requested "subtitle opportunities" focus area.

**Newcomer path:**
- Issues: https://github.com/Diaoul/subliminal/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- Help wanted: https://github.com/Diaoul/subliminal/issues?q=is%3Aopen+label%3A%22help+wanted%22  
- All issues: https://github.com/Diaoul/subliminal/issues

**Difficulty:** Easy  
**Stack:** Python

---

#### 10. zlib-ng · [github.com/zlib-ng/zlib-ng](https://github.com/zlib-ng/zlib-ng)

**Why it matches you:**  
- zlib-ng is a modern, high-performance fork of zlib — the canonical DEFLATE implementation.  
- Your malmom implements DEFLATE from scratch; this lets you contribute upstream to the real-world library.  
- They seek SIMD optimizations, platform patches, and test improvements.

**Newcomer path:**
- Contributing guide: https://github.com/zlib-ng/zlib-ng/blob/develop/CONTRIBUTING.md  
- Good first issues: https://github.com/zlib-ng/zlib-ng/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- Help wanted: https://github.com/zlib-ng/zlib-ng/issues?q=is%3Aopen+label%3A%22help+wanted%22

**Difficulty:** Medium  
**Stack:** C

---

## C) Issue Label Search for Each Organization

| Organization | `good first issue` | `help wanted` | `first-timers-only` | Roadmap / Ideas |
|---|---|---|---|---|
| yt-dlp | [link](https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3A%22help+wanted%22) | N/A | [wiki](https://github.com/yt-dlp/yt-dlp/wiki) |
| mpv-player | [link](https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3A%22help+wanted%22) | N/A | [roadmap](https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3Aroadmap) |
| FFmpeg | [trac easy](https://trac.ffmpeg.org/query?status=open&difficulty=easy) | N/A | N/A | [trac](https://trac.ffmpeg.org/) |
| libass | [link](https://github.com/libass/libass/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/libass/libass/issues?q=is%3Aopen+label%3A%22help+wanted%22) | N/A | [issues](https://github.com/libass/libass/issues) |
| Aegisub | [link](https://github.com/Aegisub/Aegisub/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/Aegisub/Aegisub/issues?q=is%3Aopen+label%3A%22help+wanted%22) | N/A | [issues](https://github.com/Aegisub/Aegisub/issues) |
| facebook/zstd | [link](https://github.com/facebook/zstd/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/facebook/zstd/issues?q=is%3Aopen+label%3A%22help+wanted%22) | N/A | [roadmap](https://github.com/facebook/zstd/issues?q=label%3Aroadmap) |
| google/brotli | [link](https://github.com/google/brotli/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/google/brotli/issues) | N/A | [issues](https://github.com/google/brotli/issues) |
| HandBrake | [link](https://github.com/HandBrake/HandBrake/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/HandBrake/HandBrake/issues?q=is%3Aopen+label%3A%22help+wanted%22) | N/A | [roadmap](https://github.com/HandBrake/HandBrake/milestones) |
| subliminal | [link](https://github.com/Diaoul/subliminal/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/Diaoul/subliminal/issues?q=is%3Aopen+label%3A%22help+wanted%22) | N/A | [issues](https://github.com/Diaoul/subliminal/issues) |
| zlib-ng | [link](https://github.com/zlib-ng/zlib-ng/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/zlib-ng/zlib-ng/issues?q=is%3Aopen+label%3A%22help+wanted%22) | N/A | [roadmap](https://github.com/zlib-ng/zlib-ng/issues?q=label%3Aroadmap) |

---

## D) Focused Opportunities

### Compression-Related Opportunities

| Project | Opportunity | Evidence from your profile | Link |
|---------|-------------|---------------------------|------|
| **facebook/zstd** | Test suite improvements, CLI flag documentation, Windows/macOS build fixes | malmom shows you understand entropy coding and bit-level I/O | https://github.com/facebook/zstd/issues?q=is%3Aopen+label%3A%22good+first+issue%22 |
| **google/brotli** | Python binding improvements, documentation, test vectors | malmom/src/huffman.cpp is the exact algorithm brotli uses | https://github.com/google/brotli/issues |
| **zlib-ng/zlib-ng** | Platform CI fixes, test coverage for edge cases, benchmarks | You implemented DEFLATE (RFC 1951) in malmom — you know the spec | https://github.com/zlib-ng/zlib-ng/issues?q=is%3Aopen+label%3A%22good+first+issue%22 |
| **yt-dlp** | Postprocessor improvements that touch FFmpeg's `-c:v copy` (codec pass-through, i.e., compression decisions) | You script yt-dlp daily; Z-youtube-downloader is your work | https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3A%22good+first+issue%22 |

### Subtitle-Related Opportunities

| Project | Opportunity | Evidence from your profile | Link |
|---------|-------------|---------------------------|------|
| **libass** | Font handling, ASS/SSA parser edge cases, documentation | mpv (your media player of choice) uses libass for subtitle rendering | https://github.com/libass/libass/issues |
| **Aegisub** | Lua automation scripts, C++ UI bug fixes, new format support | You write Lua scripts for mpv; Aegisub is C++ like malmom | https://github.com/Aegisub/Aegisub/issues |
| **yt-dlp** | Subtitle format support (SRT/VTT/ASS extraction), subtitle merge in postprocessors | You use `--write-subs`/`--embed-subs` flags in your yt-dlp scripts | https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3Asubtitles |
| **subliminal** | New provider integrations (subtitle sources), language detection improvements | Pure Python, low barrier, directly complements your YouTube downloader workflow | https://github.com/Diaoul/subliminal/issues?q=is%3Aopen+label%3A%22help+wanted%22 |

---

## E) 3 Concrete "First PR" Suggestions (Start This Week)

### PR #1 — yt-dlp: Fix or add a subtitle extractor (Python · Easy)

**Repository:** https://github.com/yt-dlp/yt-dlp  
**Why you:** You built a YouTube downloader in Python and script yt-dlp daily (`yth.sh`, `ytm.sh`). You already know how the tool behaves as a user.  
**What to do:**  
1. Browse open subtitle-related issues: https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3Asubtitles  
2. Or look for a broken extractor fix: https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3A%22site+support%22  
3. Pick a site extractor that's failing, run it locally, add a fix following https://github.com/yt-dlp/yt-dlp/blob/master/CONTRIBUTING.md#adding-support-for-a-new-site  
**Effort:** A few hours. Python, no build system needed.  
**Direct issue search:** https://github.com/yt-dlp/yt-dlp/issues?q=is%3Aopen+label%3A%22good+first+issue%22+label%3Asubtitles

---

### PR #2 — facebook/zstd: Documentation or test improvement (C · Medium)

**Repository:** https://github.com/facebook/zstd  
**Why you:** malmom implements DEFLATE (LZ77 + Huffman) in C++. zstd uses the same Huffman coding you already wrote from scratch in `src/huffman.cpp`. Reading zstd source code will feel familiar.  
**What to do:**  
1. Browse good first issues: https://github.com/facebook/zstd/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
2. Or improve test coverage for edge cases in `tests/` — you know how compression edge cases behave  
3. Alternatively: improve a CLI flag description in `programs/zstdcli.c`  
**Effort:** A weekend. C knowledge you already have.  
**Direct issue search:** https://github.com/facebook/zstd/issues?q=is%3Aopen+label%3A%22good+first+issue%22

---

### PR #3 — subliminal: Add or fix a subtitle provider (Python · Easy)

**Repository:** https://github.com/Diaoul/subliminal  
**Why you:** Your DOTs repo shows you regularly download and use subtitles with mpv + yt-dlp. Subliminal is a Python library that downloads subtitles — the natural companion tool.  
**What to do:**  
1. Browse open issues: https://github.com/Diaoul/subliminal/issues  
2. Find a subtitle provider that is broken or needs updating  
3. Follow the provider template in `subliminal/providers/` to add a new source or fix an existing one  
**Effort:** A few hours. Pure Python, pytest test suite.  
**Direct issue search:** https://github.com/Diaoul/subliminal/issues?q=is%3Aopen

---

## Quick Reference: URLs

| Resource | URL |
|----------|-----|
| Your GitHub profile | https://github.com/zeyad-elkholy |
| malmom (compression) | https://github.com/zeyad-elkholy/malmom |
| DOTs (configs+scripts) | https://github.com/zeyad-elkholy/DOTs |
| Z-youtube-downloader | https://github.com/zeyad-elkholy/Z-youtube-downloader |
| yt-dlp | https://github.com/yt-dlp/yt-dlp |
| mpv-player | https://github.com/mpv-player/mpv |
| FFmpeg | https://github.com/FFmpeg/FFmpeg |
| libass | https://github.com/libass/libass |
| Aegisub | https://github.com/Aegisub/Aegisub |
| facebook/zstd | https://github.com/facebook/zstd |
| google/brotli | https://github.com/google/brotli |
| HandBrake | https://github.com/HandBrake/HandBrake |
| subliminal | https://github.com/Diaoul/subliminal |
| zlib-ng | https://github.com/zlib-ng/zlib-ng |
