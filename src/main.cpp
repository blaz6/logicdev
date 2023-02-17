#include "filesystem"
#include "headers/8ball.h"
#include "headers/checkFileExistence.h"
#include "headers/definitions.h"
#include "headers/log.h"
#include "headers/ping.h"
#include "headers/read_env.hpp"
#include "headers/register.h"
#include "vector"
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <unistd.h>
#include <dpp/dpp.h>
#include "headers/crow_all.h"

using std::cout;
using std::map;
using std::string;
namespace fs = std::filesystem;

string BOT_TOKEN;

int main(int argc, char *argv[]) {
  Log::setLevel(Log::INFO_LEVEL);
  fs::path path = __FILE__;
  map<string, string> env_vars =
      read_dotenv(path.remove_filename().string() + "../.env");
  for (int i = 0; i < argc; ++i) {
    if (!strcmp(argv[i], "self-uninstall")) {
      Log::println("==> Uninstalling...");
      if (!fileExists((string)("/usr/bin/") + EXECUTABLE_NAME)) {
        Log::error("Program is not installed on this system. Exiting...");
        exit(1);
      }
      system(((string)("sudo rm /usr/bin/") + EXECUTABLE_NAME).c_str());
      Log::println("==> Successfully uninstalled!");
      exit(0);
    } else if (!strcmp(argv[i], "hlw")) {
      Log::println("Hello World!");
      exit(0);
    } else if (!strcmp(argv[i], "start")) {
      BOT_TOKEN = env_vars["BOT_TOKEN"];
      Log::info("Starting Byte...");
      dpp::cluster client(BOT_TOKEN);
      std::vector<string> files;
      Log::println("==> Getting Commands");
      for (const fs::directory_entry &entry : fs::directory_iterator(
               path.remove_filename().string() + "/Commands")) {
        if (fs::is_regular_file(entry))
          continue;
        for (const auto &file : fs::directory_iterator(entry.path())) {
          files.push_back(file.path().filename().string().substr(
              0, file.path().filename().string().length() - 4));
          cout << "\033[1;32m"
               << " - "
               << file.path().filename().string().substr(
                      0, file.path().filename().string().length() - 4)
               << "\033[0m"
               << "\n";
        }
      }
      // client.on_log(dpp::utility::cout_logger());
      client.on_slashcommand([&client](const dpp::slashcommand_t &event) {
        std::string command_name = event.command.get_command_name();
        if (command_name == "ping") {
          Ping::execute(event);
        } else if (command_name == "register") {
          Register::execute(event, client);
        } else if (command_name == "8ball") {
          Ball::execute(event);
        }
      });
      client.on_ready([&client](const dpp::ready_t &event) {
        Log::info("Byte has been initialized!");
      });
      client.start(dpp::st_wait);
      exit(0);
    } else if (!strcmp(argv[i], "time")) {
      while (true) {
        usleep(100000 * 1);
        std::time_t result = std::time(nullptr);
        cout << std::asctime(std::localtime(&result)) << "\n";
      }
      exit(0);
    } else if (!strcmp(argv[i], "http")) {
        crow::SimpleApp app;
        app.loglevel(crow::LogLevel::Warning);
        CROW_ROUTE(app, "/")([](){
            return "Hello world";
        });
        app.port(8080).multithreaded().run();
    }
  }

  /** This is the main program if no arguments are provided */
  Log::println((string) "Usage: " + EXECUTABLE_NAME + " [options]");
  cout << "\n";
  Log::println("==> Options:");
  Log::println("   self-uninstall - uninstalls the program");
  Log::println("   hlw - Prints Hello World!");
  Log::println("   time - Displays time");
  Log::println("   start - start Byte");
  Log::println("   start - start http server");
}