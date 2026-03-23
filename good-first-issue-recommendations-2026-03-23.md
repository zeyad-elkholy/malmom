# Good-first-issue scouting report (2026-03-23)

Search start URL used:
https://github.com/search?q=org%3Akiwix+org%3Aopenzim+org%3Aoffspot+label%3A%22good+first+issue%22+state%3Aopen&type=issues&s=updated&o=desc&p=8

I collected candidates across multiple result pages (API equivalent of pages 1–4, 91 total matches), then filtered out stale-labeled issues and reviewed comment activity.

## Assumptions / limitations
- GitHub search and issue metadata were available via MCP; public profile event timeline was not directly available, so contribution-pattern analysis is inferred from repo/PR metadata and recent visible activity.
- “Linked PR / in progress” is based on issue comments and explicit mentions of PRs or ownership intent; if no explicit signal exists, it is marked as "No clear signal".
- Complexity (S/M/L) and dependency risk (Low/Med/High) are estimates based on issue description + comment context.

## Profile analysis: `zeyad-elkholy`
- **Dominant languages:** mostly **C++** (malmom, CP, GameOfLife, PRODIGY_SD_0x, zero_cpp_course), with some Python/Lua/HTML.
- **Recent repos:** latest active repo is `malmom` (C++), plus multiple C++ learning/project repositories updated through 2025.
- **Contribution pattern:** mostly personal repos; a small number of PRs (including merged PRs), indicating practical familiarity with GitHub flow but limited volume in large multi-maintainer OSS repos.
- **Implication for issue selection:** best fit is likely **small C++/CLI/web-view bugfixes** in `kiwix-tools`, `libkiwix`, `kiwix-desktop`; avoid ambiguous “needs discussion” items and issues already clearly owned.

## 30 candidate issues (scored)

Scoring formula (0–100):
- Skill match (35%)
- Likelihood to finish by 2026-03-31 (30%)
- Clarity of acceptance criteria (15%)
- Maintainer responsiveness / recent activity (10%)
- Low dependency/blocker risk (10%)

| # | Issue URL | Repo | Title | Labels | created_at | updated_at | comments | Linked PR / in-progress signal | Complexity | Dependency risk | Score |
|---|---|---|---|---|---|---|---:|---|---|---|---:|
| 1 | https://github.com/openzim/phet/issues/296 | openzim/phet | Upgrade to node-libzim 4.1.0 | good first issue, task | 2025-12-15 | 2026-03-23 | 4 | **Yes** (maintainer asked another contributor to proceed with PR) | M | Med | 30 |
| 2 | https://github.com/kiwix/kiwix-android/issues/4727 | kiwix/kiwix-android | Add "Select All" option to Bookmarks and History selection toolbar | question, good first issue | 2026-02-27 | 2026-03-23 | 8 | **Yes** (active discussion + proposal; migration dependency) | M | High | 28 |
| 3 | https://github.com/kiwix/kiwix-tools/issues/775 | kiwix/kiwix-tools | Improve a bit kiwix-serve download widget UI | enhancement, good first issue | 2025-11-05 | 2026-03-23 | 8 | Interest from multiple people; no fresh linked PR | M | Med | 63 |
| 4 | https://github.com/kiwix/kiwix-tools/issues/809 | kiwix/kiwix-tools | White line at bottom of content iframe due to fixed height | bug, kiwix-serve, good first issue | 2026-03-22 | 2026-03-22 | 1 | **No clear signal** (no claimant/PR yet) | **S** | **Low** | **86** |
| 5 | https://github.com/kiwix/kiwix-android/issues/4749 | kiwix/kiwix-android | Improve look & feel of the TOC | enhancement, good first issue, UI | 2026-03-06 | 2026-03-22 | 10 | **Yes** (ongoing mockup/prototype discussion) | M | Med | 32 |
| 6 | https://github.com/openzim/mwoffliner/issues/2384 | openzim/mwoffliner | Use `<meta name="description">` to fill ZIM `LongDescription` | enhancement, question, good first issue | 2025-06-24 | 2026-03-20 | 7 | **Yes** (contributor shared implementation direction/tests) | M | Med | 34 |
| 7 | https://github.com/openzim/zim-tools/issues/473 | openzim/zim-tools | ZIM `Counter` Metadata should be checked properly | enhancement, good first issue, zimcheck | 2025-06-30 | 2026-03-17 | 5 | **Yes** (contributor actively discussing implementation/tests) | M | Med | 57 |
| 8 | https://github.com/kiwix/libkiwix/issues/1166 | kiwix/libkiwix | external link blocker does not respect `target` | bug, good first issue, kiwix-serve | 2024-12-09 | 2026-03-11 | 16 | **Yes** (collaborator already working related fixes) | L | High | 20 |
| 9 | https://github.com/openzim/youtube/issues/439 | openzim/youtube | What is the average size of 1-minute ZIM file? | question, good first issue | 2025-12-19 | 2026-03-10 | 5 | **Yes** (comment says PR is up) | S | Low | 26 |
| 10 | https://github.com/kiwix/kiwix-tools/issues/572 | kiwix/kiwix-tools | Better explanation for "Cannot add zim" error | enhancement, good first issue | 2022-08-19 | 2026-02-24 | 16 | **Yes** (explicit PR #794 mentioned) | M | Med | 25 |
| 11 | https://github.com/kiwix/libkiwix/issues/1192 | kiwix/libkiwix | Limited number of results on homepage | bug, good first issue, kiwix-serve | 2025-05-02 | 2026-02-24 | 2 | Interest from multiple contributors; no linked PR in comments | M | Med | 78 |
| 12 | https://github.com/kiwix/libkiwix/issues/1083 | kiwix/libkiwix | Add download button in ZIM preview | enhancement, good first issue, kiwix-serve | 2024-05-14 | 2026-02-24 | 9 | **Yes** (contributor says PR raised) | M | Med | 24 |
| 13 | https://github.com/kiwix/libkiwix/issues/976 | kiwix/libkiwix | Add Kiwix logo to OPDS feed | enhancement, good first issue | 2023-07-24 | 2026-02-24 | 7 | **Yes** (discussion references almost-ready PR/testing) | M | Med | 38 |
| 14 | https://github.com/kiwix/kiwix-tools/issues/715 | kiwix/kiwix-tools | Can't copy text from kiwix-serve cards | bug, good first issue | 2024-10-21 | 2026-02-22 | 8 | **Yes** (maintainer said they will try to fix) | M | Med | 42 |
| 15 | https://github.com/kiwix/kiwix-tools/issues/159 | kiwix/kiwix-tools | kiwix-serve: favicon | enhancement, kiwix-serve, good first issue | 2018-03-04 | 2026-02-22 | 18 | Active discussion but long-lived/ambiguous scope | L | High | 35 |
| 16 | https://github.com/kiwix/libkiwix/issues/922 | kiwix/libkiwix | kiwix-serve should only use svg files (not PNG) | enhancement, good first issue, kiwix-serve | 2023-03-27 | 2026-02-22 | 3 | No clear active owner/PR in comments | M | Low | 76 |
| 17 | https://github.com/kiwix/libkiwix/issues/457 | kiwix/libkiwix | Trailing slash handling in computeRelativePath | enhancement, good first issue | 2021-03-02 | 2026-02-22 | 3 | No clear active owner/PR in recent comments | S | Low | 66 |
| 18 | https://github.com/kiwix/kiwix-desktop/issues/1454 | kiwix/kiwix-desktop | Window disappears/reappears when opening local ZIM | bug, good first issue | 2026-01-06 | 2026-02-20 | 2 | Interest comments only; no linked PR yet | M | Med | 74 |
| 19 | https://github.com/kiwix/kiwix-desktop/issues/1450 | kiwix/kiwix-desktop | Flathub publishing failed for 2.5.1 | bug, good first issue, flatpak | 2026-01-04 | 2026-02-19 | 0 | **No clear signal** | M | Med | 82 |
| 20 | https://github.com/kiwix/kiwix-apple/issues/1479 | kiwix/kiwix-apple | Switching tab is not smooth | enhancement, question, good first issue | 2026-02-14 | 2026-02-15 | 6 | **Yes** (contributor says PR opened) | M | Med | 27 |
| 21 | https://github.com/kiwix/kiwix-android/issues/4673 | kiwix/kiwix-android | Consistency theme in the Dark | question, good first issue, UI, needs discussion | 2026-02-09 | 2026-02-13 | 7 | **Yes** (collaborator already said another collaborator can take it) | M | High | 22 |
| 22 | https://github.com/kiwix/kiwix-android/issues/4668 | kiwix/kiwix-android | Storage UI text isn't aligned correctly | good first issue, UI | 2026-02-09 | 2026-02-11 | 2 | Claim/interest in comments, no linked PR | S | Low | 68 |
| 23 | https://github.com/kiwix/container-images/issues/152 | kiwix/container-images | Script to apply a change to all repos in org | enhancement, good first issue | 2020-10-23 | 2026-02-07 | 8 | New contributor asked to work; no linked PR | M | High | 40 |
| 24 | https://github.com/openzim/libzim/issues/786 | openzim/libzim | Test of base type operator ? | enhancement, good first issue, CI | 2023-04-28 | 2026-02-02 | 7 | Interest exists; maintainers warn it’s not beginner-friendly | L | High | 31 |
| 25 | https://github.com/openzim/nautilus-webui/issues/99 | openzim/nautilus-webui | Web UI assigns Description to Title, Title to Filename | bug, good first issue | 2025-03-24 | 2026-01-31 | 7 | **Yes** (contributor says mostly done, testing) | M | Med | 33 |
| 26 | https://github.com/openzim/libzim/issues/766 | openzim/libzim | Put exact title search result first | enhancement, question, good first issue, search | 2023-03-14 | 2026-01-28 | 22 | No active PR linked in latest comments; complex long thread | L | High | 36 |
| 27 | https://github.com/kiwix/kiwix-android-custom/issues/359 | kiwix/kiwix-android-custom | Advertise Wikivoyage custom apps on Wikivoyage | good first issue, advertisement | 2026-01-27 | 2026-01-27 | 5 | Active member discussion; no explicit PR link | S | Med | 49 |
| 28 | https://github.com/kiwix/kiwix-android/issues/4621 | kiwix/kiwix-android | Remove swipe gesture once user is familiar | question, good first issue, UI | 2026-01-25 | 2026-01-25 | 1 | **Blocked signal** (maintainer said rationale not convincing) | M | High | 18 |
| 29 | https://github.com/kiwix/kiwix-desktop/issues/314 | kiwix/kiwix-desktop | Prepare Windows package (*.msix) for Windows11 | enhancement, good first issue, windows | 2019-11-29 | 2026-01-23 | 35 | **Yes** (active contributor threads/work-in-progress) | L | High | 19 |
| 30 | https://github.com/kiwix/kiwix-build/issues/263 | kiwix/kiwix-build | Add flake8 check | enhancement, good first issue | 2018-10-29 | 2026-01-20 | 17 | **Yes** (contributor actively working in latest comments) | M | Med | 21 |

## Top 5 ranked issues

1. **#4** – https://github.com/kiwix/kiwix-tools/issues/809 (**86/100**)  
   Small, clear bug, fresh issue, no ownership conflict, good C++/web-view fit.

2. **#19** – https://github.com/kiwix/kiwix-desktop/issues/1450 (**82/100**)  
   Unclaimed and recent, but packaging/tooling dependency risk is moderate.

3. **#11** – https://github.com/kiwix/libkiwix/issues/1192 (**78/100**)  
   Good C++ fit; may need deeper debugging but still bounded.

4. **#16** – https://github.com/kiwix/libkiwix/issues/922 (**76/100**)  
   Technical fit and low ownership conflict; moderate scope.

5. **#18** – https://github.com/kiwix/kiwix-desktop/issues/1454 (**74/100**)  
   Relevant C++/desktop bug; some unknowns in reproducibility/root cause.

## Primary + backup recommendation

- **Primary recommendation:** https://github.com/kiwix/kiwix-tools/issues/809
  - Why: fastest path to completion by 2026-03-31, likely self-contained CSS/layout fix, minimal blocker risk, no clear active assignee.

- **Backup recommendation:** https://github.com/kiwix/kiwix-desktop/issues/1450
  - Why: still relatively fresh and unclaimed, but choose only if you can reproduce and validate Flathub pipeline steps quickly.

## Day-by-day plan (2026-03-23 → 2026-03-31)

### For primary issue (`kiwix/kiwix-tools#809`)
- **2026-03-23:** Comment to claim, confirm expected behavior with maintainer, set up env.
- **2026-03-24:** Reproduce bug on current main and isolate root cause (CSS/layout/container sizing).
- **2026-03-25:** Implement minimal fix; verify no regression in iframe/content rendering.
- **2026-03-26:** Add/update tests if available (or screenshot/manual repro steps if test harness lacks UI checks).
- **2026-03-27:** Open PR with before/after evidence; request feedback from maintainers.
- **2026-03-28:** Address review comments quickly; keep diff focused.
- **2026-03-29:** Rebase/update and final polish (docs/changelog if requested).
- **2026-03-30:** Ensure CI green; ask for final review/merge.
- **2026-03-31:** Buffer day for last fixes or fallback switch to backup issue if blocked.

## First comment draft to post on selected issue

For **https://github.com/kiwix/kiwix-tools/issues/809**:

> Hi maintainers 👋 I’d like to work on this issue.
> 
> I’ll first reproduce the white line problem on current `main`, identify whether it comes from fixed iframe/content height constraints, and then propose a minimal patch.
> 
> If there are any constraints/preferences for the fix approach (e.g., specific layout rules to preserve), please let me know before I open the PR.

## PR checklist (tailored to `kiwix/kiwix-tools`)

- [ ] Issue reproduced locally on latest `main`
- [ ] Root cause explained clearly in PR description (what caused the white line)
- [ ] Fix is minimal and scoped only to the relevant UI/layout code
- [ ] Existing tests/build pass locally (or explain if not reproducible in local env)
- [ ] Manual verification done on affected page(s) and at least one unaffected page
- [ ] Before/after screenshots or short recording attached
- [ ] No unrelated refactors in the same PR
- [ ] Commit messages are clear and focused
- [ ] PR links issue (`Fixes #809` when appropriate)
- [ ] Ready for review with concise testing notes

