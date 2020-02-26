# Getting base image UBUNTU
FROM ubuntu:18.04

MAINTAINER Julian Angeles <jtangeles@ucdavis.edu>

# Install dependencies
RUN apt-get update -y

RUN \
  apt-get install git vim build-essential zlib1g zlib1g-dev cmake openssl libssl-dev -y

# Setup necessary files
WORKDIR /NuRaft
ADD NuRaft/src/ src/
ADD NuRaft/cmake/ cmake/
ADD NuRaft/tests/ tests/
ADD NuRaft/include/ include/
ADD NuRaft/scripts/ scripts/
ADD NuRaft/examples/ examples/
ADD NuRaft/manifest.sh .
ADD NuRaft/prepare.sh .
ADD NuRaft/CMakeLists.txt .

# Additional preparation
RUN \
  ./prepare.sh

# Compile code
WORKDIR /NuRaft/build

RUN cmake ../

RUN make

# Start from root folder
WORKDIR /NuRaft
