package com.anniljing.jnidemo;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                People people = new People();
//                JniCallJavaField jniCallJavaField = new JniCallJavaField();
//                jniCallJavaField.initPeopleData(people);
                JniThread jniThread = new JniThread();
//                jniThread.createNativeThread();
//                jniThread.createNativeThreadWithArgs();
//                jniThread.joinNativeThread();
                jniThread.startProductAndConsumerThread();
            }
        });

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

}