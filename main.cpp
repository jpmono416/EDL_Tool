#include <iostream>
#include <vector>
#include <regex>
#include "util.h"


/**
 * Tool created and owned by Jonathan Perez. For any queries contact jonathanperez.11.02.98@gmail.com
 * Commercial use granted to Framestore as an automation tool for their business.
 */
int main()
{
    std::vector<std::string> resultsList;
    std::string dirPath;

    std::cout << "This tool is used to extract all the unique tape names from a series of .edl files." << std::endl;
    std::cout << "Please paste below the absolute path to the directory containing the files." << std::endl << std::endl;
    std::cout << "Please enter the directory path:" << std::endl;
    std::cin >> dirPath;

    util utilObject;
    utilObject.processDir(dirPath);

    std::cout << "A file named 'generated_names.txt' has appeared on the given directory.";
    return 0;
}
