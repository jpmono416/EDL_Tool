//
// Tool created and owned by Jonathan Perez. For any queries contact jonathanperez.11.02.98@gmail.com
//
#include <dirent.h>
#include <fstream>
#include "util.h"

// Extract from http://forum.codecall.net/topic/60157-read-all-files-in-a-folder/
std::vector<std::string> util::openDir(std::string path) {

    DIR*    dir;
    dirent* pdir;
    std::vector<std::string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) {
        files.emplace_back(pdir->d_name);
    }

    return files;
}

std::vector<std::string> util::readFile(std::string fileName)
{
    std::vector<std::string> lines;

    std::ifstream fsFile(fileName);
    std::string line;

    while(std::getline(fsFile, line)) {
        lines.emplace_back(line);
    }
    return lines;
}

void util::processDir(const std::string& path)
{
    // Get all file names
    std::vector<std::string> fileNames = openDir(path);
    std::vector<std::string> resultsList;

    for(unsigned int i = 0; i < fileNames.size(); i++)
    {
        if(fileNames[i].length() < 4)
            continue;

        std::string extension =fileNames[i].substr(fileNames[i].length() - 4, 4);
        // Ensuring only the right files are evaluated
        if(extension != ".edl")
            continue;

        // Get all lines for each file
        std::vector<std::string> lines = readFile(path + "\\" + fileNames[i]);

        // Loop through characters in order to get second word with custom spacing
        for(unsigned int j = 0; j < lines.size(); j++)
        {
            bool firstWordCompleted = false;
            bool secondWordCompleted = false;

            // The word we're looking for
            std::string fileName = "";

            // Not take into account any lines without data
            if(lines[j][0] == '*'
            || lines[j].substr(0, 6) == "TITLE:"
            || lines[j].substr(0, 4) == "FCM:")
                continue;

            for(auto currentChar : lines[j])
            {
                if(!firstWordCompleted)
                {
                    if(isspace(currentChar))
                    {
                       firstWordCompleted = true;
                    }
                } else
                {
                    if(!isspace(currentChar))
                    {
                        secondWordCompleted = true;
                        fileName += currentChar;
                    } else
                    {
                        if(secondWordCompleted)
                            break;
                    }
                }
            }
            // Save to list if it's not already there
            if(!isDuplicate(resultsList, fileName))
                resultsList.emplace_back(fileName);
        }
    }
    writeResult(path, resultsList);
}

void util::writeResult(const std::string &path, std::vector<std::string> resultsList)
{
    std::ofstream file;
    file.open(path + "\\generated_names.txt");
    for(const auto & i : resultsList)
    {
        file << i << std::endl;
    }
    file.close();
}

bool util::isDuplicate(std::vector<std::string> vec, const std::string duplicate) {
    for(const auto & current : vec)
    {
        if(current == duplicate)
            return true;
    }
    return false;
}
