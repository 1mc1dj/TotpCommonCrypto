# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


# Now simply link against gtest or gtest_main as needed. Eg

include_directories(${CMAKE_CURRENT_DIR}../include/)

set(MYWD "${CMAKE_CURRENT_BINARY_DIR}")
message(${MYWD})

if(NOT EXISTS ${MYWD}/Base32randomStr.inc)
  message("Base32randomStr.inc is not found")
  set(MYPYTHONCMD "/usr/bin/python")
  set(MYPYTHONARG1 "${CMAKE_SOURCE_DIR}/test/CreateRandomDataset.py")
  message(${MYPYTHONCMD})
  execute_process(
    COMMAND ${MYPYTHONCMD} ${MYPYTHONARG1}
    WORKING_DIRECTORY ${MYWD} 
    RESULT_VARIABLE CMD_ERROR
    OUTPUT_FILE CMD_OUTPUT)
  
  message( STATUS "CMD_ERROR:" ${CMD_ERROR})
  message( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})    
  message("generate test codes")  
endif()

include_directories(${MYWD})
add_executable(test Base32DecoderTest.cpp)
target_link_libraries(test gtest_main totp)
add_test(NAME example_test COMMAND test)

