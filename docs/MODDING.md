# Official mod launcher integration

Dynamic Dash will be open source. Its official mod launcher is a separate companion application connected to the game through a documented integration.

## Responsibilities

- **Dynamic Dash:** runs the game and exposes supported extension points.
- **Dynamic Dash Mod Launcher:** discovers, installs, updates and removes mods, then makes installed mods available to the game.
- Mods add optional content and features; the base game must remain playable without them.

## Integration goals

- A stable, versioned interface between the game and the official launcher.
- A documented mod package/manifest format with mod ID, name, version and compatible game/API versions.
- Clear handling of missing files, incompatible mods and failed loads.
- The launcher must not be required to start or play the unmodified base game.

## Mod scope

Mods exist to add more things to the game: for example additional levels, visual content, music, themes and supported gameplay extensions. The exact extension API will be designed alongside the game systems.

## Development status

This is the intended architecture. The companion launcher and game integration are not implemented yet. The current prototype focuses on the initial menu, a separate level-selection screen and one sample level.
