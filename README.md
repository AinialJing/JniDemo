# JniDemo
## JNI数据类型及与Java数据类型的映射关系
Java数据类型 | JNI数据类型
-------------|-----------
byte         | jbyte
char         | jchar
short        | jshort
int          | jint
long         | jlong
float        | jfloat
double       | jdouble

## java数据类型与签名类型的对应关系
Java类型  |  类型签名
----------|----------
boolean   |     Z
byte      |     B
int       |     I
char      |     C
short     |     S
long      |     L
float     |     F
double    |     D
void      |     V
数组     |     [类型签名，比如String[] 是[Ljava/lang/String;
类       |     L全限定名;，比如String, 其签名为Ljava/lang/String;(注意后面有个分号)
## 问题1：新增加的AndroidLog.h的头文件一直无法预编译<android/log.h>和<jni.h>头文件

## 解决方法：
先创建空的AndroidLog.h文件，然后在其他的cpp源文件加入其预编译的头文件，重新编译一下，AndroidLog头文件再重新加入相关的头文件，编译即可通过

## 问题2：新增加jni_dynamic_load.cpp，实现动态注册jni，CMakeList.txt的编写如下：
![image](https://user-images.githubusercontent.com/8243494/147808634-6dc02c34-a8b1-46dc-97dc-3267d267f3c4.png)  
新增了如下代码：
```
add_library(
        dynamicLoad-lib
        SHARED
        jni_dynamic_load.cpp
)
```  
## 但是编译的时候，抛出之前的AndroidLog.h文件未定义的异常  

![555d51a695b861ed316cd118068eefb](https://user-images.githubusercontent.com/8243494/147808895-532a97b6-d4ef-4a2a-88f9-7fb86a5b9f8e.png)  

## 解决方法：  
## 1、把jni_dynamic_load.cpp放到 native-lib里面，CMakeList.txt如下：
```
cmake_minimum_required(VERSION 3.10.2)

project("jnidemo")


add_library(
        native-lib
        SHARED
        native-lib.cpp
        jni_dynamic_load.cpp
)
find_library(
        log-lib
        log
)
include_directories(${CMAKE_HOME_DIRECTORY}/base)
target_link_libraries(
        native-lib
        ${log-lib})
```  
这样的话，就放在了一个库里面。  
## 2、但是这不是我当初想要的效果，我是想生成两个库的。原因肯定是在连接库的地方出现了问题的，于是CMakeList.txt改为如下内容：  
```
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
```  
## 核心代码在于最下面第二个target_link_libraries，就是做了dynamicLoad-lib库与Log库的连接。
```
target_link_libraries(
        dynamicLoad-lib
        ${log-lib}
```  
## 问题3：illegal class name  
![image](https://user-images.githubusercontent.com/8243494/147809896-45476764-8fa5-4411-b1f7-8d108890a582.png)  
![image](https://user-images.githubusercontent.com/8243494/147809848-36e28c7e-97e8-4fd9-936d-5eefd08543f3.png)  
## cpp文件是无法识别“.”的路径，要把“.”换成“/”即可
```
#define JAVA_CLASS "com/anniljing/jnidemo/JniDynamicLoad"
```


