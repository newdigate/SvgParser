cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(SvgParser_st7735_test C CXX)
set(BUILD_FOR_OPENGL_EMULATOR 1)

set(USE_SD 1)

include(../CMakeLists.cmake.in)

if (DEFINED BUILD_FOR_OPENGL_EMULATOR)
    add_executable(SvgParser_st7735_test
            st7735.cpp
            ../../../SvgParser.h
            ../../../SvgParser.cpp
            ../../../SvgOutput_st7735_t3.h
            ../../../SvgOutput_st7735_t3.cpp)
    target_link_libraries(SvgParser_st7735_test ${LIBS} ${teensy_x86_stubs_LIBS} ${teensy_st7735_linux_stubs_LIBS} ${teensy_st7735_linux_extras_opengl_LIBS})
else()
    teensy_add_executable(SvgParser_st7735_test
            st7735.cpp)
endif()

