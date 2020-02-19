# Getting base image UBUNTU
FROM ubuntu:18.04

MAINTAINER Julian Angeles <jtangeles@ucdavis.edu>

# Install dependencies
RUN apt-get update -y

RUN \
  apt-get install git vim build-essential zlib1g zlib1g-dev cmake openssl libssl-dev -y

# Setup necessary files
WORKDIR /NuRaft
ADD src/ src/
ADD cmake/ cmake/
ADD tests/ tests/
ADD include/ include/
ADD scripts/ scripts/
ADD examples/ examples/
ADD manifest.sh .
ADD prepare.sh .
ADD CMakeLists.txt .

# Additional preparation
RUN \
  ./prepare.sh

# Compile code
WORKDIR /NuRaft/build

RUN cmake ../

RUN make

# Start from root folder
WORKDIR /NuRaft
