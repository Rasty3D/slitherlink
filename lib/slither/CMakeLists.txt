# Project configuration
project(slither)

# Include directories
include_directories(include)

# Add library
add_library(slither
  src/slither.cpp)

# Add test
#add_executable(test
#  test/test.cpp)
#target_link_libraries(test
#  slither)
#add_test(Test
#  ${EXECUTABLE_OUTPUT_PATH}/test)

