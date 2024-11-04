# Use Ubuntu as base image
FROM ubuntu:22.04

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages including Python 3.10
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    software-properties-common \
    curl \
    freeglut3-dev \
    libgl1-mesa-dev \
    git \
    && add-apt-repository ppa:deadsnakes/ppa \
    && apt-get update \
    && apt-get install -y \
    python3.10 \
    python3.10-dev \
    python3.10-distutils \
    && rm -rf /var/lib/apt/lists/*

# Install pip for Python 3.10
RUN curl -sS https://bootstrap.pypa.io/get-pip.py | python3.10

# Install required Python packages
RUN python3.10 -m pip install numpy matplotlib

# Create symlinks for python3 and python
RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.10 1 \
    && update-alternatives --install /usr/bin/python python /usr/bin/python3.10 1

# Set working directory
WORKDIR /app

# Copy the source code
COPY . .

# Create build directory and build the project
RUN mkdir -p build
WORKDIR /app/build

# Create script to build the project
RUN echo '#!/bin/bash\n\
    cmake .. && \
    make -j$(nproc) && \
    echo "Build completed. Check the build directory for the executable."' > /build.sh

RUN chmod +x /build.sh

# Set the entrypoint to our build script
ENTRYPOINT ["/build.sh"]