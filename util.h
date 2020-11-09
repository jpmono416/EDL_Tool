//
// Created by jpmon on 09/11/2020.
//

#ifndef EDL_TOOL_UTIL_H
#define EDL_TOOL_UTIL_H


#include <vector>
#include <string>

class util {

public:
    void processDir(const std::string& path);
private:
    std::vector<std::string> openDir(std::string path = ".");
    std::vector<std::string> readFile(std::string fileName);
    void writeResult(const std::string& path, std::vector<std::string> resultsList);
    bool isDuplicate(std::vector<std::string> vec, const std::string duplicate);
};


#endif //EDL_TOOL_UTIL_H
