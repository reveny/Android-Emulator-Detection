//
// Created by reveny on 29/08/2023.
//

namespace FileHelper {
    std::vector<std::string> readFile(const string& path) {
        std::vector<std::string> returnVal = std::vector<std::string>();
        char line[512] = {0};
        unsigned int line_count = 0;

        FILE *file = fopen(path.c_str(), "r");
        if (!file) {
            returnVal.push_back("File error");
            return returnVal;
        }

        while (fgets(line, 512, file)) {
            line_count++;
            returnVal.emplace_back(line);
        }

        fclose(file);
        if (returnVal.empty()) {
            returnVal.push_back("empty");
        }

        return returnVal;
    }

    bool fileExists(const string& path) {
        FILE *file;
        if ((file = fopen(path.c_str(), "r"))) {
            fclose(file);
            return true;
        } else {
            return false;
        }
    }
}
