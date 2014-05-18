# Project configuration
project(slither)

# Include directories
include_directories(include)

# Add library
add_library(slither
  src/slither.cpp)

# Add test
add_executable(test_board
  test/test_board.cpp)
target_link_libraries(test_board
  slither)
add_test(Board
  ${EXECUTABLE_OUTPUT_PATH}/test_board)
