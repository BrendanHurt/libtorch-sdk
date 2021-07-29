# libtorch-sdk

For building:
1. cd build   
2. cmake -DCMAKE_PREFIX_PATH="$(python -c 'import torch.utils; print(torch.utils.cmake_prefix_path)')" ..   
    (can also uncomment the set(CMAKE_PREFIX_PATH) line to make it easier)
3. make
