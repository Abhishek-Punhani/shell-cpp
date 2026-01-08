# Custom Shell in C++

[![C++](https://img.shields.io/badge/language-C%2B%2B-orange)](https://isocpp.org)
[![CMake](https://img.shields.io/badge/build-CMake-blue)](https://cmake.org)
[![vcpkg](https://img.shields.io/badge/package%20manager-vcpkg-green)](https://vcpkg.io)
[![Linux](https://img.shields.io/badge/platform-Linux-lightgrey)](https://www.linux.org/)

A POSIX-compliant interactive shell implemented in C++ that supports command parsing, builtin commands, external executables, pipelines, I/O redirection, tab completion, and history navigation.

## Features

- **REPL (Read-Eval-Print Loop):** Interactive command execution
- **Command Parsing:** Handles single/double quotes and backslash escapes
- **Builtin Commands:** echo, type, pwd, cd, history, and more
- **External Program Execution:** Launches programs with correct argv and environment
- **I/O Redirection:** Supports stdout/stderr redirection (>, >>, 2>, 2>>)
- **Pipelines:** Command chaining with pipes
- **Tab Completion:** Autocomplete for builtins and executables using GNU Readline
- **History Navigation:** Up/down arrow navigation with persistent history

## Getting Started

### Prerequisites

- CMake (version 3.10 or higher)
- C++ compiler (g++ or clang++)
- vcpkg for dependency management
- GNU Readline library

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Abhishek-Punhani/shell-cpp.git
   cd shell-cpp
   ```

2. Install dependencies using vcpkg:

   ```bash
   vcpkg install
   ```

3. Build the project:
   ```bash
   make build
   ```

### Usage

Build and run the interactive shell:

- Using Makefile:

  ```bash
  make build
  make run
  ```

- Directly:

  ```bash
  make build
  ./start.sh
  ```

- Using Docker Compose:
  ```bash
  make docker-up
  ```

## Development

### Building

Use the provided Makefile for easy building:

```bash
make build      # Configure and build
make clean      # Clean build artifacts
make run        # Build and run the shell
```

### Manual Build

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

## Examples

```bash
$ echo "Hello, World!"
Hello, World!

$ ls -la | grep "\.cpp$"
commands.cpp
main.cpp

$ cat file.txt > output.txt
$ history
1 echo "Hello"
2 ls
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. Keep changes focused and well-documented.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

Built with modern C++ and POSIX system calls for educational purposes.
