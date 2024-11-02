//
// Created by reveny on 29/08/2023.
//

#include <link.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <dirent.h>
#include <unistd.h>

namespace FileHelper {
    inline bool findStringInMaps(const std::string& targetLib, const std::string& targetString) {
        std::ifstream mapsFile("/proc/self/maps");
        if (!mapsFile.is_open()) {
            perror("fopen");
            return false;
        }

        std::string line;
        void *startAddr = nullptr, *endAddr = nullptr;

        while (std::getline(mapsFile, line)) {
            std::istringstream iss(line);
            std::string addressRange, permissions, offset, dev, inode, pathname;

            if (iss >> addressRange >> permissions >> offset >> dev >> inode) {
                if (iss >> pathname && pathname.find(targetLib) != std::string::npos) {
                    sscanf(addressRange.c_str(), "%p-%p", &startAddr, &endAddr);
                    auto size = static_cast<size_t>(static_cast<char *>(endAddr) - static_cast<char *>(startAddr));

                    if (permissions.find('r') != std::string::npos) {
                        for (size_t offset = 0; offset <= size - targetString.size(); offset++) {
                            if (memcmp(static_cast<char *>(startAddr) + offset, targetString.c_str(), targetString.size()) == 0) {
                                return true;
                            }
                        }
                    }
                }
            }
        }

        return false;
    }

    inline std::vector<std::string> readFile(const std::string& path) {
        std::vector<std::string> returnVal = std::vector<std::string>();
        char line[512] = {0};
        unsigned int line_count = 0;

        FILE *file = fopen(path.c_str(), "r");
        if (!file) {
            return returnVal;
        }

        while (fgets(line, 512, file)) {
            line_count++;
            returnVal.emplace_back(line);
        }

        fclose(file);
        return returnVal;
    }

    inline std::vector<std::string> listFilesInDirectory(const std::string& path) {
        std::vector<std::string> files;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(path.c_str())) != nullptr) {
            while ((ent = readdir(dir)) != nullptr) {
                files.emplace_back(ent->d_name);
            }
            closedir(dir);
        }

        return files;
    }

    inline bool fileExists(const std::string& path) {
        FILE *file;
        if ((file = fopen(path.c_str(), "r"))) {
            fclose(file);
            return true;
        } else {
            return false;
        }
    }

    inline std::vector<dl_phdr_info> getLoadedLibraries() {
        std::vector<dl_phdr_info> infos{};
        dl_iterate_phdr([](struct dl_phdr_info *info, size_t size, void *data) -> int {
            if ((info)->dlpi_name == nullptr) {
                return 0;
            }

            ((std::vector<dl_phdr_info> *) data)->push_back(*info);
            return 0;
        }, &infos);

        return infos;
    }

    inline std::string getSystemProperty(const std::string& input) {
        char prop_out[PROP_VALUE_MAX];
        if (__system_property_get(input.c_str(), prop_out)) {
            return {prop_out};
        }

        return "";
    }
}
