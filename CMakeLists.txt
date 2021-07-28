cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(modelSend)
#set(CMAKE_PREFIX_PATH "$(python -c 'import torch.utils; print(torch.utils.cmake_prefix_path)')")

find_package(Torch REQUIRED)

add_subdirectory(proto)

add_executable(modelSend modelSend.cpp)
target_link_libraries(modelSend protoModule ${TORCH_LIBRARIES})

#cmake -DCMAKE_PREFIX_PATH="$(python -c 'import torch.utils; print(torch.utils.cmake_prefix_path)')" ..