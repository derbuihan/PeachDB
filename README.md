# PeachDB

PeachDB is a simple database management system that is written in C.

## Requirements

- Bison (version 3)
- Flex
- CMake

## Installation

For macOS, install the following packages using Homebrew

```bash
$ brew install bison flex cmake gcc make
```

Write the following lines in your `.zshrc` file

```bash
export PATH="/opt/homebrew/Cellar/bison/3.8.2/bin:$PATH"
export PATH="/opt/homebrew/Cellar/flex/2.6.4_2/bin:$PATH"
```

## Build

```bash
$ mkdir cmake-build-debug
$ cd cmake-build-debug
$ cmake ..
$ make
```

## Usage

```bash
$ ./PeachDB "select id, name from table;"
```

OR

```bash
$ echo "select id, name from table;" | ./PeachDB
```
