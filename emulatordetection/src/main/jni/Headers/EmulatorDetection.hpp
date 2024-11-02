//
// Created by reveny on 11/2/2024.
//
#pragma once

#include <sys/system_properties.h>
#include <jni.h>
#include <string>
#include <vector>
#include <android/log.h>

#include <Include/FileHelper.hpp>
#include <Include/EmulatorData.hpp>

namespace EmulatorDetection
{
    extern std::vector<std::string> detections;

    void checkHardwareProps();
    void checkMounts();
    void checkCPUInfo();
    void checkSystemFiles();
    void checkCPUArchitecture();
    void checkArmTranslation();
    void findEmulatorMemory();

    bool isDetected();
    std::string getResult();
}