# JniDemo
问题1：
新增加的AndroidLog.h的头文件一直无法预编译<android/log.h>和<jni.h>头文件

解决方法：
先创建空的AndroidLog.h文件，然后在其他的cpp源文件加入其预编译的头文件，重新编译一下，AndroidLog头文件再重新加入相关的头文件，编译即可通过

问题2：
新增加jni_dynamic_load.cpp，实现动态注册jni，CMakeList.txt的编写如下：
![image](https://user-images.githubusercontent.com/8243494/147808634-6dc02c34-a8b1-46dc-97dc-3267d267f3c4.png)  
新增了如下代码：
```
add_library(
        dynamicLoad-lib
        SHARED
        jni_dynamic_load.cpp
)
```
