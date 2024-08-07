cmake_minimum_required(VERSION 3.5)

project(c8emu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  c8emu
  main.cpp
  cpu.hpp
  cpu.cpp
  memory.hpp
  memory.cpp
  display.hpp
  display.cpp
  input.cpp
  input.hpp
  utils.hpp
  audio.hpp
  audio.cpp)

target_link_libraries(c8emu SDL2)


include(GNUInstallDirs)
install(
  TARGETS c8emu
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
