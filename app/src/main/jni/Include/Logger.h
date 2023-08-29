#ifndef LOGGER_H
#define LOGGER_H

#include <android/log.h>

enum daLogType {
    daDEBUG = 3,
    daERROR = 6,
    daINFO = 4,
    daWARN = 5
};

#define TAG "EmulatorDetector"

#define LOGD(...) ((void)__android_log_print(daDEBUG, TAG, __VA_ARGS__))
#define LOGE(...) AntiCheatMain::logMessage(GlobalDef::ERROR, __VA_ARGS__)
#define LOGI(...) AntiCheatMain::logMessage(GlobalDef::MESSAGE, __VA_ARGS__)
#define LOGW(...) AntiCheatMain::logMessage(GlobalDef::WARNING, __VA_ARGS__)

#endif