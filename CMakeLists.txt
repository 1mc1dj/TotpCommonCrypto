cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
include_directories(include)

project(totp)
add_library(totp SHARED 
    src/totp_token_generator.cc 
    src/base32_decoder.cc
    c_interface.cpp)

project(totpCmd)
add_executable(totpCmd main.cpp)
target_link_libraries(totpCmd totp "-framework System")
set_target_properties(totpCmd PROPERTIES LINK_FLAGS "-Wl,-F/Library/Frameworks")

enable_testing()
add_subdirectory(test)

