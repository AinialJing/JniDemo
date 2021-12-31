# JniDemo
问题1：
新增加的AndroidLog.h的头文件一直无法预编译<android/log.h>和<jni.h>头文件

解决方法：
先创建空的AndroidLog.h文件，然后在其他的cpp源文件加入其预编译的头文件，重新编译一下，AndroidLog头文件再重新加入相关的头文件，编译即可通过
