package com.reveny.emulatordetector.plugin;

public class EmulatorDetection {
    public EmulatorDetection() {
        System.loadLibrary("emulatordetector");
    }

    public native boolean isDetected();
    public native String getResult();
}
