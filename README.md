# Dynamic Dash

An original rhythm-platformer project built with C++ and Cocos2d-x v4, targeting Android.

> The game interface and in-game text will be in English. Development notes may be written in Portuguese.

## Project goals
- Original platforming gameplay and level design
- Cocos2d-x v4 rendering and game loop
- Native C++ game systems
- Local player save system
- Android support, initially tested on Samsung Galaxy A04s
- Official open-source mod launcher integration
- Public preview builds through GitHub Actions and GitHub Releases

## First playable prototype
The Cocos2d-x application now has source implementations for:
- Loading scene followed by the main menu
- A separate level-selection screen with the original sample level **First Steps**
- A playable auto-running cube section: tap to jump, avoid hazards, and reach 100%
- Retry after a crash/completion and return to level selection

The Android project targets `arm64-v8a`, landscape orientation and Android API 23+. The first Cocos2d/Gradle build is being validated; do not consider an APK available until the Android workflow publishes one.

## Engine dependency
Cocos2d-x v4 is fetched from the upstream `v4` branch into the ignored `cocos2d/` folder. See [Android build instructions](docs/ANDROID_BUILD.md). The engine's upstream license and notices are retained with the fetched dependency.

## Public preview releases
Dynamic Dash is developed in the open. Users will be able to test published versions even when incomplete or experimental. The first release belongs to the **1.0 release line** and will be labeled **`1.0.0-alpha.1`** (Alpha 1 of version 1.0). Later previews use `1.0.0-alpha.2`, `1.0.0-beta.1`, etc. All alpha/beta GitHub Releases will be marked as pre-releases and include known issues.

## Build status
The existing native-core workflow builds the C++ state library and runs tests. A separate Android workflow builds the Cocos2d-x app and publishes a debug APK artifact when successful. A successful native-core build alone is not an installable game.

## Development
Use `development` for ongoing work. This Cocos2d integration is being developed on `feature/cocos2d-alpha` before merging.

## License
See [LICENSE](LICENSE). Third-party engine code and assets retain their own licenses.
