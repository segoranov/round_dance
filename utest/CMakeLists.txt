cmake_minimum_required(VERSION 3.0.0)
project(ChorbRoundDance VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)

set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(chorb_round_dance_utest
    utest_main.cpp
    chorb_round_dance_utest.cpp
    nickname_generator_utest.cpp
    input_file_utest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/model/chorb_dancer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/model/chorb_round_dance.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/chorb_round_dance_builder/chorb_round_dance_builder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/chorb_round_dance_builder/chorb_round_dance_director.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/nickname_generator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/chorb_round_dance_app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/presenter/chorb_round_dance_presenter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/view/console_chorb_round_dance_view.cpp)

set_property(TARGET chorb_round_dance_utest PROPERTY CXX_STANDARD 20)

target_include_directories(chorb_round_dance_utest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test_framework)

add_test(chorb_round_dance chorb_round_dance_utest)
