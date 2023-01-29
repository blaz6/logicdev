#include "iostream"
#include "headers/log.h"
#include "headers/checkFileExistence.h"
#include "cstring"
#define EXECUTABLE_NAME "HelloWorld"

using std::cout;
using std::string;

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "self-uninstall") == 0) {
            log("==> Uninstalling...");
            if (!fileExists((string)("/usr/bin/") + EXECUTABLE_NAME)) {
                log("==> Program is not installed on this system. Exiting...");
                exit(0);
            }
            system(((string)("sudo rm /usr/bin/") + EXECUTABLE_NAME).c_str());
            log("==> Successfully uninstalled!");
            exit(0);
        }
    }

    /** This is the main program if no arguments are provided */
    log(((string)"Usage: " + EXECUTABLE_NAME + " [options]").c_str());
    cout << "\n";
    log("Options:");
    log("self-uninstall - uninstalls the program");
}