package com.anniljing.jnidemo;

import android.Manifest;
import android.os.Environment;

import androidx.annotation.NonNull;

import com.anniljing.jnidemo.databinding.ActivityFileOperatorBinding;
import com.anniljing.unixlearn.UnixNativeLib;

import java.util.List;

import pub.devrel.easypermissions.EasyPermissions;

public class FileOperatorActivity extends BaseActivity<ActivityFileOperatorBinding> implements EasyPermissions.PermissionCallbacks {

    @Override
    protected int getLayoutId() {
        return R.layout.activity_file_operator;
    }

    @Override
    protected void initData() {
        EasyPermissions.requestPermissions(this, "", 100, Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE);
    }

    @Override
    protected void setListener() {
        mBinding.btnCreateFile.setOnClickListener((view) -> {
            UnixNativeLib.creatFile(Environment.getExternalStorageDirectory().getPath()+"/unix/text.txt");
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
}