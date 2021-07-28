add_library(protoModule modelParams.pb.cc)

#set up the include directory
set(PROTO_MODULE_INCLUDE_DIR -I/usr/include)
target_include_directories(protoModule PUBLIC PROTO_MODULE_INCLUDE_DIR)
#set up the libraries
target_link_libraries(protoModule -L/usr/lib -lprotobuf -lpthread -pthread)