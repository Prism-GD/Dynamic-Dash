#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
if [ -d "$ROOT/cocos2d/.git" ]; then
 git -C "$ROOT/cocos2d" fetch --tags
else
 git clone --branch v4 --depth 1 --recurse-submodules https://github.com/cocos2d/cocos2d-x.git "$ROOT/cocos2d"
fi
git -C "$ROOT/cocos2d" submodule update --init --recursive
python3 "$ROOT/cocos2d/download-deps.py"
echo "Cocos2d-x v4 ready: $ROOT/cocos2d"