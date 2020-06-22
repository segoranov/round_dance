cmake_minimum_required(VERSION 3.0.0)
project(ChorbRoundDance VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(chorb_round_dance
  main.cpp
  src/chorb_dancer.cpp)

target_include_directories(chorb_round_dance PUBLIC ${CMAKE_SOURCE_DIR}/include)
