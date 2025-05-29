//
// Created by xyx on 25-5-30.
//

#include "StringUtil.h"
#include <sstream>

std::string StringUtil::escape(const std::string &str) {
    std::stringstream ss;
    for (const char &c : str) {
        switch (c) {
            case '\n':
                ss << "\\n";
                break;
            case '\\':
                ss << "\\\\";
                break;
            default:
                ss << c;
                break;
        }
    }
    return ss.str();
}

std::string StringUtil::unescape(const std::string &str) {
    std::stringstream ss;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '\\' && ++i < str.length()) {
            if (str[i] == 'n') {
                ss << '\n';
            } else if (str[i] == '\\') {
                ss << '\\';
            } else {
                throw std::invalid_argument("Invalid escape sequence");
            }
        } else {
            ss << str[i];
        }
    }
    return ss.str();
}

std::vector<std::string> StringUtil::split(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    if (str.find(delimiter) == std::string::npos) {
        result.push_back(str);
    } else {
        result.push_back(str.substr(0, str.find(delimiter)));
        result.push_back(str.substr(str.find(delimiter) + 1));
    }
    return result;
}
