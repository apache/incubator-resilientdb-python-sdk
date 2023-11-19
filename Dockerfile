FROM ubuntu:20.04

# Prevents prompts and dialogues during package installation
ENV DEBIAN_FRONTEND=noninteractive 

# Setup the deadsnakes PPA and other basic dependencies
RUN apt-get update && apt-get install -y \
    software-properties-common \
    apt-transport-https \
    curl \
    gnupg \
    git \
    && add-apt-repository ppa:deadsnakes/ppa \
    && apt-get update

# Install other required packages
RUN apt-get install -y \
    protobuf-compiler \
    rapidjson-dev \
    clang-format \
    build-essential \
    openjdk-11-jdk \
    zip unzip \
    python3.10 \
    python3.10-dev \
    python3-venv \
    python3-dev \
    python3-pip \
    python3-distutils

# Set python3.10 as the default python3 version
RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.10 1 && \
    python3 --version

# Install pip3 using the get-pip.py script
RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && \
    python3 get-pip.py && \
    rm get-pip.py

# Cleanup apt cache
RUN rm -rf /var/lib/apt/lists/*

# Add Bazel repository and its GPG key
RUN curl -Lo /usr/local/bin/bazel https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-arm64 \
    && chmod +x /usr/local/bin/bazel

# Set the working directory
WORKDIR /app

# Copy your project files to the container
COPY . /app

RUN pip3 install virtualenv && \
    . venv/bin/activate && \
    pip install --upgrade setuptools && \
    pip install -r requirements.txt 

RUN sh service/tools/start_kv_service_sdk.sh

# Expose port
EXPOSE 18000  

# Set healthcheck
HEALTHCHECK CMD curl -f http://localhost:18000/ || exit 1

RUN bazel build service/http_server/crow_service_main

ENTRYPOINT ["./entrypoint.sh"]