# Good-first-issue scouting report (updated 2026-03-23)

Search start URL used:
https://github.com/search?q=org%3Akiwix+org%3Aopenzim+org%3Aoffspot+label%3A%22good+first+issue%22+state%3Aopen&type=issues&s=updated&o=desc&p=8

Your new requirement applied:
- Checked assignees for every previously listed issue.
- Kept only issues with either:
  1) no assignee, or
  2) assignee context that still looks askable/valid (not clearly locked by an active owner).
- Added a short “how to fix” brief per kept issue.

## Filtering rule used
- **Excluded**: clearly owned issues (assignee exists and comments/metadata indicate active ownership or direct assignment).
- **Kept**: unassigned issues, plus edge cases where assignment does not clearly block asking to contribute.

## Updated list (filtered)

| Issue | Repo | Assignee status | Why kept | Small fix brief |
|---|---|---|---|---|
| https://github.com/kiwix/kiwix-tools/issues/809 | kiwix/kiwix-tools | **Unassigned** | Cleanest available candidate | Reproduce in Safari/macOS with dark theme, replace fixed-height layout with flex/100%-height chain for html/body/iframe, verify no double-scroll or footer gap regression. |
| https://github.com/kiwix/kiwix-tools/issues/775 | kiwix/kiwix-tools | **Unassigned** | No explicit owner | Update download widget template order (direct → bittorrent → magnet), add spacing before checksum, verify both desktop/mobile rendering. |
| https://github.com/openzim/mwoffliner/issues/2384 | openzim/mwoffliner | **Unassigned** | Discussed but not hard-assigned | Fetch main page metadata via API/DOM fallback, map to `LongDescription`, add tests for API-success, API-missing, and fallback paths. |
| https://github.com/kiwix/kiwix-desktop/issues/1454 | kiwix/kiwix-desktop | **Unassigned** | Fresh bug, no assignee | Reproduce first-local-file open regression on 2.5.1, trace startup/file-open flow diff vs 2.4.1, avoid full window re-init on first load. |
| https://github.com/kiwix/kiwix-desktop/issues/1450 | kiwix/kiwix-desktop | **Unassigned** | Open and free to pick | Reproduce flathub failure using linked PR context, patch packaging manifest/build metadata, run flatpak validation/build checks. |
| https://github.com/kiwix/container-images/issues/152 | kiwix/container-images | **Unassigned** | Old but still unowned | Build org-wide update script (topic/file sync task), dry-run mode first, then selective apply mode with clear target repo allowlist. |
| https://github.com/openzim/libzim/issues/786 | openzim/libzim | **Unassigned** | No assignee; can ask before coding | Add compile-time/negative-compilation style tests for operator behavior in CI-compatible form, document expected fail/pass matrix. |
| https://github.com/kiwix/kiwix-android-custom/issues/359 | kiwix/kiwix-android-custom | **Unassigned** | Documentation/content task, no owner | Update Wikivoyage offline page content structure: dedicated custom-app section, links/buttons, concise mention of language/platform coverage. |
| https://github.com/kiwix/kiwix-android/issues/4621 | kiwix/kiwix-android | **Unassigned** | Unassigned, but **needs maintainer buy-in first** | Before coding, propose UX rationale + criteria; if accepted, gate gesture hint by usage familiarity state and keep accessible fallback. |
| https://github.com/kiwix/kiwix-tools/issues/159 | kiwix/kiwix-tools | **Unassigned** | Unassigned, but broad/old | Implement practical first step: dynamic favicon propagation from iframe content when available, fallback favicon otherwise; keep patch narrow. |

## Excluded from updated list (assigned/likely owned)

These were in the previous long list but now excluded because they are currently assigned and/or clearly being handled:
- https://github.com/openzim/phet/issues/296
- https://github.com/kiwix/kiwix-android/issues/4749
- https://github.com/openzim/zim-tools/issues/473
- https://github.com/kiwix/libkiwix/issues/1166
- https://github.com/openzim/youtube/issues/439
- https://github.com/kiwix/kiwix-tools/issues/572
- https://github.com/kiwix/libkiwix/issues/1192
- https://github.com/kiwix/libkiwix/issues/1083
- https://github.com/kiwix/libkiwix/issues/976
- https://github.com/kiwix/kiwix-tools/issues/715
- https://github.com/kiwix/libkiwix/issues/922
- https://github.com/kiwix/libkiwix/issues/457
- https://github.com/kiwix/kiwix-apple/issues/1479
- https://github.com/kiwix/kiwix-android/issues/4673
- https://github.com/kiwix/kiwix-android/issues/4668
- https://github.com/openzim/nautilus-webui/issues/99
- https://github.com/openzim/libzim/issues/766
- https://github.com/kiwix/kiwix-desktop/issues/314
- https://github.com/kiwix/kiwix-build/issues/263

## Best immediate pick
- **Primary:** https://github.com/kiwix/kiwix-tools/issues/809
- **Why:** unassigned, very clear reproduction, small self-contained UI/layout fix, lowest blocker risk.

## Ask-first template (for issues with uncertain ownership)

> Hi! I’d like to work on this issue. It appears open and currently unassigned / not actively locked.  
> My plan is: [1-line technical approach].  
> If this direction looks good, I’ll open a focused PR with tests/evidence.
