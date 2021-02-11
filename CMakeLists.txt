cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(SvgParser C CXX)

set(TEENSY_VERSION 40 CACHE STRING "Set to the Teensy version corresponding to your board (30 or 31 allowed)" FORCE)
set(CPU_CORE_SPEED 600000000 CACHE STRING "Set to 24000000, 48000000, 72000000 or 96000000 to set CPU core speed" FORCE) # Derived variables
set(CPU cortex-m7 CACHE STRING "Set to cortex-m7, cortex-m4")

set(COMPILERPATH "/Applications/ARM/bin/")
set(DEPSPATH "/Users/moolet/Development/newdigate/temp_dep")
set(COREPATH "${DEPSPATH}/cores/teensy4/")

find_package(teensy_cmake_macros)

import_arduino_library(${DEPSPATH} SPI)
import_arduino_library(${DEPSPATH} ST7735_t3)
import_arduino_library(${DEPSPATH} SdFat/src)
import_arduino_library(${DEPSPATH} SdFat/src/common)
import_arduino_library(${DEPSPATH} SdFat/src/DigitalIO)
import_arduino_library(${DEPSPATH} SdFat/src/ExFatLib)
import_arduino_library(${DEPSPATH} SdFat/src/FatLib)
import_arduino_library(${DEPSPATH} SdFat/src/FsLib)
import_arduino_library(${DEPSPATH} SdFat/src/iostream)
import_arduino_library(${DEPSPATH} SdFat/src/SdCard)
import_arduino_library(${DEPSPATH} SdFat/src/SpiDriver)
import_arduino_library(${DEPSPATH} SD/src)

teensy_add_library(SvgParser
        SvgParser.h
        SvgParser.cpp
        SvgOutput_st7735_t3.h
        SvgOutput_st7735_t3.cpp)
set(CMAKE_VERBOSE_MAKEFILE 1)