cmake_minimum_required(VERSION 3.20)
project(MockString)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/CMakeHelpers")

include(FileDownload)

FileDownload(https://github.com/catchorg/Catch2/releases/download/v2.13.6/catch.hpp
             "UnitTests/Catch2/catch.hpp" SHA1=31c6c4220b9cc768d3e59c32161c239b28c5415f)
FileDownload(https://raw.githubusercontent.com/rollbear/trompeloeil/v40/include/catch2/trompeloeil.hpp
             "UnitTests/Catch2/trompeloeil.hpp" SHA1=1c4c6a8d788630936acb0b8601ad2e0cf9c646b7)
FileDownload(https://raw.githubusercontent.com/rollbear/trompeloeil/v40/include/trompeloeil.hpp
             UnitTests/trompeloeil.hpp SHA1=ecdba31204124a5cce7ae2bd58495ff7c0b862bb)

include_directories(".")
add_library(MockString SHARED
            Strings/StringManipulation.cpp
            Strings/StringManipulation.h
            Strings/FastString.cpp
            Strings/FastString.h
            GeneralMacros/NPOS.h
            BitTwiddling/BitHacks.h
            GeneralMacros/ALIGN.h
            MemoryManagement/MemoryManager.cpp
            MemoryManagement/MemoryManager.h
            Exceptions/ExceptionHandling.cpp
            Exceptions/ExceptionHandling.h
            GeneralMacros/ALIGN.h
            )

add_executable(Catch_tests_run

               UnitTests/Mocks/MockStringManipulation.cpp
               UnitTests/Mocks/MockStringManipulation.h
               UnitTests/Catch2/catchmain.cpp
               UnitTests/Matchers/cstring.h
               UnitTests/StringManipulation/StripComments.cpp
               UnitTests/StringManipulation/Substring.cpp
               )

target_link_libraries(Catch_tests_run MockString)