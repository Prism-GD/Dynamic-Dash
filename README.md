# Dynamic Dash

An original rhythm-platformer project built with C++ and Cocos2d, targeting Android.

> The game interface and in-game text will be in English. Development notes may be written in Portuguese.

## Project goals
- Original platforming gameplay and level design
- Cocos2d-based rendering and game loop
- Native C++ game systems
- Local player save system
- Android support, initially tested on Samsung Galaxy A04s
- Automated builds and downloadable artifacts through GitHub Actions

## Repository layout
- `src/` — C++ game and gameplay systems
- `include/` — public C++ headers
- `assets/` — original images, audio, fonts and other game assets
- `cocos2d/` — pinned Cocos2d engine dependency (to be added)
- `android/` — Android application and platform integration
- `tests/` — automated tests
- `scripts/` — developer and build scripts
- `.github/workflows/` — CI and build workflows
- `docs/` — technical documentation
- `builds/` — build metadata; generated binaries belong in Actions artifacts or Releases, not Git history

## Build status
The initial workflow cross-compiles the native C++ core for Android `arm64-v8a` and uploads the shared library as a workflow artifact. This is **not yet an installable APK**. Android app packaging and Cocos2d integration are subsequent milestones.

## Development
The repository is the source of truth. Use `development` for ongoing work and merge tested changes into `main`.

## License
See [LICENSE](LICENSE). Third-party engine code and assets retain their own licenses.
