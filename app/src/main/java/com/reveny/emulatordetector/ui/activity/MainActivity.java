package com.reveny.emulatordetector.ui.activity;

import android.os.Bundle;

import com.reveny.emulatordetection.R;
import com.reveny.emulatordetection.databinding.ActivityMainBinding;
import com.reveny.emulatordetector.ui.fragment.HomeFragment;

public class MainActivity extends BaseActivity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityMainBinding binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        getSupportFragmentManager().beginTransaction().replace(R.id.container, new HomeFragment()).commit();
    }
}