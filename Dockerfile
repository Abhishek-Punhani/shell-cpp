# Use Ubuntu as base image with build tools
FROM ubuntu:22.04

# Install necessary packages
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    git \
    curl \
    unzip \
    pkg-config \
    libreadline-dev \
    zip\
    tar \
    && rm -rf /var/lib/apt/lists/*

# Install vcpkg
RUN git clone https://github.com/Microsoft/vcpkg.git /opt/vcpkg \
    && /opt/vcpkg/bootstrap-vcpkg.sh \
    && /opt/vcpkg/vcpkg integrate install

# Set environment variables for vcpkg
ENV VCPKG_ROOT=/opt/vcpkg
ENV PATH="$VCPKG_ROOT:$PATH"

# Set working directory
WORKDIR /app

ENV HOME=/app

RUN touch /app/.myshell_history && chmod 0644 /app/.myshell_history

# Copy source code
COPY . .

# Remove any existing build artifacts
RUN rm -rf build

# Build the project
RUN mkdir -p build && cd build && cmake .. && make -j$(nproc)

# Set entrypoint to run the shell
CMD ["./build/shell"]