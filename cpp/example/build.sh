mkdir -p build
cd build
cmake .. -DGGML_NUMA=OFF

echo "Building the project..."
make

ln -sf ../../../cpp/ggml-llama.metallib default.metallib
