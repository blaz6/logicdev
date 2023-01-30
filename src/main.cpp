#include <ctime>

// Discord RPC
#include "discord/discord.h"

#include <csignal>
#include <memory>
#include <iostream>
#include <cstring>
#include "headers/log.h"
#include "headers/checkFileExistence.h"
#include "headers/definitions.h"

using std::cout;
using std::string;

int main(int argc, char *argv[]) {
    Log log;
    log.setLevel(Log::INFO_LEVEL);
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
            discord::Core *core = nullptr;
            discord::Result result = discord::Core::Create(795592654058160148,
                                                           static_cast<uint64_t>(discord::CreateFlags::Default), &core);

            if (result != discord::Result::Ok) {
                std::cout << "Error initializing Discord: " << "\n";
                return 1;
            }
            while (true) {
                discord::Activity activity{};
                activity.SetState("Playing");
                activity.SetDetails("C++");
                core->ActivityManager().UpdateActivity(activity, [&log](discord::Result result) {
                    cout << static_cast<bool>(discord::Result::Ok) << "\n";
                    if (result == discord::Result::Ok) {
                        log.info("Successfully updated activity");
                    } else
                        log.error("Failed to update activity:");
                });
                cout << "updating activity" << "\n";
                usleep(1000000 * 5);
            }

            // });
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