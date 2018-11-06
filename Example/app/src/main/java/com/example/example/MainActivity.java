package com.example.example;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("internal-jni");
    }
    public native String stringFromJNI(int x);
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.txt_view);
        int k = 12345;
        tv.setText(stringFromJNI(k));
    }
}
