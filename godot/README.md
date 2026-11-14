# Dynamic Dash — Godot prototype

A fresh Godot 4 / GDScript prototype. The previous Cocos2d-x work remains untouched on its own branch.

## Open on Android
1. Install **Godot Engine 4** (the Android editor).
2. Download this repository branch: `feature/godot-prototype`.
3. In Godot, choose **Import**, then select the `godot/project.godot` file.
4. Open the project and press **Run Project**.

## Prototype contents
- One authored level: **Neon Run**
- Cube, Ship, UFO, Ball, Wave, Robot and Spider modes
- Touch / mouse / keyboard input
- Mode portals, progress bar, death and retry, level completion
- Compatibility renderer for broader Android GPU support

This is an early playable foundation. Level geometry is intentionally hand-authored in `scripts/game.gd`, not procedurally randomized.
