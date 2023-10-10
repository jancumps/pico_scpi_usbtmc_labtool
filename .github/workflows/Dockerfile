FROM ubuntu:latest

# Install required dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    gnupg2 \
    cmake \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Import the missing public key
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 871920D1991BC93C

# Download and install gcc-arm toolchain
RUN wget -q https://developer.arm.com/-/media/Files/downloads/gnu/12.3.rel1/binrel/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz \
    && tar -xvf arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz \
    && rm arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz


# Set environment variables
ENV PATH="/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi/bin:${PATH}"

# Set the working directory
WORKDIR /armbuild

# Set a placeholder entry point 
CMD ["/bin/bash"]