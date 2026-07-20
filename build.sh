#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
TEST_IR="$ROOT_DIR/tests/test.ll"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -G Ninja "$ROOT_DIR"

ninja MyPass

opt \
  -load-pass-plugin "$BUILD_DIR/MyPass.dylib" \
  -passes='MyPass' \
  "$TEST_IR" \
  -S -o "$BUILD_DIR/output.ll"
