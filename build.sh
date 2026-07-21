#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
DEFAULT_INPUT="$ROOT_DIR/tests/test.ll"
INPUT="$1"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -G Ninja "$ROOT_DIR"

ninja MyPass

if [[ -n "$INPUT" ]]; then
  if [[ "$INPUT" = /* ]]; then
    INPUT_FILE="$INPUT"
  else
    INPUT_FILE="$ROOT_DIR/$INPUT"
  fi

  if [[ ! -f "$INPUT_FILE" ]]; then
    echo "Input file not found: $INPUT" >&2
    exit 1
  fi

  INPUT_BASENAME="$(basename "$INPUT_FILE")"
  INPUT_NAME="${INPUT_BASENAME%.*}"
  OUTPUT_LL="$BUILD_DIR/${INPUT_NAME}.ll"

  clang -O0 -Xclang -disable-O0-optnone -emit-llvm -S "$INPUT_FILE" -o "$OUTPUT_LL"

  /opt/homebrew/Cellar/llvm/22.1.8/bin/opt \
    -load-pass-plugin "$BUILD_DIR/MyPass.dylib" \
    -passes='MyPass' \
    "$OUTPUT_LL" \
    -S -o "$BUILD_DIR/${INPUT_NAME}_out.ll"
  else
    /opt/homebrew/Cellar/llvm/22.1.8/bin/opt \
      -load-pass-plugin "$BUILD_DIR/MyPass.dylib" \
      -passes='MyPass' \
      "$DEFAULT_INPUT" \
      -S -o "$BUILD_DIR/output.ll"
fi
