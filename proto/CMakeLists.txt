find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRC PROTO_HEADER modelParams.proto)

add_library(protoModule ${PROTO_SRC} ${PROTO_HEADER})
target_link_libraries(protoModule ${Protobuf_LIBRARIES})
target_include_directories(protoModule PUBLIC ${Protobuf_INCLUDE_DIRS})

#old method (keeping for now in case things break)
#add_library(protoModule modelParams.pb.cc)

#set up the include directory
#set(PROTO_MODULE_INCLUDE_DIR -I/usr/include)
#target_include_directories(protoModule PUBLIC PROTO_MODULE_INCLUDE_DIR)
#set up the libraries
#target_link_libraries(protoModule -L/usr/lib -lprotobuf -lpthread -pthread)
