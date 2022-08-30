package com.anniljing.unixlearn;

public class FileInfo {
    long size;

    public long getSize() {
        return size;
    }

    public void setSize(long size) {
        this.size = size;
    }

    @Override
    public String toString() {
        return "FileInfo{" +
                "size=" + size +
                '}';
    }
}
