# libtorch-sdk

Currently the project performs two epochs of linear regression training on a network. Then, it sends the weights of that network to the server using gRPC. Once the server receives these weights it loads them into its own network.

Next step: Get the server to run its own iterations with the model and send the weights back to the client.



For building and running:
1. mkdir build
2. cd build   
3. cmake -DCMAKE_PREFIX_PATH="path/to/libtorch"
4. make
5. Run the server using ./server
6. Run the client using ./client



Packages:
gRPC: 
https://grpc.io/docs/languages/cpp/quickstart/


Protobuf: 3.15.8
zip:
    wget https://github.com/protocolbuffers/protobuf/releases/download/v3.15.8/protobuf-all-3.15.8.zip

tar:
    wget https://github.com/protocolbuffers/protobuf/releases/download/v3.15.8/protobuf-all-3.15.8.tar.gz

Instructions for C++ installation:
https://github.com/protocolbuffers/protobuf/blob/master/src/README.md


libtorch: 1.9.0
https://pytorch.org/get-started/locally/

Note: When installing on Linux, ensure that the version of libtorch is using the cxx11 ABI. Otherwise it will cause compatability issues with Protobuf.