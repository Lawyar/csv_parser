#include <CSVFile.hpp>

#include <iostream>
#include <cassert>
#include <filesystem>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include<iostream>
using namespace std;

std::string get_current_dir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX);
    string current_working_dir(buff);
    return current_working_dir;
}

int main(int argc, char** argv) {
    std::cout << get_current_dir();

    if (argc != 2) {
        std::cerr << "Error: use filepath as single argument";
        return 0;
    }
    std::filesystem::path fp(argv[1]);
    csv::CSVFile file(fp);
}
