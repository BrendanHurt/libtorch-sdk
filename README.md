# libtorch-sdk

Currently the project performs two epochs of linear regression training on a network. Then, it sends the weights of that network to the server using gRPC. Once the server receives these weights it loads them into its own network.

Next step: Get the server to run its own iterations with the model and send the weights back to the client.



For building and running:
1. mkdir build
2. cd build   
3. cmake -DCMAKE_PREFIX_PATH="path/to/libtorch" ..
4. make
5. Run the server using ./server
6. Run the client using ./client
"path/to/libtorch" being the path to TorchConfig.cmake, i.e. "home/username/libtorch/share/cmake/Torch"


Packages:

gRPC: 
Instructions for performing local installation of gRPC from the gRPC documentation: https://grpc.io/docs/languages/cpp/quickstart/

1. Export the installation path for the local installation of gRPC
    export MY_INSTALL_DIR=$HOME/.local
    export PATH="$MY_INSTALL_DIR/bin:$PATH"
    
    (Optional) Ensure the path exists:
    mkdir -p $MY_INSTALL_DIR
    
2. Install cmake (if cmake isn't already isntalled)
    sudo apt install -y cmake

3. Install other required tools
    sudo apt install -y build-essential autoconf libtool pkg-config

4. Clone the grpc repo
    git clone --recurse-submodules -b v1.41.0 https://github.com/grpc/grpc

5. Build and install gRPC and Protobuf
    cd grpc
    mkdir -p cmake/build
    pushd cmake/build
    cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
          ../..
    make -j
    make install
    popd



Protobuf: 
Version: 3.15.8
Installation steps from the protobuf documentation: https://github.com/protocolbuffers/protobuf/blob/master/src/README.md

1. Download and extract the zip or tar file
zip link:
    wget https://github.com/protocolbuffers/protobuf/releases/download/v3.15.8/protobuf-all-3.15.8.zip

tar link:
    wget https://github.com/protocolbuffers/protobuf/releases/download/v3.15.8/protobuf-all-3.15.8.tar.gz

2. cd into the directory
    cd protobuf-all-3.15.8
3. Configure and build the protobuf installation
    ./configure --prefix=/usr
    make
    make check
    sudo make install
    sudo ldconfig


libtorch: 1.9.0
https://pytorch.org/get-started/locally/

Note: When installing on Linux, ensure that the version of libtorch is using the cxx11 ABI. Otherwise it will cause compatability issues with Protobuf.
