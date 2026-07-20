# LLVM Pass Example

This project builds a simple LLVM function pass plugin named `MyPass` and runs it on a sample LLVM IR file.

## Prerequisites

- A working LLVM installation (tested with LLVM 22.1.8)
- CMake
- Ninja
- A C++ compiler compatible with LLVM

Make sure the LLVM tools are available in your shell, especially `opt`.
Also make sure that opt/cmake/ninja are added to the PATH

## Build the project

From the repository root:

```bash
chmod +x build.sh
./build.sh
```

This script will:

1. create a `build/` directory
2. run CMake with Ninja
3. build the `MyPass` plugin
4. run the plugin on `tests/test.ll`

## Manual build steps

If you prefer to run the steps manually:

```bash
mkdir -p build
cd build
cmake -G Ninja ..
ninja MyPass
```

## Run the pass

Run the plugin with `opt`:

```bash
opt \
  -load-pass-plugin ./MyPass.dylib \
  -passes='MyPass' \
  ../tests/test.ll \
  -S -o output.ll
```

You should see output like function names and instruction counts printed by the pass.
