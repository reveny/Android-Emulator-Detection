//
// Created by reveny on 29/08/2023.
//
#include <jni.h>
#include <string>
#include <vector>
#include <sys/system_properties.h>

using namespace std;

#include "Include/StringUtility.h"
#include "Include/EmulatorData.h"
#include "Include/FileHelper.h"

string detections;

/*
 * Read System property. Type getprop in shell to list all props
 */
string getSystemProperty(char *input) {
    char sdk_ver_str[PROP_VALUE_MAX];
    string output;
    if (__system_property_get(input, sdk_ver_str)) {
        output = string(sdk_ver_str);
    } else {
        output = string("unknown");
    }
    return output;
}

/*
 * Useless against any modern emulator such as nox or bluestacks
 */
void checkHardware() {
    string product = ::getSystemProperty("ro.build.product");
    string manufacturer = ::getSystemProperty("ro.product.manufacturer");
    string bootloader = ::getSystemProperty("ro.bootloader");
    string device = ::getSystemProperty("ro.product.device");
    string hardware = ::getSystemProperty("ro.hardware");

    for (const string& product : products) {
        if (strcmp(product.c_str(), product.c_str()) != 0) {
            detections.append(string("- Detected Product: ") + product + "\n");
        }
    }

    for (const string& _manufacturer : manufacturs) {
        if (StringUtility::stringCompare(manufacturer, _manufacturer)) {
            detections.append(string("- Detected Manufacturer: ") + manufacturer + "\n");
        }
    }

    if (StringUtility::stringCompare(bootloader, "nox")) {
        detections.append(string("- Detected Bootloader: ") + bootloader + "\n");
    }

    for (const string& info : deviceInfo) {
        if (StringUtility::stringCompare(device, info)) {
            detections.append(string("- Detected Device: ") + info + "\n");
        }
    }

    for (const string& _hardware : hardwares) {
        if (StringUtility::stringCompare(hardware, _hardware)) {
            detections.append(string("- Detected Hardware: ") + hardware + "\n");
        }
    }
}

void checkMounts() {
    vector<string> file = FileHelper::readFile("/proc/mounts");

    for (auto & i : file) {
        if (StringUtility::stringContains(i, "vboxsf")) {
            detections.append(string("- Detected VM Module in Mounts") + "\n");
        }
    }
}

/*
 * Bluestacks 4 is based on virtual box, meaning it needs a kernel module loaded for it
 */
void checkModules() {
    vector<string> file = FileHelper::readFile("/proc/modules");

    for (auto & i : file) {
        for (auto & procModule : procModules) {
            if (StringUtility::stringContains(i, procModule)) {
                detections.append(string("- Detected VM Module: ") + procModule + "\n");
            }
        }
    }
}

/*
 * CPU Info will always be the host cpu on emulators,
 * none of the emulators hide it for some reason
 */
void checkCPU() {
    vector<string> file = FileHelper::readFile("/proc/cpuinfo");

    for (auto & i : file) {
        if (StringUtility::stringContains(i, "hypervisor")) {
            detections.append(string("- Detected Hypervisor in cpuinfo") + "\n");
            break;
        }
    }

    //The only reason we loop over it twice is so we can get hypervisor detection and cpu detection
    for (auto & i : file) {
        if (StringUtility::stringContains(i, "amd") || StringUtility::stringContains(i, "intel")) {
            detections.append(string("- Detected Host CPU in cpuinfo") + "\n");
            break;
        }
    }
}

/*
 * Emulator specific files, most of these can be spoofed if you know which files you need
 */
void checkFiles() {
    for (int i = 0; i < emulatorFiles.size(); ++i) {
        if (FileHelper::fileExists(emulatorFiles[i])) {
            detections.append("- Detected Emulator File: " + emulatorFiles[i] + "\n");
        }
    }
}

void checkCPUArchitecture() {
    string abi = ::getSystemProperty("ro.product.cpu.abilist");

    if (StringUtility::stringContains(abi, "x86")) {
        detections.append("- Detected x86 Architecture\n");
    }
}

extern "C" {
    JNIEXPORT jboolean JNICALL
    Java_com_reveny_emulator_detection_MainActivity_isDetected(JNIEnv *env, jobject clazz) {
        checkHardware();
        checkMounts();
        checkModules();
        checkCPU();
        checkFiles();
        checkCPUArchitecture();

        return !detections.empty();
    }

    JNIEXPORT jstring JNICALL
    Java_com_reveny_emulator_detection_MainActivity_getResult(JNIEnv *env, jobject clazz) {
        detections.append("\n\n Created by github.com/reveny");
        return env->NewStringUTF(detections.c_str());
    }
}