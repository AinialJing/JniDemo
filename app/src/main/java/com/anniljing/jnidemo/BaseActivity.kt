package com.anniljing.jnidemo

import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import androidx.databinding.ViewDataBinding

abstract class BaseActivity<DB : ViewDataBinding> : AppCompatActivity() {
    protected lateinit var mContext: Context
    protected lateinit var binding: DB
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        mContext = this
        binding = DataBindingUtil.inflate(LayoutInflater.from(mContext), getLayoutId(), null, false)
        setContentView(binding.root)
        initData()
        setListener()
    }

    protected abstract fun getLayoutId(): Int

    protected abstract fun initData()

    protected abstract fun setListener()
}