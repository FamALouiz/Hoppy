# Hoppy - OpenGL Graphics Project

A graphics project using OpenGL 2.1 and FreeGLUT.

## Prerequisites

- MinGW-w64 (g++ compiler)
- Make (for building)
- FreeGLUT (already included in `lib/` and `bin/`)
- OpenGL libraries (comes with Windows)

## Project Structure

```
Hoppy/
├── main.cpp           # Main source file
├── include/           # FreeGLUT headers
├── lib/x64/           # FreeGLUT library files
├── bin/x64/           # FreeGLUT DLL
├── build/             # Compiled object files (generated)
├── bin/               # Executable output (generated)
├── Makefile           # Build configuration
└── .vscode/           # VS Code configuration
```

## Building the Project

### Using Make (Command Line)

```bash
# Build the project
make

# Build and run
make run

# Clean build files
make clean

# Clean everything
make distclean

# Show help
make help
```

### Using VS Code

1. **Build**: Press `Ctrl+Shift+B` or use Terminal → Run Build Task
2. **Build and Run**: Press `Ctrl+Shift+T` (Run Test Task) and select "Build and Run"
3. **Clean**: Run task "Clean Build" from the command palette

## Running the Application

After building, the executable will be in the `bin/` directory:

```bash
# Run directly
./bin/Hoppy.exe

# Or using make
make run
```

## Development

### Adding New Source Files

Add your `.cpp` files to the root directory. The Makefile will automatically detect and compile them.

### Modifying Build Settings

Edit the `Makefile` to change:

- Compiler flags (`CXXFLAGS`)
- Linker flags (`LDFLAGS`)
- C++ standard (default: C++11)
- Include paths
- Library paths

## Troubleshooting

### "g++ is not recognized"

Make sure MinGW/g++ is installed and added to your PATH environment variable.

### Missing DLL errors

The Makefile automatically copies `freeglut.dll` to the output directory. If you still get errors, ensure the DLL is in the same folder as the executable.

### Compilation errors

Check that:

1. All source files compile with C++11 standard
2. FreeGLUT headers are in the `include/` directory
3. FreeGLUT library is in the `lib/x64/` directory

## License

See LICENSE file for details.
