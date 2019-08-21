[![Build Status](https://travis-ci.org/ashumkin/network-optix-test-1-tcp-server-hash.svg?branch=master)](https://travis-ci.org/ashumkin/network-optix-test-1-tcp-server-hash)

[![Build status](https://ci.appveyor.com/api/projects/status/92r5nd8e0njj4up8?svg=true)](https://ci.appveyor.com/project/ashumkin/network-optix-test-1-tcp-server-hash)

## Description

Simple TCP server that responds with a SHA-256 hash sum for each input string received (strings are separated with the "newline" = LF (0x0A) character).

## Prerequisites

Clone repository. Update submodules.
```
   $ git clone ...
   $ git submodule update --init
```

### On Ubuntu
GCC installed.

Install Ninja and Boost library, i.e. `ninja-build` and `libboost-dev` packages.

   `# apt install ninja-build libboost-dev`

### On Windows

Microsoft Visual Studio 2017 with C++ support installed.

#### Ninja
Get Ninja x86_64 from
https://github.com/ninja-build/ninja/releases/tag/v1.9.0

Or for x86: a simple way to get Ninja x86 is to get it from Python pip modules (heh!).
Install Python 2.7. Run `pip install ninja`.

Add a path with the `ninja` executable to the PATH.

#### Boost
Download prebuilt `boost` binaries (e.g. 32 bit):
  `https://sourceforge.net/projects/boost/files/boost-binaries/1.60.0/boost_1_60_0-msvc-14.0-32.exe/download`

Run and extract to `lib/boost_1_60_0` subdirectory of the cloned repository.

You may want to do it in a batch manner:
  `boost_1_60_0-msvc-14.0-32.exe /DIR=lib/boost_1_60_0 /SILENT`

## Build and test

### On Ubuntu
```
   $ cmake -GNinja .
   $ cmake --build .
   $ ctest .
```

### On Windows
```
   > "%PROGRAMFILES%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
   > cmake -GNinja -DCMAKE_C_COMPILER=cl.exe
   > cmake --build .
   > ctest .
```

## Usage

### Run server

#### Ubuntu
```
    bin/hash_server PORT
```

#### Windows
```
    bin\hash_server.exe PORT
```

### Connect with the client

Netcat
```
    $ nc localhost PORT
```
Enter string, press ENTER. `Ctrl+C` to interrupt

Netcat + cat
```
    $ cat FILE | nc localhost PORT
```

Netcat + cat + STDIN
```
    $ cat FILE - | nc localhost PORT
```
Enter string, press ENTER. `Ctrl+C` to interrupt
