//
// Created by reveny on 29/08/2023.
//

namespace StringUtility {
    bool stringContains(string str, string contains) {
        if (str.find(contains) != std::string::npos) {
            return true;
        }
        return false;
    }

    bool stringCompare(string str1, string str2) {
        return str1 == str2;
    }
}