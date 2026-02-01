cmake_minimum_required(VERSION 3.10)
project(TotpCommonCrypto)

set(CMAKE_CXX_STANDARD 11)

# Library
add_library(totp SHARED 
    src/totp_token_generator.cc 
    src/base32_decoder.cc
    c_interface.cpp)

target_include_directories(totp PUBLIC include)

if(APPLE)
    target_link_libraries(totp PRIVATE "-framework System")
endif()

# Executable
add_executable(totpCmd main.cpp)
target_link_libraries(totpCmd PRIVATE totp)

# Testing
enable_testing()
add_subdirectory(test)

