cmake_minimum_required(VERSION 3.10.2)

project("serialportlib")

add_library( # Sets the name of the library.
        SerialPortlib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/SerialPortJNI.cpp
        src/SerialPort.cpp)

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

target_link_libraries( # Specifies the target library.
        SerialPortlib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})