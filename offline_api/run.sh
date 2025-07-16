#!/bin/bash

# Build the web server
(cd cpp/example && ./build.sh)

# Run the web server
./cpp/example/build/cactus_server gemma-2b-it-q4_k_m.gguf
