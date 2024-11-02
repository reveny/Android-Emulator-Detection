//
// Created by reveny on 29/08/2023.
//
#include <Headers/EmulatorDetection.hpp>

extern "C" {
    JNIEXPORT jboolean JNICALL
    Java_com_reveny_emulatordetector_plugin_EmulatorDetection_isDetected(JNIEnv *env, jobject clazz) {
        (void)env;
        (void)clazz;

        return EmulatorDetection::isDetected();
    }

    JNIEXPORT jstring JNICALL
    Java_com_reveny_emulatordetector_plugin_EmulatorDetection_getResult(JNIEnv *env, jobject clazz) {
        (void)clazz;

        return env->NewStringUTF(EmulatorDetection::getResult().c_str());
    }
}
