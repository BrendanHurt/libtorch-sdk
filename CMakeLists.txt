cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(modelSend C CXX)
#add_subdirectory(proto)
set(CMAKE_PREFIX_PATH "/home/adduser/grpc;/home/adduser/libtorch/share/cmake/Torch")
#set(CMAKE_FIND_DEBUG_MODE 1)

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
set(PROTO_SRC "proto/sendReceiveWeights.pb.cc")
set(PROTO_HDR "proto/sendReceiveWeights.pb.h")
set(GRPC_SRC "proto/sendReceiveWeights.grpc.pb.cc")
set(GRPC_HDR "proto/sendReceiveWeights.grpc.pb.h")

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
add_executable(client client.cpp ${GRPC_SRC} ${PROTO_SRC})
target_link_libraries(client protoModule)
add_executable(server server.cpp ${GRPC_SRC} ${PROTO_SRC})
target_link_libraries(server protoModule)

#add_executable(modelSend modelSend.cpp ${PROTO_SRC} ${PROTO_HDR})
#target_link_libraries(modelSend protoModule "${TORCH_LIBRARIES}")

#protoc -I. --grpc_out=. --plugin=protoc-gen-grpc=/home/adduser/grpc/bin/grpc_cpp_plugin sendReceiveWeights.proto
#protoc -I. --cpp_out=. sendReceiveWeights.proto

#grpc 1.32
#client side version > 1.27
#grpcio
#grpcio-tools