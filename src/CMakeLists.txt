add_executable (TicTacToe "TicTacToe.cpp")

add_custom_command(TARGET TicTacToe POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/public $<TARGET_FILE_DIR:TicTacToe>)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TicTacToe PROPERTY CXX_STANDARD 20)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -sEXPORTED_RUNTIME_METHODS=cwrap")
