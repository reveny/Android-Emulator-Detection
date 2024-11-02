//
// Created by reveny on 11/2/2024.
//
#include <Headers/EmulatorDetection.hpp>

namespace EmulatorDetection
{
    std::vector<std::string> detections;
}

void EmulatorDetection::checkHardwareProps() {
    std::string product = FileHelper::getSystemProperty("ro.build.product");
    std::string manufacturer = FileHelper::getSystemProperty("ro.product.manufacturer");
    std::string bootloader = FileHelper::getSystemProperty("ro.bootloader");
    std::string device = FileHelper::getSystemProperty("ro.product.device");
    std::string hardware = FileHelper::getSystemProperty("ro.hardware");

    for (const std::string& _product : EmulatorData::products) {
        if (product == _product) {
            detections.push_back("- Detected Product: " + _product);
        }
    }

    for (const std::string& _manufacturer : EmulatorData::manufacturers) {
        if (manufacturer == _manufacturer) {
            detections.push_back("- Detected Manufacturer: " + manufacturer);
        }
    }

    if (bootloader == "nox") {
        detections.push_back("- Detected Bootloader: " + bootloader);
    }

    for (const std::string& info : EmulatorData::deviceInfo) {
        if (device == info) {
            detections.push_back("- Detected Device: " + info);
        }
    }

    for (const std::string& _hardware : EmulatorData::hardwares) {
        if (hardware == _hardware) {
            detections.push_back("- Detected Hardware: " + hardware);
        }
    }
}

void EmulatorDetection::checkMounts() {
    std::vector<std::string> file = FileHelper::readFile("/proc/mounts");

    for (const std::string& i : file) {
        if (i.find("vboxsf") != std::string::npos) {
            detections.emplace_back("- Detected VM Module in Mounts");
            return;
        }
    }
}

void EmulatorDetection::checkCPUInfo() {
    std::vector<std::string> file = FileHelper::readFile("/proc/cpuinfo");

    for (const std::string& i : file) {
        if (i.find("hypervisor") != std::string::npos) {
            detections.emplace_back("- Detected Hypervisor in cpuinfo");
            break;
        }
    }

    for (const std::string& i : file) {
        if (i.find("amd") != std::string::npos || i.find("intel") != std::string::npos) {
            detections.emplace_back("- Detected Host CPU in cpuinfo");
            break;
        }
    }
}

void EmulatorDetection::checkSystemFiles() {
    for (const std::string& emulatorFile : EmulatorData::emulatorFiles) {
        if (FileHelper::fileExists(emulatorFile)) {
            detections.push_back("- Detected Emulator File: " + emulatorFile);
            break;
        }
    }

    for (const std::string& emulatorFile : EmulatorData::newEmulatorFiles) {
        if (FileHelper::fileExists(emulatorFile)) {
            detections.push_back("- Detected Emulator File (2): " + emulatorFile);
            break;
        }
    }

    std::vector<std::string> out = FileHelper::listFilesInDirectory("/data/property/");
    for (const std::string& i : out) {
        if (i.find("nox") != std::string::npos) {
            detections.emplace_back("- Detected Nox Property File");
            break;
        }
    }
}

void EmulatorDetection::checkCPUArchitecture() {
    std::string abi = FileHelper::getSystemProperty("ro.product.cpu.abilist");

    if (abi.find("x86") != std::string::npos) {
        detections.emplace_back("- Detected x86 Architecture");
    }
}

void EmulatorDetection::checkArmTranslation() {
    std::vector<dl_phdr_info> info = FileHelper::getLoadedLibraries();
    for (const dl_phdr_info& i : info) {
        if (strstr(i.dlpi_name, "libhoudini.so")) {
            detections.emplace_back("- Detected ARM Translation");
            break;
        }
    }

    std::string prop = FileHelper::getSystemProperty("ro.dalvik.vm.native.bridge");
    if (prop != "0" && !prop.empty()) {
        detections.emplace_back("- Detected ARM Translation Property");
    }

    if (FileHelper::fileExists("/system/lib/libhoudini.so") ||
        FileHelper::fileExists("/system/lib64/libhoudini.so")) {
        detections.emplace_back("- Detected ARM Translation Library");
    }

    std::string arm = FileHelper::getSystemProperty("ro.dalvik.vm.isa.arm");
    std::string arm64 = FileHelper::getSystemProperty("ro.dalvik.vm.isa.arm64");
    if (arm == "x86" || arm64 == "x86_64") {
        detections.emplace_back("- Detected ARM Translation Property (2)");
    }
}

void EmulatorDetection::findEmulatorMemory() {
    std::vector<std::string> libraries {
        "libc.so",
        "libandroid_runtime.so",
        "libart.so"
    };

    for (const std::string& library : libraries) {
        bool result = FileHelper::findStringInMaps(library, "bluestacks");
        if (result) {
            detections.emplace_back("- Detected Bluestacks Memory");
            return;
        }
    }
}

bool EmulatorDetection::isDetected() {
    if (!detections.empty()) {
        return true;
    }

    checkHardwareProps();
    checkMounts();
    checkCPUInfo();
    checkSystemFiles();
    checkCPUArchitecture();
    checkArmTranslation();
    findEmulatorMemory();

    return !detections.empty();
}

std::string EmulatorDetection::getResult() {
    if (detections.empty()) {
        return "";
    }

    std::string result;
    for (const std::string& detection : detections) {
        result += detection + "\n";
    }

    return result;
}