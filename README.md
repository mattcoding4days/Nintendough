<br>
<div align="center">
  <h1>Nintendough</h1>
</div>

## :information_source: About 

> A Nintedo Entertainment System emulator written in doughy, delicious modern C++

1. Built using the [Nesdev Wiki](https://www.nesdev.org/wiki/Nesdev_Wiki) as reference

2. Also refer to the [Mot 6502 Data sheet](http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf) courtesy of `archive.6502.org`
  - This contains very valuable information such as...
    * Alphabetic instruction set with Mnemonics and their Functions.
    * Detailed descriptions of all addressing modes used, incase you havn't memorized
      8 bit micro controller addressing modes from the 1970s.
    * And possibly the most important: Instruction set op code matrix.

## :building_construction: Development

1. Install [CC65 Assembler for Intel 6502 CPU's](https://www.nesdev.org/wiki/Installing_CC65#Building_CC65_on_Ubuntu_(Lin


### Compiling
> Standard cmake rules apply, the following commands should be made from the root of the project

1. `cmake -B build` Generate the make files, fetch build dependencies
2. `cmake --build build -j$(nproc)` Compile the code

### Using the `devkit` tool

1. Please see [this documentation for devkit usage](https://github.com/mattcoding4days/cmake-starter#building_construction-development)

## :computer: Docker

> This container builds the development environment for Ubuntu 22.04,
> installs the cmake project, and then runs the tests

### :keyboard: Commands

```bash
# Build the container (can be used to rebuild image after code changes)
# [e.g] docker image build -t <image-name>:<tag> .
docker image build -t nintendough:v0.1 .

# Rebuild with no cache
docker image build --no-cache -t nintendough:v0.1 .

# Run the container interactively
# [e.g] docker container run -it <image-name>:<tag>
docker container run -it nintendough:v0.1

# Run non interactively
docker container run nintendough:v0.1
```

## :package: 3rd party packages
1. [gtest](https://github.com/google/googletest)
  - Googles Unit test framework which also includes a mock library
  - Why? It compiles way faster than catch2, has a built in mocking framework, and blends nicely
    with the google benchmark library
2. [nlohmann json](https://github.com/nlohmann/json)
  - Json serializer/deserializer
3. [spdlog](https://github.com/gabime/spdlog)
  - Fast logging library
4. [SFML](https://www.sfml-dev.org/index.php)
  - A simple and fast multimedia library
  - `sudo apt install libsfml-dev`
