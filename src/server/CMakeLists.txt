cmake_minimum_required(VERSION 3.12)

add_executable(server app.cpp tcp.cpp)

set_property(TARGET server PROPERTY C_STANDARD 99)