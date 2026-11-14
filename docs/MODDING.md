# Official mod loader

Dynamic Dash is an open-source game and will include an official mod loader maintained as part of the game project.

## Goals

- Mods are installed and managed from inside the game.
- A public, versioned API lets community developers extend supported game systems.
- Mods declare their identity, version, API compatibility, dependencies and requested capabilities.
- Players can enable, disable and remove mods without reinstalling the game.
- The loader checks compatibility and explains failures instead of silently loading incompatible mods.

## Initial package design

A mod package will contain a manifest and its content/scripts. The manifest will define at least:

- unique mod identifier
- display name and version
- mod API version
- supported game-version range
- entry point
- dependencies
- requested capabilities/permissions

The exact file format and runtime will be selected when the Android/Cocos2d application layer is ready.

## Security principles

- Mods must not receive unrestricted access to player files, network access or operating-system features.
- The default mod format will use a sandboxed scripting runtime, not arbitrary native shared libraries.
- Sensitive capabilities must be explicit and user-approved.
- Invalid packages, dependency conflicts and API mismatches must be reported clearly.
- The game must remain playable with all mods disabled.

## Compatibility

The loader API will be versioned independently from the game version. Breaking API changes require a new API version and migration notes. The loader must reject or disable incompatible mods safely.

## Development status

This document defines the direction, not a completed loader. The actual loader, in-game manager and scripting runtime have not yet been implemented. See [the roadmap](ROADMAP.md) for milestones.
