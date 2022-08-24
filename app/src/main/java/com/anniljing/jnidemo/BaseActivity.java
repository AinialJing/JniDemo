package com.anniljing.jnidemo;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;
import androidx.databinding.ViewDataBinding;

public abstract class BaseActivity<DB extends ViewDataBinding> extends AppCompatActivity {
    protected Context mContext;
    protected DB mBinding;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mContext = this;
        mBinding = DataBindingUtil.inflate(LayoutInflater.from(this), getLayoutId(), null, false);
        setContentView(mBinding.getRoot());
        initData();
        setListener();
    }

    protected abstract int getLayoutId();

    protected abstract void initData();

    protected abstract void setListener();
}