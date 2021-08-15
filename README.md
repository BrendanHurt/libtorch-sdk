# libtorch-sdk

For building and running:
1. cd build   
2. cmake -DCMAKE_PREFIX_PATH="path/to/libtorch"
3. make
4. ./modelSend name_of_output_file.txt


Package versions:
Protobuf: 3.17.3
(protobuf install link)
(link to c++ installation instructions)
litbtorch: 1.6.0
(libtorch install link)

Potential issues:

Undefined symbol set_bytes (find the real name) with protobuf when calling make.
    - Ensure that the installation of libtorch has the cxx11 ABI
        Installing torch via conda has a pre-cxx11 ABI, making it incompatible with versions of protobuf that have the