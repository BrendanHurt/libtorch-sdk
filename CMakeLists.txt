cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(modelSend C CXX)
#set(CMAKE_PREFIX_PATH "/home/adduser/libtorch/share/cmake/Torch")

#find the packagaes & link the proto directory
find_package(Threads REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Torch REQUIRED)

#--------------------
#protobuf
message("Protobuf version: ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
find_program(_PROTOBUF_PROTOC protoc)
message("Protoc location: ${_PROTOBUF_PROTOC}")

#--------------------
#grpc
set(_REFLECTION gRPC::grpc++_reflection)
message("gRPC version: ${gRPC_VERSION}")

#needed?
set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE /home/adduser/grpc/bin/grpc_cpp_plugin)
message("gRPC plugin location: ${_GRPC_CPP_PLUGIN_EXECUTABLE}")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

#get the proto files
set(PROTO_SRC "proto/sdk_transport.pb.cc")
set(PROTO_HDR "proto/sdk_transport.pb.h")
set(GRPC_SRC "proto/sdk_transport.grpc.pb.cc")
set(GRPC_HDR "proto/sdk_transport.grpc.pb.h")

add_library(protoModule
    ${GRPC_SRC}
    ${GRPC_HDR}
    ${PROTO_SRC}
    ${PROTO_HDR}
)
target_link_libraries(protoModule
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    ${TORCH_LIBRARIES}
)

#make the executables
add_executable(client client.cc testModel.cc ${GRPC_SRC} ${PROTO_SRC})
target_link_libraries(client protoModule)
add_executable(server server.cc ${GRPC_SRC} ${PROTO_SRC})
target_link_libraries(server protoModule)

#protoc -I. --grpc_out=. --plugin=protoc-gen-grpc=/home/adduser/grpc/bin/grpc_cpp_plugin sdk_transport.proto
#protoc -I. --cpp_out=. sdk_transport.proto

#grpc 1.32
#client side version > 1.27
#grpcio > 1.27
#grpcio-tools 1.32