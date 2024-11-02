package com.reveny.emulatordetector;

import android.app.Application;
import android.content.SharedPreferences;

import androidx.preference.PreferenceManager;

public class App extends Application {

    private static App instance = null;
    private SharedPreferences pref;
    public static SharedPreferences getPreferences() {
        return instance.pref;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        instance = this;
        pref = PreferenceManager.getDefaultSharedPreferences(this);
    }
}