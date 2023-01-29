#include <ctime>
#include <csignal>
#include <iostream>
#include <cstring>
#include "headers/log.h"
#include "headers/checkFileExistence.h"
#define EXECUTABLE_NAME "HelloWorld"

using std::cout;
using std::string;

int main(int argc, char *argv[]) {
    Log log;
    log.setLevel(Log::WARNING_LEVEL);
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "self-uninstall")) {
            log.println("==> Uninstalling...");
            if (!fileExists((string) ("/usr/bin/") + EXECUTABLE_NAME)) {
                log.error("==> Program is not installed on this system. Exiting...");
                exit(0);
            }
            system(((string) ("sudo rm /usr/bin/") + EXECUTABLE_NAME).c_str());
            log.println("==> Successfully uninstalled!");
            exit(0);
        } else if (!strcmp(argv[i], "hlw")) {
            log.println("Hello World!");
            exit(0);
        } else if (!strcmp(argv[i], "tut")) {
            log.info("Tutor");
            std::cin.get();
            exit(0);
        } else if (!strcmp(argv[i], "time")) {
            while (true) {
                usleep(1000000);
                std::time_t result = std::time(nullptr);
                cout << std::asctime(std::localtime(&result)) << "\n";
            }
            exit(0);
        }
    }

    /** This is the main program if no arguments are provided */
    log.println(((string) "Usage: " + EXECUTABLE_NAME + " [options]").c_str());
    cout << "\n";
    log.println("==> Options:");
    log.println("   self-uninstall - uninstalls the program");
    log.println("   hlw - Prints Hello World!");
    log.println("   time - Displays time");
    log.println("   tut - Tutorial");
}