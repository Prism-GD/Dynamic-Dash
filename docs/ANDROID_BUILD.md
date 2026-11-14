# Android build — Cocos2d-x v4

Dynamic Dash uses the upstream Cocos2d-x **v4** release. The engine is fetched into the ignored `cocos2d/` directory and is not copied into this repository; its upstream MIT license and notices remain with that dependency.

Run `bash scripts/setup-cocos2d.sh` to clone the v4 tag, initialize submodules and download external dependencies. Open `android/` in Android Studio and install SDK 35, CMake 3.22.1 and NDK 21.4.7075529. Build the `app` debug variant. The first build downloads and compiles the engine.

Target: Android API 23+, `arm64-v8a`, landscape.

## First playable scope
- Loading scene, main menu and separate level-selection screen.
- One original level: **First Steps**.
- Tap to jump, avoid pink hazards and reach 100%.
- Retry after a crash/completion, or return to level selection.

This is an early alpha. Audio sync, editor, save system and official companion mod-launcher connection are later milestones.