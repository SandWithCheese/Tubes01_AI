# Use Ubuntu as base image
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    python3.10 \
    python3.10-dev \
    python3-pip \
    freeglut3-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    mesa-utils \
    x11-apps \
    && rm -rf /var/lib/apt/lists/*

# Install Python dependencies
RUN pip3 install numpy matplotlib

# Create working directory
WORKDIR /app

# Copy the project files
COPY . /app/

# Build the project
RUN mkdir build && cd build && \
    cmake .. && \
    make

# Set display environment variable
ENV DISPLAY=:0

# Command to run the application
CMD ["./build/main"]