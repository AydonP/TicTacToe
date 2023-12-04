# CMakeList.txt : CMake project for CTicTacToe, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CTicTacToe "CTicTacToe.cpp" "CTicTacToe.h"  )

add_custom_command(TARGET CTicTacToe POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/public $<TARGET_FILE_DIR:CTicTacToe>)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CTicTacToe PROPERTY CXX_STANDARD 20)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sEXPORTED_RUNTIME_METHODS=cwrap")
# TODO: Add tests and install targets if needed.
