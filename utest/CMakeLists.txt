cmake_minimum_required(VERSION 3.0.0)
project(ChorbRoundDance VERSION 0.1.0)

add_executable(chorb_round_dance_utest
    utest_main.cpp
    chorb_round_dance_utest.cpp
    nickname_generator_utest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/model/chorb_dancer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/model/chorb_round_dance.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/chorb_round_dance_builder/chorb_round_dance_builder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/chorb_round_dance_builder/chorb_round_dance_director.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/nickname_generator.cpp)

set_property(TARGET chorb_round_dance_utest PROPERTY CXX_STANDARD 20)

target_include_directories(chorb_round_dance_utest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test_framework)

add_test(chorb_round_dance chorb_round_dance_utest)
