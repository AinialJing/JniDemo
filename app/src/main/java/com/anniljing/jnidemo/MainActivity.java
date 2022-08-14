package com.anniljing.jnidemo;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.anniljing.jnidemo.ClassFieldOperator.ClassStaticFieldOperator;
import com.anniljing.jnidemo.ClassOperator.FindClassForJava;
import com.anniljing.jnidemo.ClassOperator.JniDynamicLoad;
import com.anniljing.jnidemo.JavaClassOperator.JniOperatorJavaClass;
import com.anniljing.jnidemo.VersionInformation.VersionInformation;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public void findClass(View view) {
        JniDynamicLoad dynamicLoad = new JniDynamicLoad();
        Log.d(TAG, dynamicLoad.getNativeString());
    }

    public void toVersionInformation(View view) {
        int versionInformation = VersionInformation.getVersionInformation();
        Log.d(TAG, "VersionInformation:0x" + Integer.toHexString(versionInformation));
    }

    public void findJavaClass(View view) {
        FindClassForJava forJava = new FindClassForJava();
        Animal animal = forJava.InitAnimal();
        Log.d(TAG, "Hash:" + animal.hashCode());
        Log.d(TAG, animal.toString());

        JavaClass javaClass = JniOperatorJavaClass.operatorJavaClass();
        Log.d(TAG, "JavaClass:" + javaClass);
    }

    public void setStaticField(View view) {
        StaticFieldClass staticFieldClass = new StaticFieldClass();
        ClassStaticFieldOperator.setClassStaticField(staticFieldClass);
        Log.d(TAG, "getStaticField:" + ClassStaticFieldOperator.getClassStaticField(staticFieldClass));
    }
}