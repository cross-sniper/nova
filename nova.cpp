#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <iterator>
#include <filesystem>
#include <chrono>

using namespace std;

bool hasChanged(const std::string& filename, const std::string& executable) {
    try {
        filesystem::file_time_type sourceTime = filesystem::last_write_time(filename);
        filesystem::file_time_type executableTime = filesystem::last_write_time(executable);
        return sourceTime > executableTime;
    } catch (filesystem::__cxx11::filesystem_error) {
        // Check which file is missing and print an error message
        if (!filesystem::exists(filename)) {

            cout << "\033[38;2;255;0;0mError:\033[39m Source file '" << filename << "' is missing." << endl;
            exit(1);
        } else {

            //dont show anything, since this is the case where the executable is not found
        }
        return true;
    }
}

void build(string source, vector<string> flags, vector<string> libs, string output) {
    // Construct the compile command
    if (not hasChanged(source, output)) {
        std::cout << "executable is up to date, not building: " << output << std::endl;
        return;
    }
    string compileCommand = "g++ " + source;

    // Add compilation flags
    for (const string& flag : flags) {
        compileCommand += " " + flag;
    }

    // Add library dependencies
    for (const string& lib : libs) {
        compileCommand += " -l" + lib;
    }

    // Specify the output file
    compileCommand += " -o " + output;

    //make it stripped
    compileCommand += "; strip " + output;

    // Execute the compile command
    int result = system(compileCommand.c_str());

    // Check if the compilation was successful
    if (result == 0) {
        cout << "Build successful. Executable created: " << output << endl;
    } else {
        cerr << "Build failed." << endl;
    }
}


int main() {
    // Nova(the compiler)'s build process
    string sourceFile = "nova.cpp";
    vector<string> novaCompilationFlags = {"-Os", "-static"};
    vector<string> novaLibraries = {};
    string novaOutputFile = "nova";

    build(sourceFile, novaCompilationFlags, novaLibraries, novaOutputFile);

    // The actual app
    string source = "main.cpp";
    vector<string> mainCompilationFlags = {"-Os"};
    vector<string> mainLibraries = {"ncurses"};
    string mainOutputFile = "main";
    build(source, mainCompilationFlags, mainLibraries, mainOutputFile);

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <iterator>
#include <filesystem>
#include <chrono>

using namespace std;

bool hasChanged(const std::string& filename, const std::string& executable) {
    try {
        filesystem::file_time_type sourceTime = filesystem::last_write_time(filename);
        filesystem::file_time_type executableTime = filesystem::last_write_time(executable);
        return sourceTime > executableTime;
    } catch (filesystem::__cxx11::filesystem_error) {
        // Check which file is missing and print an error message
        if (!filesystem::exists(filename)) {

            cout << "\033[38;2;255;0;0mError:\033[39m Source file '" << filename << "' is missing." << endl;
            exit(1);
        } else {

            //dont show anything, since this is the case where the executable is not found
        }
        return true;
    }
}

void build(string source, vector<string> flags, vector<string> libs, string output) {
    // Construct the compile command
    if (not hasChanged(source, output)) {
        std::cout << "executable is up to date, not building: " << output << std::endl;
        return;
    }
    string compileCommand = "g++ " + source;

    // Add compilation flags
    for (const string& flag : flags) {
        compileCommand += " " + flag;
    }

    // Add library dependencies
    for (const string& lib : libs) {
        compileCommand += " -l" + lib;
    }

    // Specify the output file
    compileCommand += " -o " + output;

    //make it stripped
    compileCommand += "; strip " + output;

    // Execute the compile command
    int result = system(compileCommand.c_str());

    // Check if the compilation was successful
    if (result == 0) {
        cout << "Build successful. Executable created: " << output << endl;
    } else {
        cerr << "Build failed." << endl;
    }
}


int main() {
    // Nova(the compiler)'s build process
    string sourceFile = "nova.cpp";
    vector<string> novaCompilationFlags = {"-Os", "-static"};
    vector<string> novaLibraries = {};
    string novaOutputFile = "nova";

    build(sourceFile, novaCompilationFlags, novaLibraries, novaOutputFile);

    // The actual app
    string source = "main.cpp";
    vector<string> mainCompilationFlags = {"-Os"};
    vector<string> mainLibraries = {"ncurses"};
    string mainOutputFile = "main";
    build(source, mainCompilationFlags, mainLibraries, mainOutputFile);

    return 0;
}
