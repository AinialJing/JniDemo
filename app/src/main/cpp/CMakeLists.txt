cmake_minimum_required(VERSION 3.10.2)

project("jnidemo")

add_library(
        native-lib
        SHARED
        base/jvm.cpp
        base/AndroidLog.cpp
        native-lib.cpp
        jniDynamicLoadNative.cpp
        basicType.cpp
        jniCallJavaClassField.cpp
        thread/jni_thread.cpp
        thread/jni_product_and_consumer_thread.cpp
        VersionInformation/VersionInformation.cpp
        JavaClassOperator/JavaClassOperator.cpp
        ClassFieldOperator/ClassStaticFieldOperator.cpp
        ClassFieldOperator/ClassFieldOperator.cpp
        ClassMethodOperator/ClassMethodOPerator.cpp
)


find_library(
        log-lib
        log
)
include_directories(${CMAKE_HOME_DIRECTORY}/base)
target_link_libraries(
        native-lib
        ${log-lib})
