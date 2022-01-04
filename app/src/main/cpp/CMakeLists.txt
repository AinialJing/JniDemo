cmake_minimum_required(VERSION 3.10.2)

project("jnidemo")

add_library(
        native-lib
        SHARED
        base/jvm.cpp
        base/AndroidLog.cpp
        native-lib.cpp
        jni_dynamic_load.cpp
        basicType.cpp
        jniCallJavaClassField.cpp
)


find_library(
        log-lib
        log
)
include_directories(${CMAKE_HOME_DIRECTORY}/base)
target_link_libraries(
        native-lib
        ${log-lib})
