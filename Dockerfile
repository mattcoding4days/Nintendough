# using ubuntu base image
FROM ubuntu:22.04

# Use default  answers for all questions.
ENV DEBIAN_FRONTEND noninteractive

# Upgrade the system
RUN apt-get update && apt-get upgrade -y --allow-downgrades

# install basics
RUN apt-get -y install lsb-release wget software-properties-common

# Install generlized tooling
RUN apt-get -y install cmake build-essential python3-pip checkinstall vim git

# Install LLVM (clang toolchain) and formatters
RUN apt-get -y install clang clang-format clang-tidy cmake-format

# Install with pip
RUN pip install  distro

# Copy the files to the image
COPY cmake/ /nintendough/cmake
COPY app/ /nintendough/app
COPY CMakeLists.txt /nintendough/CMakeLists.txt

# copy clang config files
COPY .clang-format /nintendough
COPY .clang-tidy /nintendough
COPY .cmake-format.yaml /nintendough

# Copy the python devkit tooling
COPY devkit /nintendough/devkit
COPY tooling /nintendough/tooling

WORKDIR /nintendough

# format the project
RUN ./devkit clang --format

# Build Entire project with tests and examples on
RUN ./devkit compile --clang

# Statically analyze the project
RUN ./devkit clang --lint

# Run tests. If you did not build a project,
# make sure to comment out the tests for that project
RUN cd build/app && ctest -VV
RUN ./build/app/src/nintendough
