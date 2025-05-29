//
// Created by xyx on 25-5-30.
//

#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <string>
#include <vector>

class StringUtil {
private:
    StringUtil() = default;

public:
    static std::string escape(const std::string &str);
    static std::string unescape(const std::string &str);
    static std::vector<std::string> split(const std::string &str, char delimiter);
};

#endif //STRINGUTIL_H
