cmake_minimum_required(VERSION 3.12)

add_executable(cli app.cpp)

set_property(TARGET cli PROPERTY C_STANDARD 99)
