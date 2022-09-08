package com.anniljing.jnidemo;

import android.Manifest;
import android.os.Environment;
import android.util.Log;
import android.view.View;

import com.anniljing.jnidemo.databinding.ActivityFileOperatorBinding;
import com.anniljing.unixlearn.FileCallBack;
import com.anniljing.unixlearn.FileInfo;
import com.anniljing.unixlearn.UnixNativeLib;

import java.util.List;

import androidx.annotation.NonNull;
import pub.devrel.easypermissions.EasyPermissions;

public class FileOperatorActivity extends BaseActivity<ActivityFileOperatorBinding> implements EasyPermissions.PermissionCallbacks, FileCallBack {
    private static final String TAG = "FileOperatorActivity";
    private static final String DIRECTOR = Environment.getExternalStorageDirectory() + "/unix/";
    private static final String FILE_NAME = "text.txt";
    private int fd;
    private UnixNativeLib mUnixNativeLib;
    private long streamFile;

    @Override
    protected int getLayoutId() {
        return R.layout.activity_file_operator;
    }

    @Override
    protected void initData() {
        mUnixNativeLib = new UnixNativeLib();
        mUnixNativeLib.initLib();
        mUnixNativeLib.setCallBack(this);
        if (EasyPermissions.hasPermissions(mContext, Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
            Log.d(TAG, "hasPermissions");
        } else {
            EasyPermissions.requestPermissions(this, "", 100, Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE);
        }
    }

    @Override
    protected void setListener() {
        mBinding.btnCreateFile.setOnClickListener((view) -> mUnixNativeLib.creatFile(DIRECTOR, FILE_NAME));
        mBinding.btnOpenFile.setOnClickListener((view) -> {
            boolean isChecked = mBinding.switchState.isChecked();
            if (isChecked) {
                fd = mUnixNativeLib.openFile(DIRECTOR, FILE_NAME);
            } else {
                streamFile = mUnixNativeLib.openStreamFile(DIRECTOR + FILE_NAME);
                Log.d(TAG, "openStreamFile:" + streamFile);
            }
        });
        mBinding.btnSeekFile.setOnClickListener((view) -> {
            int index = mUnixNativeLib.lseekFile(fd);
            Log.d(TAG, "Index:" + index);
        });
        mBinding.btnGetFileInfo.setOnClickListener((view) -> {
            FileInfo fileInfo = mUnixNativeLib.getFileInfo(DIRECTOR + FILE_NAME);
            Log.e(TAG, "FileInfo:" + fileInfo);
        });
        mBinding.btnWriteFile.setOnClickListener((view) -> {
            byte[] data = mBinding.etContent.getText().toString().getBytes();
            if (mBinding.switchState.isChecked()) {
                int ret = mUnixNativeLib.writeFile(fd, data, data.length);
                if (ret == data.length) {
                    mBinding.etContent.setText("");
                } else {
                    Log.d(TAG, "写入错误：" + ret);
                }
            } else {
                int ret = mUnixNativeLib.writeStreamFile(streamFile, data);
                if (ret == data.length) {
                    mBinding.etContent.setText("");
                }
            }

        });
        mBinding.btnReadFile.setOnClickListener((view) -> {
            if (mUnixNativeLib != null) {
                boolean isFileRead = mBinding.switchState.isChecked();
                if (isFileRead) {
                    mUnixNativeLib.readFile(fd);
                } else {
                    FileInfo fileInfo = mUnixNativeLib.getFileInfo(DIRECTOR + FILE_NAME);
                    mUnixNativeLib.readStreamIO(streamFile, (int) fileInfo.getSize());
                }
            }
        });
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        EasyPermissions.onRequestPermissionsResult(requestCode, permissions, grantResults, this);
    }

    @Override
    public void onPermissionsGranted(int requestCode, @NonNull List<String> perms) {

    }

    @Override
    public void onPermissionsDenied(int requestCode, @NonNull List<String> perms) {

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mBinding.switchState.isChecked()) {
            mUnixNativeLib.closeFile(fd);
        } else {
            mUnixNativeLib.closeStreamFile(streamFile);
        }
    }

    @Override
    public void readData(byte[] data) {
        String content = new String(data);
        Log.d(TAG, content);
        Log.d(TAG, "Thread:" + Thread.currentThread().getName());
        runOnUiThread(() -> {
            mBinding.tvFileContent.setText("" + content);
        });
    }

    public void createThread(View view) {
        mUnixNativeLib.createThread();
    }
}