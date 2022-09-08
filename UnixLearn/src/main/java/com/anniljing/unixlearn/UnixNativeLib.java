package com.anniljing.unixlearn;

public class UnixNativeLib {
    private FileCallBack mCallBack;

    static {
        System.loadLibrary("unixlearn");
    }

    public native void initLib();

    public native int creatFile(String path, String fileName);

    public native FileInfo getFileInfo(String path);

    public native int openFile(String path, String fileName);

    public native void readFile(int fd);

    public native int writeFile(int fd, byte[] data, int size);

    public native int lseekFile(int fd);

    public native int closeFile(int fd);

    public void readCallBack(byte[] data) {
        if (mCallBack != null) {
            mCallBack.readData(data);
        }
    }

    public void setCallBack(FileCallBack callBack) {
        mCallBack = callBack;
    }

    public native long openStreamFile(String fileName);

    public native int writeStreamFile(long file, byte[] data);

    public native int readStreamIO(long file, int size);

    public native int closeStreamFile(long file);

    public native void createThread();

    public native void jointThread();

    public native void exitThread();
}