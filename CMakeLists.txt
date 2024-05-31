cmake_minimum_required(VERSION 3.5)

project(CHIP8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  CHIP8
  main.cpp
  cpu.hpp
  cpu.cpp
  memory.hpp
  memory.cpp
  display.hpp
  display.cpp
  input.hpp
  input.cpp)

target_link_libraries(CHIP8 SDL2)

include(GNUInstallDirs)
install(
  TARGETS CHIP8
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
