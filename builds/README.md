# Build outputs

Generated APKs, AABs and native binaries are not committed to Git history.

## Where users can test builds
- **Development builds:** GitHub Actions artifacts, attached to individual workflow runs.
- **Public milestone versions:** GitHub Releases, marked as pre-releases until the game is stable.
- Published preview versions should remain available so users can test older builds and compare changes.

## Version labels
- `1.0.0-alpha.N` — early, incomplete previews of the 1.0 release line.
- `1.0.0-beta.N` — broader testing previews of the 1.0 release line.
- `1.0.0` — stable 1.0 release.
- Every alpha/beta GitHub Release must be marked as a pre-release.

Every public build should include release notes, known issues, supported Android architecture/minimum version, and a checksum. Never label a native `.so` artifact as an installable APK.

This directory is reserved for build metadata, checksums and release notes.
