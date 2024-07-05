package com.reveny.emulator.detection.sample;


import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import com.reveny.emulator.detection.EmulatorDetection;

public class MainActivity extends AppCompatActivity {

    @SuppressLint({"SetTextI18n", "UseCompatLoadingForDrawables"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        EmulatorDetection detection = new EmulatorDetection();

        getWindow().getDecorView().setBackgroundColor(Color.parseColor("#81a832"));
        TextView headerText = findViewById(R.id.header_text);
        ImageView headerImage = findViewById(R.id.header_image);
        TextView detectionText = findViewById(R.id.detection_test);

        boolean result = detection.isDetected();
        if (result) {
            getWindow().getDecorView().setBackgroundColor(Color.parseColor("#a83632"));

            headerText.setText("Emulation Detected");
            headerText.setTextColor(this.getResources().getColor(R.color.white));

            headerImage.setImageDrawable(getResources().getDrawable(R.drawable.xmark));
            headerImage.setColorFilter(Color.parseColor("#FF0000"));

            detectionText.setText(detection.getResult());
            detectionText.setTextColor(this.getResources().getColor(R.color.white));
        }
    }
}