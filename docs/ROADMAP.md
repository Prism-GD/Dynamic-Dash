# Development roadmap

## Milestone 1 — Repository and native core
- [x] Create central repository and native C++ skeleton
- [x] Add Android arm64-v8a native-core workflow
- [x] Verify native-core build and prototype tests

## Milestone 2 — Cocos2d-x and Android app
- [x] Select and pin Cocos2d-x v4 upstream engine line
- [x] Add Cocos2d application entry point and Android Gradle project
- [ ] Validate Cocos2d-x Android build in CI
- [ ] Produce an installable debug APK artifact
- [ ] Install and test on Samsung Galaxy A04s

## Milestone 3 — First playable prototype
- [x] Implement loading scene and main menu in Cocos2d
- [x] Implement separate level-selection screen
- [x] Implement first playable level, tap-to-jump, hazards and progress
- [x] Add retry and return-to-level-select flows
- [ ] Validate gameplay and touch controls on a physical Android device

## Milestone 4 — First public preview: 1.0.0-alpha.1
- [ ] Package and verify installable Android APK
- [ ] Publish GitHub Release `1.0.0-alpha.1` as a pre-release
- [ ] Add release notes, known issues, device requirements and checksum
- [ ] Keep all published preview versions available

## Milestone 5 — Gameplay improvements
- [ ] Add original music and synchronized obstacles
- [ ] Improve collision/physics and add effects
- [ ] Add more levels and difficulty progression

## Milestone 6 — Player data
- [ ] Versioned local save format
- [ ] Progress, best scores, coins, icons and settings
- [ ] Save migration and corruption recovery

## Milestone 7 — Official mod launcher integration
- [ ] Define the game-to-launcher integration interface
- [ ] Define and version the public mod API and package format
- [ ] Discover optional content installed by the companion launcher
- [ ] Publish mod documentation and example mods

## Milestone 8 — Editor and ongoing releases
- [ ] Expand automated tests
- [ ] Publish `1.0.0-alpha.N` and `1.0.0-beta.N` previews during development
- [ ] Publish stable `1.0.0` when ready
