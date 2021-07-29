find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS modelParams.proto)
add_library(protoModule ${PROTO_HDRS} ${PROTO_SRCS})
target_link_libraries(protoModule ${Protobuf_LIBRARIES})


#old method (keeping for now in case things break)
#add_library(protoModule modelParams.pb.cc)

#set up the include directory
#set(PROTO_MODULE_INCLUDE_DIR -I/usr/include)
#target_include_directories(protoModule PUBLIC PROTO_MODULE_INCLUDE_DIR)
#set up the libraries
#target_link_libraries(protoModule -L/usr/lib -lprotobuf -lpthread -pthread)
