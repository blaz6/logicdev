#include <ctime>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <map>
#include "vector"
#include "filesystem"
#include "headers/log.h"
#include "headers/checkFileExistence.h"
#include "headers/definitions.h"
#include "headers/read_env.hpp"

#include "headers/all_commands.h"
#include "Commands/Command.hpp"

#include <dpp/dpp.h>

using std::cout;
using std::string;
namespace fs = std::filesystem;

string BOT_TOKEN;
string Command::name;
string Command::description;

int main(int argc, char *argv[]) {
    fs::path path = __FILE__;
    std::map<std::string, std::string> env_vars = read_dotenv(path.remove_filename().string() + "/../.env");
    for (const auto& [key, value] : env_vars) {
        if(key == "BOT_TOKEN") BOT_TOKEN = value;
    }
    Log log;
    log.setLevel(Log::INFO_LEVEL);

    dpp::cluster client(BOT_TOKEN);

    std::vector<string> files;
    for (const auto &entry : fs::directory_iterator(path.remove_filename().string() + "/Commands")) {
        if (fs::is_regular_file(entry)) continue;
        for (const auto &file : fs::directory_iterator(entry.path())) {
            files.push_back(file.path().filename().string().substr(0, file.path().filename().string().length() - 4));
        }
    }

    client.on_log(dpp::utility::cout_logger());
    client.on_slashcommand([&client](const dpp::slashcommand_t& event) {
        if(event.command.get_command_name() == "ping") {
            Ping::execute(event);
        } else if(event.command.get_command_name() == "register") {
            Register::execute(event);
        }
    });

    client.on_ready([&client](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            Ping p;p.~Ping();
            std::cout << Command::get_name() << " : " << Command::get_description() << std::endl;
            client.global_command_create(dpp::slashcommand(Command::get_name(), Command::get_description(), client.me.id));

            Register r;r.~Register();
            std::cout << Command::get_name() << " : " << Command::get_description() << std::endl;
            client.global_command_create(dpp::slashcommand(Command::get_name(), Command::get_description(), client.me.id));
        }
    });

    client.start(dpp::st_wait);






    std::cin.get();
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
        } else if (!strcmp(argv[i], "a discord bot?")) {
            log.info("Tutor");
            std::cin.get();
            exit(0);
        } else if (!strcmp(argv[i], "time")) {
            while (true) {
                usleep(100000 * 1);
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