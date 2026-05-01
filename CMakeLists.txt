cmake_minimum_required(VERSION 3.15...4.0)
project(CLI)

add_library(CLIlib)
target_include_directories(CLIlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(CLIlib PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Argument.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Command.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Interface.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Context.cpp"
)

add_executable(CLItest "CLI_lib_test.cpp")
target_link_libraries(CLItest PRIVATE CLIlib)