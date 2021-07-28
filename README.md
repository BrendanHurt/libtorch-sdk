# libtorch-sdk

The -I and -L are set in the protoModule library because I used --prefix=/usr when configuring the protobuf install.

For running:
1. cd build   
2. cmake -DCMAKE_PREFIX_PATH="$(python -c 'import torch.utils; print(torch.utils.cmake_prefix_path)')" ..   
3. make
