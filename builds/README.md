# Build outputs

Generated APKs, AABs and native binaries are not committed to Git history.

## Where users can test builds
- **Development builds:** GitHub Actions artifacts, attached to individual workflow runs.
- **Public milestone versions:** GitHub Releases, marked as pre-releases until the game is stable.
- Published preview versions should remain available so users can test older builds and compare changes.

## Version labels
- `0.x.y-alpha.N` — early, incomplete builds; features may be missing or change.
- `0.x.y-beta.N` — broader testing builds; still may contain bugs.
- A GitHub Release must be marked as a pre-release until the project is ready for a stable release.

Every public build should include release notes, known issues, supported Android architecture/minimum version, and a checksum. Never label a native `.so` artifact as an installable APK.

This directory is reserved for build metadata, checksums and release notes.
