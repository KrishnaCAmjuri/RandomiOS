//
// Created by kunaldawn on 23/12/16.
//

#include "FileUtils.h"
#include <iostream>
#include <fstream>
#include <dirent.h>

Json::Value FileUtils::loadJson(std::string path) {
    Json::Value root;
    Json::Reader reader;
    std::ifstream jsonData(path, std::ifstream::binary);

    try {
        if (!reader.parse(jsonData, root, false)) {
            throw std::runtime_error("reading file : " + path + " has failed!");
        }
    } catch (std::exception exception) {
        throw std::runtime_error("reading file : " + path + " has failed : " + std::string(exception.what()));
    }

    return root;
}

std::vector<std::string> FileUtils::getFiles(std::string path, bool isApplyFilter, std::string filter)  {
    std::vector<std::string> list;
    path = path + "/";
    DIR *dir = opendir(path.c_str());
    struct dirent *entry = readdir(dir);

    while (entry != NULL) {
        if (entry->d_type != DT_DIR) {
            std::string fileName = std::string(entry->d_name);
            if (isApplyFilter) {
                if (fileName.find(filter) != std::string::npos) {
                    list.push_back(fileName);
                }
            } else {
                list.push_back(fileName);
            }
        }
        entry = readdir(dir);
    }
    closedir(dir);

    return list;
}

std::vector<std::string> FileUtils::getDirs(std::string path)  {
    std::vector<std::string> list;
    DIR *dir = opendir(path.c_str());
    struct dirent *entry = readdir(dir);

    while (entry != NULL) {
        if (entry->d_type == DT_DIR) {
            std::string dirName = std::string(entry->d_name);
            if (dirName.find(".") == std::string::npos) {
                list.push_back(dirName);
            }
        }
        entry = readdir(dir);
    }
    closedir(dir);

    return list;
}
