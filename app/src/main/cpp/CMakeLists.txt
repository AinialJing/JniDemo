cmake_minimum_required(VERSION 3.10.2)

project("jnidemo")


add_library(
        native-lib
        SHARED
        native-lib.cpp
)
add_library(
        dynamicLoad-lib
        SHARED
        jni_dynamic_load.cpp
)
add_library(
        basicType-lib
        SHARED
        basicType.cpp
)
find_library(
        log-lib
        log
)
include_directories(${CMAKE_HOME_DIRECTORY}/base)
target_link_libraries(
        native-lib
        ${log-lib})
target_link_libraries(
        dynamicLoad-lib
        ${log-lib}
)
target_link_libraries(
        basicType-lib
        ${log-lib}
)