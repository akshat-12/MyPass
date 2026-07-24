# LLVM Pass Example

This project builds a simple LLVM function pass plugin named `MyPass` and runs it on a sample LLVM IR file.

## Prerequisites

- A working LLVM installation (tested with LLVM 22.1.8)
- CMake
- Ninja
- A C++ compiler compatible with LLVM

Make sure the LLVM tools are available in your shell, especially `opt`.
Also make sure that opt/cmake/ninja are added to the PATH

## Run the pass on the sample testcase

To build and run the sample C++ testcase `tests/test.cpp`:

```bash
chmod +x build.sh
./build.sh tests/test.cpp
```

This will:

1. build the `MyPass` plugin
2. run Clang to generate LLVM IR from `tests/test.cpp`
3. run `opt` with the plugin on the generated `.ll` file
4. print the pass output, including function names and instruction counts