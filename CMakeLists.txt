cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(modelSend)
set(CMAKE_PREFIX_PATH "/home/adduser/libtorch/share/cmake/Torch")

find_package(Torch REQUIRED)
message(${TORCH_LIBRARIES})
add_subdirectory(proto)

add_executable(modelSend modelSend.cpp ${PROTO_SRCS} ${PROTO_HDR})
target_link_libraries(modelSend protoModule "${TORCH_LIBRARIES}")
