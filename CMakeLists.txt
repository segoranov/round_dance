cmake_minimum_required(VERSION 3.0.0)
project(ChorbRoundDance VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(chorb_round_dance
  main.cpp
  src/chorb_dancer.cpp
  src/chorb_round_dance.cpp
  src/chorb_round_dance_builder/chorb_round_dance_builder.cpp
  src/chorb_round_dance_builder/chorb_round_dance_director.cpp
  src/nickname_generator.cpp)

set_property(TARGET chorb_round_dance PROPERTY CXX_STANDARD 20)

target_include_directories(chorb_round_dance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(utest)
