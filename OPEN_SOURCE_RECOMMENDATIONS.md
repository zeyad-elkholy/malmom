# Open-Source Contribution Recommendations for zeyad-elkholy

> **Analysis date:** 2026-03-17  
> **Profile:** [github.com/zeyad-elkholy](https://github.com/zeyad-elkholy)  
> **Evidence base:** 17 public repos · DOTs config files · shell scripts · commit history  
> **Filter:** ⚡ **Google Summer of Code (GSoC) organizations only**  
> GSoC org directory: https://summerofcode.withgoogle.com/programs/2024/organizations

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

## B) Top Organizations to Contribute To (GSoC only)

> All organizations below are confirmed **Google Summer of Code** participants.

### Summary Table

| # | Organization | GSoC page | Why it matches you | Difficulty | Stack |
|---|-------------|-----------|---------------------|------------|-------|
| 1 | FFmpeg | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/ffmpeg) | Powers mpv (your media player) and yt-dlp; DEFLATE codec matches malmom | Hard | C |
| 2 | VideoLAN (VLC) | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/videolan) | VLC is a media player like mpv; active subtitles + codec work | Medium–Hard | C / C++ |
| 3 | CCExtractor | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/ccextractor-development) | Dedicated subtitle extraction org; Python + C; directly hits your subtitle focus | Easy–Medium | C / Python |
| 4 | KDE | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/kde) | Kdenlive video editor is C++; many C++ GSoC projects aligned with your skills | Medium | C++ / Python |
| 5 | GNOME | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/gnome) | Pitivi video editor + GStreamer multimedia framework; Python matches your secondary skill | Medium | C / Python |
| 6 | Xiph.org | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/xiph-org) | Ogg/Vorbis/Opus/FLAC/Theora; audio-video codecs and compression match malmom | Medium | C |
| 7 | mpv | [GSoC via VideoLAN](https://summerofcode.withgoogle.com/programs/2024/organizations/videolan) | Your exact media player; DOTs/mpv/ shows deep familiarity with config and Lua scripting | Medium–Hard | C / Lua |
| 8 | Blender Foundation | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/blender-foundation) | 3D/video pipeline in C++ + Python; video sequence editor hits your media interest | Medium | C++ / Python |
| 9 | LLVM | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/llvm-compiler-infrastructure) | C++ compiler infrastructure; low-level systems match malmom's bit-manipulation work | Hard | C++ |
| 10 | Python Software Foundation | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/python-software-foundation) | Python is your secondary language; CPython and stdlib improvements are well-scoped | Medium | Python / C |
| 11 | OpenCV | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/opencv) | C++ computer vision and video processing; matches your video + C++ interests | Medium | C++ / Python |
| 12 | GNU Project | [GSoC 2024](https://summerofcode.withgoogle.com/programs/2024/organizations/gnu-project) | gzip/bzip2/xz are in the GNU ecosystem; DEFLATE knowledge from malmom applies | Medium | C / C++ |

---

### Detailed Notes

#### 1. FFmpeg · [github.com/FFmpeg/FFmpeg](https://github.com/FFmpeg/FFmpeg)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/ffmpeg  
**Project ideas:** https://trac.ffmpeg.org/wiki/SponsoringPrograms/GSoC

**Why it matches you:**  
- FFmpeg is the backbone of mpv (your configured media player) and of all the yt-dlp scripts in your DOTs.  
- FFmpeg's zlib/DEFLATE codec (`libavcodec/zlib_wrapper.c`) is the production version of what you built from scratch in malmom.  
- GSoC 2024 ideas included subtitle improvements, new codec support, and performance work.

**Newcomer path:**
- Contributing guide: https://ffmpeg.org/developer.html  
- Easy trac tickets: https://trac.ffmpeg.org/query?status=open&difficulty=easy  
- GSoC project ideas: https://trac.ffmpeg.org/wiki/SponsoringPrograms/GSoC

**Difficulty:** Hard  
**Stack:** C

---

#### 2. VideoLAN (VLC) · [github.com/videolan](https://github.com/videolan)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/videolan  
**Project ideas:** https://wiki.videolan.org/SoC_2024/

**Why it matches you:**  
- VLC is the most widely used open media player — the same category as mpv, which you deeply configure in your DOTs.  
- VideoLAN GSoC projects span subtitle rendering, codec improvements, and UI work — all hitting your interest areas.  
- VLC uses C for its core and has C++ modules, matching your primary language.

**Newcomer path:**
- Contributing guide: https://wiki.videolan.org/Developers_Corner  
- Good first issues: https://code.videolan.org/videolan/vlc/-/issues?label_name%5B%5D=Newcomers  
- GSoC project ideas: https://wiki.videolan.org/SoC_2024/

**Difficulty:** Medium–Hard  
**Stack:** C, C++

---

#### 3. CCExtractor · [github.com/CCExtractor](https://github.com/CCExtractor)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/ccextractor-development  
**Project ideas:** https://github.com/CCExtractor/ccextractor/wiki/Google-Summer-of-Code-2024

**Why it matches you:**  
- CCExtractor is entirely focused on subtitle extraction from video files — your exact focus area.  
- Their main tool is written in C (matching malmom's systems approach), with Python tooling around it.  
- They have a very welcoming GSoC track record and explicitly publish easy starter tasks.  
- mpv (which you use) can call CCExtractor to extract embedded subtitles.

**Newcomer path:**
- Contributing guide: https://github.com/CCExtractor/ccextractor/blob/master/CONTRIBUTING.md  
- Good first issues: https://github.com/CCExtractor/ccextractor/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- GSoC ideas: https://github.com/CCExtractor/ccextractor/wiki/Google-Summer-of-Code-2024

**Difficulty:** Easy–Medium  
**Stack:** C, Python

---

#### 4. KDE · [github.com/KDE](https://github.com/KDE)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/kde  
**Project ideas:** https://community.kde.org/GSoC/2024/Ideas

**Why it matches you:**  
- **Kdenlive** (KDE's video editor) is written in C++ — your primary language from malmom.  
- KDE has dozens of C++ GSoC projects; you can focus on video/multimedia tools.  
- Kdenlive has subtitle track support, connecting your C++ and subtitle interests.

**Newcomer path:**
- Contributing guide: https://community.kde.org/Get_Involved/development  
- Good first issues: https://bugs.kde.org/buglist.cgi?keywords=junior-jobs  
- GSoC project ideas: https://community.kde.org/GSoC/2024/Ideas

**Difficulty:** Medium  
**Stack:** C++, Python, QML

---

#### 5. GNOME · [gitlab.gnome.org/GNOME](https://gitlab.gnome.org/GNOME)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/gnome  
**Project ideas:** https://wiki.gnome.org/Outreach/SummerOfCode/2024/Ideas

**Why it matches you:**  
- **Pitivi** (GNOME's video editor, Python + GStreamer) directly hits your video processing and Python interests.  
- **GStreamer** multimedia framework (C) underpins many media apps and is a GSoC target within GNOME.  
- Your Linux desktop experience (DOTs: sxhkd, zsh, etc.) means you already run and understand the GNOME ecosystem.

**Newcomer path:**
- Contributing guide: https://wiki.gnome.org/Newcomers/  
- Good first issues (GitLab): https://gitlab.gnome.org/groups/GNOME/-/issues?label_name%5B%5D=4.+Newcomers  
- GSoC project ideas: https://wiki.gnome.org/Outreach/SummerOfCode/2024/Ideas

**Difficulty:** Medium  
**Stack:** C, Python, GStreamer

---

#### 6. Xiph.org · [github.com/xiph](https://github.com/xiph)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/xiph-org  
**Project ideas:** https://wiki.xiph.org/Google_Summer_of_Code

**Why it matches you:**  
- Xiph.org maintains **Opus** (audio codec), **FLAC** (lossless compression), **Ogg** (container), and **Theora/Daala** (video codecs).  
- FLAC uses a form of LPC + Rice coding, conceptually adjacent to your LZ77 + Huffman work in malmom.  
- Opus and FLAC are both used by mpv (your media player) for audio decoding.

**Newcomer path:**
- Contributing guide: https://wiki.xiph.org/Contribute  
- Issues (FLAC): https://github.com/xiph/flac/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- Issues (Opus): https://github.com/xiph/opus/issues  
- GSoC ideas: https://wiki.xiph.org/Google_Summer_of_Code

**Difficulty:** Medium  
**Stack:** C

---

#### 7. mpv (via VideoLAN GSoC umbrella) · [github.com/mpv-player/mpv](https://github.com/mpv-player/mpv)

**GSoC umbrella:** https://summerofcode.withgoogle.com/programs/2024/organizations/videolan  
**Why it matches you:**  
- You have a complete, customized mpv configuration in your DOTs repo: `mpv.conf`, `input.conf`, Lua `scripts/`, and `script-opts/`.  
- You are already a power user who understands mpv's scripting API — the next step is contributing to the C core.  
- mpv contributors have participated in GSoC under the VideoLAN umbrella.

**Newcomer path:**
- Contributing guide: https://github.com/mpv-player/mpv/blob/master/DOCS/contribute.md  
- Open issues: https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3A%22help+wanted%22  
- Good first issues: https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3A%22good+first+issue%22

**Difficulty:** Medium–Hard  
**Stack:** C, Lua

---

#### 8. Blender Foundation · [github.com/blender/blender](https://github.com/blender/blender)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/blender-foundation  
**Project ideas:** https://developer.blender.org/docs/handbook/contributing/gsoc/

**Why it matches you:**  
- Blender's **Video Sequence Editor (VSE)** is a non-linear video editor written in C++ — combining your C++ skills with your video processing interest (`time_video_calc.sh`, mpv).  
- Blender has extensive Python scripting for automation; your ZYTgui Python GUI experience transfers directly.  
- GSoC 2024 projects included VSE improvements, codec integrations, and Python API enhancements — all aligned with your interests.  
- Blender uses DEFLATE for its `.blend` file format (zlib-compressed), so your malmom knowledge is directly applicable.

**Newcomer path:**
- Contributing guide: https://developer.blender.org/docs/handbook/contributing/  
- Good first issues: https://projects.blender.org/blender/blender/issues?type=bug&label=&milestone=0&project=0&assignees=&poster=&q=good+first+issue  
- GSoC project ideas: https://developer.blender.org/docs/handbook/contributing/gsoc/

**Difficulty:** Medium  
**Stack:** C, C++, Python

---

#### 9. LLVM · [github.com/llvm/llvm-project](https://github.com/llvm/llvm-project)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/llvm-compiler-infrastructure  
**Project ideas:** https://llvm.org/OpenProjects.html

**Why it matches you:**  
- LLVM is the industry-standard C++ compiler infrastructure — writing C++ to improve C++ tooling is the most direct match for your malmom work.  
- LLVM uses bitstream encoding (a form of variable-length integer packing), conceptually related to your `bit_io.cpp` in malmom.  
- **Clang** (LLVM's C++ compiler front end) is used to build projects like malmom and mpv; you already implicitly depend on it.  
- GSoC 2024 ideas included new diagnostic improvements, static analysis, and LLVM IR transformations — well-suited for a systems programmer.

**Newcomer path:**
- Contributing guide: https://llvm.org/docs/Contributing.html  
- Good first issues: https://github.com/llvm/llvm-project/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- GSoC project ideas: https://llvm.org/OpenProjects.html

**Difficulty:** Hard  
**Stack:** C++

---

#### 10. Python Software Foundation · [github.com/python](https://github.com/python)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/python-software-foundation  
**Project ideas:** https://python-gsoc.org/

**Why it matches you:**  
- Python is your secondary language: Z-youtube-downloader, ZYTgui, and PRODIGY_SD_04 are all Python projects in your profile.  
- The PSF sponsors GSoC work on **CPython** itself, as well as sub-orgs like **PyPy**, **SymPy** (matches competitive programming), and **pip**.  
- `zlib` is part of CPython's standard library (`import zlib`) — your DEFLATE knowledge from malmom gives you a unique edge on compression-related CPython improvements.  
- Python's `compileall`, `zipfile`, and `tarfile` modules all touch the compression domain you know deeply.

**Newcomer path:**
- Contributing guide: https://devguide.python.org/  
- Good first issues: https://github.com/python/cpython/issues?q=is%3Aopen+label%3A%22easy%22  
- GSoC project ideas: https://python-gsoc.org/

**Difficulty:** Medium  
**Stack:** Python, C

---

#### 11. OpenCV · [github.com/opencv/opencv](https://github.com/opencv/opencv)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/opencv  
**Project ideas:** https://github.com/opencv/opencv/wiki/GSoC_2024

**Why it matches you:**  
- OpenCV is the world's most widely used computer vision library, written in C++ with Python bindings — both your primary and secondary languages.  
- Video processing is a core OpenCV use case: reading video frames, applying filters, and writing output maps directly to your `time_video_calc.sh` and video interest areas.  
- OpenCV uses DEFLATE-compressed PNG I/O internally (through `libpng`/`zlib`), linking it to your malmom compression work.  
- GSoC 2024 projects included video codec integrations, SIMD optimizations, and deep learning improvements.

**Newcomer path:**
- Contributing guide: https://github.com/opencv/opencv/wiki/How_to_contribute  
- Good first issues: https://github.com/opencv/opencv/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
- GSoC project ideas: https://github.com/opencv/opencv/wiki/GSoC_2024

**Difficulty:** Medium  
**Stack:** C++, Python

---

#### 12. GNU Project · [gnu.org](https://www.gnu.org)

**GSoC page:** https://summerofcode.withgoogle.com/programs/2024/organizations/gnu-project  
**Project ideas:** https://www.gnu.org/software/soc-projects/ideas.html

**Why it matches you:**  
- The GNU Project includes **gzip** (DEFLATE) and **bzip2** (Burrows–Wheeler + Huffman) — compression tools directly in your domain from malmom.  
- **GNU Octave** (scientific computing) and **GNU Radio** (signal processing) are relevant to your algorithms background from competitive programming.  
- **GNU Bash** and **GNU coreutils** are what power your DOTs shell scripts (`yth.sh`, `ytm.sh`, `time_video_calc.sh`).  
- GSoC 2024 GNU ideas included gzip improvements, Octave toolboxes, and coreutils optimizations.

**Newcomer path:**
- Contributing guide: https://www.gnu.org/help/  
- gzip issues: https://savannah.gnu.org/bugs/?group=gzip  
- GSoC project ideas: https://www.gnu.org/software/soc-projects/ideas.html

**Difficulty:** Medium  
**Stack:** C, C++, Bash

---

## C) Issue Label Search for Each Organization

| Organization | `good first issue` | `help wanted` | GSoC Ideas List |
|---|---|---|---|
| FFmpeg | [trac easy](https://trac.ffmpeg.org/query?status=open&difficulty=easy) | N/A | [GSoC ideas](https://trac.ffmpeg.org/wiki/SponsoringPrograms/GSoC) |
| VideoLAN (VLC) | [Newcomers](https://code.videolan.org/videolan/vlc/-/issues?label_name%5B%5D=Newcomers) | N/A | [SoC ideas](https://wiki.videolan.org/SoC_2024/) |
| CCExtractor | [link](https://github.com/CCExtractor/ccextractor/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/CCExtractor/ccextractor/issues?q=is%3Aopen+label%3A%22help+wanted%22) | [GSoC ideas](https://github.com/CCExtractor/ccextractor/wiki/Google-Summer-of-Code-2024) |
| KDE | [junior-jobs](https://bugs.kde.org/buglist.cgi?keywords=junior-jobs) | N/A | [GSoC ideas](https://community.kde.org/GSoC/2024/Ideas) |
| GNOME | [Newcomers](https://gitlab.gnome.org/groups/GNOME/-/issues?label_name%5B%5D=4.+Newcomers) | N/A | [GSoC ideas](https://wiki.gnome.org/Outreach/SummerOfCode/2024/Ideas) |
| Xiph.org | [FLAC issues](https://github.com/xiph/flac/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [Opus issues](https://github.com/xiph/opus/issues) | [GSoC ideas](https://wiki.xiph.org/Google_Summer_of_Code) |
| mpv | [link](https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/mpv-player/mpv/issues?q=is%3Aopen+label%3A%22help+wanted%22) | [VideoLAN GSoC](https://wiki.videolan.org/SoC_2024/) |
| Blender Foundation | [link](https://projects.blender.org/blender/blender/issues?q=good+first+issue) | N/A | [GSoC ideas](https://developer.blender.org/docs/handbook/contributing/gsoc/) |
| LLVM | [link](https://github.com/llvm/llvm-project/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/llvm/llvm-project/issues?q=is%3Aopen+label%3A%22help+wanted%22) | [open projects](https://llvm.org/OpenProjects.html) |
| Python Software Foundation | [link](https://github.com/python/cpython/issues?q=is%3Aopen+label%3Aeasy) | N/A | [python-gsoc.org](https://python-gsoc.org/) |
| OpenCV | [link](https://github.com/opencv/opencv/issues?q=is%3Aopen+label%3A%22good+first+issue%22) | [link](https://github.com/opencv/opencv/issues?q=is%3Aopen+label%3A%22help+wanted%22) | [GSoC ideas](https://github.com/opencv/opencv/wiki/GSoC_2024) |
| GNU Project | [gzip bugs](https://savannah.gnu.org/bugs/?group=gzip) | N/A | [GSoC ideas](https://www.gnu.org/software/soc-projects/ideas.html) |

---

## D) Focused Opportunities

### Compression-Related Opportunities (GSoC orgs only)

| Project | Opportunity | Evidence from your profile | Link |
|---------|-------------|---------------------------|------|
| **FFmpeg** | Add or improve a lossless codec; DEFLATE/zlib wrapper improvements; test coverage | malmom implements DEFLATE (RFC 1951) in C++ from scratch — you know the spec cold | https://trac.ffmpeg.org/wiki/SponsoringPrograms/GSoC |
| **Xiph.org / FLAC** | FLAC encoder optimizations, new compression levels, test vectors | malmom's Huffman coder is the same principle as FLAC's Rice coding; C experience matches | https://github.com/xiph/flac/issues |
| **Xiph.org / Opus** | Opus encoder tuning, documentation, Python binding improvements | Opus is used by mpv (your player); LZ-style pattern reuse is shared conceptually | https://github.com/xiph/opus/issues |
| **VideoLAN (VLC)** | Codec module for a new compression format; existing codec bug fixes | VLC handles the same file types your mpv config handles | https://wiki.videolan.org/SoC_2024/ |
| **GNU Project / gzip** | DEFLATE performance patches, test coverage, documentation improvements | gzip is the reference DEFLATE implementation — malmom implements the same RFC 1951 spec | https://savannah.gnu.org/bugs/?group=gzip |
| **Python PSF / zlib module** | CPython `zlib` module improvements, edge case fixes in `zipfile`/`tarfile` | `import zlib` in Python is the same compression algorithm you built in malmom | https://github.com/python/cpython/issues?q=is%3Aopen+label%3Aeasy |
| **Blender Foundation** | `.blend` file zlib decompression improvements; VSE codec integration | Blender uses DEFLATE internally; malmom is direct background | https://developer.blender.org/docs/handbook/contributing/gsoc/ |

### Subtitle-Related Opportunities (GSoC orgs only)

| Project | Opportunity | Evidence from your profile | Link |
|---------|-------------|---------------------------|------|
| **CCExtractor** | New subtitle format support (SRT/ASS/WebVTT), OCR improvements, Python tooling | You use subtitle flags with yt-dlp daily; mpv (your player) relies on subtitle extraction | https://github.com/CCExtractor/ccextractor/issues?q=is%3Aopen+label%3A%22good+first+issue%22 |
| **FFmpeg** | Subtitle demuxer fixes, ASS/SSA filter improvements | FFmpeg is the subtitle processing engine behind mpv; your C knowledge applies | https://trac.ffmpeg.org/query?status=open&difficulty=easy |
| **VideoLAN (VLC)** | Subtitle renderer improvements, new subtitle format support | VLC subtitle support is among the most comprehensive; C++ option | https://code.videolan.org/videolan/vlc/-/issues?label_name%5B%5D=Newcomers |
| **KDE / Kdenlive** | Subtitle track editor in Kdenlive's C++ timeline | C++ matches malmom; Kdenlive has active subtitle editing development | https://bugs.kde.org/buglist.cgi?keywords=junior-jobs |

### Video Processing Opportunities (GSoC orgs only)

| Project | Opportunity | Evidence from your profile | Link |
|---------|-------------|---------------------------|------|
| **OpenCV** | Video I/O improvements, Python binding fixes, SIMD optimizations | Video processing interest evident from `time_video_calc.sh`; C++ primary language | https://github.com/opencv/opencv/issues?q=is%3Aopen+label%3A%22good+first+issue%22 |
| **Blender / VSE** | Video Sequence Editor: new effect, performance fix, or export format | `time_video_calc.sh` and mpv show hands-on video editing interest; C++ + Python | https://projects.blender.org/blender/blender/issues |
| **GNOME / Pitivi** | New transition, export preset, or GStreamer pipeline fix | Python skills apply; Pitivi + GStreamer covers your video + Python interests | https://gitlab.gnome.org/GNOME/pitivi/-/issues |

### Systems / Algorithms Opportunities (GSoC orgs only)

| Project | Opportunity | Evidence from your profile | Link |
|---------|-------------|---------------------------|------|
| **LLVM / Clang** | New compiler diagnostic, static analysis rule, or IR optimization | malmom's bit-manipulation and algorithm work is exactly what LLVM works on | https://github.com/llvm/llvm-project/issues?q=is%3Aopen+label%3A%22good+first+issue%22 |
| **GNU Project** | Bash improvements, coreutils efficiency, or Octave numerical toolbox | Your DOTs shell scripts (zsh/bash) show daily system scripting; Octave fits CP interest | https://www.gnu.org/software/soc-projects/ideas.html |

---

## E) 3 Concrete "First PR" Suggestions (Start This Week)

### PR #1 — CCExtractor: Fix a subtitle format or add a small feature (C/Python · Easy)

**Repository:** https://github.com/CCExtractor/ccextractor  
**GSoC org:** https://summerofcode.withgoogle.com/programs/2024/organizations/ccextractor-development  
**Why you:** CCExtractor is the most beginner-friendly GSoC org in this list with an explicit "good first issue" label. It's written in C (which you use in malmom) with Python tooling. Its entire purpose is subtitle extraction, which is one of your focus areas. Your mpv setup depends on subtitle tools like CCExtractor.  
**What to do:**  
1. Browse good first issues: https://github.com/CCExtractor/ccextractor/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
2. Or check their GSoC micro-task list (required for applicants, but open to all): https://github.com/CCExtractor/ccextractor/wiki/Google-Summer-of-Code-2024  
3. Fix a subtitle format parsing bug or improve documentation for a subtitle format  
**Effort:** A few hours to a day. C or Python, CMake build system.  
**Direct issue link:** https://github.com/CCExtractor/ccextractor/issues?q=is%3Aopen+label%3A%22good+first+issue%22

---

### PR #2 — FFmpeg: Fix an easy trac ticket (C · Medium)

**Repository:** https://github.com/FFmpeg/FFmpeg  
**GSoC org:** https://summerofcode.withgoogle.com/programs/2024/organizations/ffmpeg  
**Why you:** malmom implements DEFLATE (LZ77 + Huffman) in C++ — the exact algorithm used by FFmpeg's zlib/PNG codec path. You already understand how bit-level I/O and entropy coding work from writing `bit_io.cpp` and `huffman.cpp`. Reading FFmpeg source will feel familiar.  
**What to do:**  
1. Find an easy trac ticket: https://trac.ffmpeg.org/query?status=open&difficulty=easy  
2. Or look for subtitle-related tickets: https://trac.ffmpeg.org/query?status=open&component=avcodec&keywords=~subtitle  
3. Follow the patch submission guide: https://ffmpeg.org/developer.html#Submitting-patches  
**Effort:** A weekend. C, Makefile-based build, `make fate` test suite.  
**Direct issue link:** https://trac.ffmpeg.org/query?status=open&difficulty=easy

---

### PR #3 — KDE / Kdenlive: Fix a junior-job C++ bug (C++ · Medium)

**Repository:** https://invent.kde.org/multimedia/kdenlive  
**GSoC org:** https://summerofcode.withgoogle.com/programs/2024/organizations/kde  
**Why you:** Kdenlive is a video editor written in C++ — your primary language from malmom. KDE's "junior-jobs" are curated, appropriately scoped bugs. Your video processing interest (`time_video_calc.sh`) and mpv usage translate directly to understanding a video editor's requirements.  
**What to do:**  
1. Browse junior jobs in Kdenlive: https://bugs.kde.org/buglist.cgi?product=kdenlive&keywords=junior-jobs&bug_status=UNCONFIRMED,NEW,ASSIGNED  
2. Set up the KDE development environment: https://community.kde.org/Get_Involved/development  
3. Fix a C++ UI bug or add a small feature to the subtitle/caption track  
**Effort:** A weekend. C++, CMake, Qt framework.  
**Direct issue link:** https://bugs.kde.org/buglist.cgi?product=kdenlive&keywords=junior-jobs&bug_status=UNCONFIRMED,NEW,ASSIGNED

### PR #4 — OpenCV: Fix a video I/O or Python binding issue (C++ · Medium)

**Repository:** https://github.com/opencv/opencv  
**GSoC org:** https://summerofcode.withgoogle.com/programs/2024/organizations/opencv  
**Why you:** OpenCV is a C++ library with Python bindings — both your primary and secondary stacks. Your `time_video_calc.sh` and video processing interest translate directly to understanding what OpenCV is used for. Video frame reading/writing bugs are well-scoped and accessible to a C++ newcomer.  
**What to do:**  
1. Browse good first issues: https://github.com/opencv/opencv/issues?q=is%3Aopen+label%3A%22good+first+issue%22  
2. Or look at Python binding issues: https://github.com/opencv/opencv/issues?q=is%3Aopen+label%3Apython  
3. Set up the build: https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html  
**Effort:** A weekend. CMake build system, C++ and Python.  
**Direct issue link:** https://github.com/opencv/opencv/issues?q=is%3Aopen+label%3A%22good+first+issue%22

---

### PR #5 — Blender: Fix a VSE (Video Sequence Editor) bug (C++ / Python · Medium)

**Repository:** https://projects.blender.org/blender/blender  
**GSoC org:** https://summerofcode.withgoogle.com/programs/2024/organizations/blender-foundation  
**Why you:** Blender's Video Sequence Editor is a non-linear video editor in C++ — hitting your video processing interest alongside your strongest language. Blender also has a rich Python scripting layer (bpy), matching your Python skills from Z-youtube-downloader and ZYTgui. Blender uses zlib/DEFLATE for `.blend` files, so your malmom background gives unique context.  
**What to do:**  
1. Browse Blender's issue tracker for VSE bugs: https://projects.blender.org/blender/blender/issues?type=bug&q=VSE  
2. Or look for Python API documentation issues (easy entry point): https://projects.blender.org/blender/blender/issues?q=python+api  
3. Follow the developer docs: https://developer.blender.org/docs/handbook/contributing/  
**Effort:** A weekend. CMake + Ninja build, C++ or Python.  
**Direct issue link:** https://projects.blender.org/blender/blender/issues

---

## Quick Reference: URLs

| Resource | URL |
|----------|-----|
| Your GitHub profile | https://github.com/zeyad-elkholy |
| malmom (compression) | https://github.com/zeyad-elkholy/malmom |
| DOTs (configs+scripts) | https://github.com/zeyad-elkholy/DOTs |
| Z-youtube-downloader | https://github.com/zeyad-elkholy/Z-youtube-downloader |
| GSoC org directory 2024 | https://summerofcode.withgoogle.com/programs/2024/organizations |
| **FFmpeg** | https://github.com/FFmpeg/FFmpeg |
| **VideoLAN (VLC)** | https://code.videolan.org/videolan/vlc |
| **CCExtractor** | https://github.com/CCExtractor/ccextractor |
| **KDE (Kdenlive)** | https://invent.kde.org/multimedia/kdenlive |
| **GNOME (Pitivi)** | https://gitlab.gnome.org/GNOME/pitivi |
| **Xiph.org (FLAC)** | https://github.com/xiph/flac |
| **Xiph.org (Opus)** | https://github.com/xiph/opus |
| **mpv** | https://github.com/mpv-player/mpv |
| **Blender Foundation** | https://projects.blender.org/blender/blender |
| **LLVM** | https://github.com/llvm/llvm-project |
| **Python Software Foundation** | https://github.com/python/cpython |
| **OpenCV** | https://github.com/opencv/opencv |
| **GNU Project** | https://www.gnu.org/software/software.html |
