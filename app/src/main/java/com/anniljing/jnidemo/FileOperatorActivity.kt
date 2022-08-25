package com.anniljing.jnidemo

import android.util.Log
import com.anniljing.jnidemo.databinding.ActivityFileOperatorBinding
import com.anniljing.unixlearn.UnixNativeLib

class FileOperatorActivity : BaseActivity<ActivityFileOperatorBinding>() {
    override fun getLayoutId(): Int {
        return R.layout.activity_file_operator
    }

    override fun initData() {
    }

    override fun setListener() {
        binding.btnCreateFile.setOnClickListener {
            Log.d("FileOperatorActivity","setOnClickListener")
            UnixNativeLib.creatFile("/sdcard/unix/test.txt")
        }
    }

}