//
// Created by kunaldawn on 23/12/16.
//

#ifndef RND_CORE_FILEUTILS_H
#define RND_CORE_FILEUTILS_H


#include "jsoncpp/json.h"

class FileUtils {
public:
    static Json::Value loadJson(std::string path);
    static std::vector<std::string> getFiles(std::string path, bool isApplyFilter, std::string filter);
    static std::vector<std::string> getDirs(std::string path);
};


#endif //RND_CORE_FILEUTILS_H
