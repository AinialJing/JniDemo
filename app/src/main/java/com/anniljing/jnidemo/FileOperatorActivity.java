package com.anniljing.jnidemo;

import android.Manifest;
import android.os.Environment;
import android.util.Log;

import com.anniljing.jnidemo.databinding.ActivityFileOperatorBinding;
import com.anniljing.unixlearn.FileCallBack;
import com.anniljing.unixlearn.UnixNativeLib;

import java.util.List;

import androidx.annotation.NonNull;
import pub.devrel.easypermissions.EasyPermissions;

public class FileOperatorActivity extends BaseActivity<ActivityFileOperatorBinding> implements EasyPermissions.PermissionCallbacks, FileCallBack {
    private static final String TAG = "FileOperatorActivity";
    private static final String DIRECTOR = Environment.getExternalStorageDirectory() + "/unix/";
    private int fd;
    private UnixNativeLib mUnixNativeLib;

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
        mBinding.btnCreateFile.setOnClickListener((view) -> mUnixNativeLib.creatFile(DIRECTOR, "text.txt"));
        mBinding.btnOpenFile.setOnClickListener((view) -> fd = mUnixNativeLib.openFile(DIRECTOR, "text.txt"));
        mBinding.btnSeekFile.setOnClickListener((view) -> {
            int index = mUnixNativeLib.lseekFile(fd);
            Log.d(TAG, "Index:" + index);
        });
        mBinding.btnWriteFile.setOnClickListener((view) -> {
            byte[] data = mBinding.etContent.getText().toString().getBytes();
            int ret = mUnixNativeLib.writeFile(fd, data, data.length);
            if (ret == data.length) {
                mBinding.etContent.setText("");
            } else {
                Log.d(TAG, "写入错误：" + ret);
            }
        });
        mBinding.btnReadFile.setOnClickListener((view) -> {
            if (mUnixNativeLib != null) {
                mUnixNativeLib.readFile(fd);
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
        mUnixNativeLib.closeFile(fd);
    }

    @Override
    public void readData(byte[] data) {
        String content = new String(data);
        Log.d(TAG,content);
        mBinding.tvFileContent.setText("" + content);
    }
}