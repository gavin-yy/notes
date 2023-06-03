package com.example.calc;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        JNI j = new JNI();
        String s = j.sayHello();
        int v = j.calc(1,2);

        TextView txt = findViewById(R.id.textView);
        txt.setText( "data :"  + s );
    }
}