package com.reveny.emulator.detection;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.widget.ImageViewCompat;

import android.annotation.SuppressLint;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public native boolean isDetected();
    public native String getResult();

    @SuppressLint({"SetTextI18n", "UseCompatLoadingForDrawables"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        System.loadLibrary("emulatordetector");

        getWindow().getDecorView().setBackgroundColor(Color.parseColor("#81a832"));
        TextView headerText = findViewById(R.id.header_text);
        ImageView headerImage = findViewById(R.id.header_image);
        TextView detectionText = findViewById(R.id.detection_test);

        boolean result = isDetected();
        if (result) {
            getWindow().getDecorView().setBackgroundColor(Color.parseColor("#a83632"));

            headerText.setText("Emulation Detected");
            headerText.setTextColor(this.getResources().getColor(R.color.white));

            headerImage.setImageDrawable(getResources().getDrawable(R.drawable.xmark));
            headerImage.setColorFilter(Color.parseColor("#FF0000"));

            detectionText.setText(getResult());
            detectionText.setTextColor(this.getResources().getColor(R.color.white));
        }
    }
}