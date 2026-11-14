# Development roadmap

## Milestone 1 — Repository and native build
- [x] Create central repository
- [x] Add C++ native-core skeleton
- [x] Add Android arm64-v8a CI workflow
- [ ] Verify first GitHub Actions run

## Milestone 2 — Engine and Android app
- [ ] Pin a compatible Cocos2d release/commit and document its license
- [ ] Add Android application project and packaging
- [ ] Launch a basic Cocos2d scene on Samsung Galaxy A04s
- [ ] Produce installable debug APK artifacts

## Milestone 3 — First playable prototype
- [x] Define main-menu to level-selection navigation
- [x] Add one selectable sample level (`First Steps`)
- [x] Add automated tests for the prototype flow
- [ ] Render the main menu and level-selection screen in Cocos2d
- [ ] Implement playable player movement and the first level

## Milestone 4 — Gameplay
- [ ] Player movement and physics
- [ ] Collision and hazards
- [ ] Level system and checkpoints
- [ ] Audio timing and effects

## Milestone 5 — Player data
- [ ] Versioned local save format
- [ ] Progress, best scores, coins, icons and settings
- [ ] Save migration and corruption recovery

## Milestone 6 — Official mod launcher integration
- [ ] Define the game-to-launcher integration interface
- [ ] Define and version the public mod API and package format
- [ ] Make the game discover mods installed by the companion launcher
- [ ] Support optional added levels, visuals, music and gameplay extensions
- [ ] Publish mod development documentation and example mods

## Milestone 7 — Editor and releases
- [ ] Level editor
- [ ] Automated tests
- [ ] Versioned APK releases
