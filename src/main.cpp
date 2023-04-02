#include "filesystem"
#include "headers/checkFileExistence.h"
#include "headers/definitions.h"
#include "headers/log.h"
#include "headers/read_env.hpp"
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <unistd.h>
#include "headers/crow_all.h"

using std::cout;
using std::map;
using std::string;

int main(int argc, char *argv[]) {
  Log::setLevel(Log::INFO_LEVEL);
  std::filesystem::path path(__FILE__);
  map<string, string> env_vars = read_dotenv(path.remove_filename().string() + "../.env");
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
    } else if (!strcmp(argv[i], "time")) {
      while (true) {
        usleep(100000 * 1);
        std::time_t result = std::time(nullptr);
        cout << std::asctime(std::localtime(&result)) << "\n";
      }
      exit(0);
    } else if (!strcmp(argv[i], "http")) {
        string PORT = env_vars["PORT"];
        std::stringstream ss(PORT);
        int port;
        ss >> port;

        crow::SimpleApp app;
        app.loglevel(crow::LogLevel::Warning);
        CROW_ROUTE(app, "/")([](){
            return "Hello worl";
        });
        app.port(port).multithreaded().run();
    }
  }

  /** This is the main program if no arguments are provided */
  Log::println((string) "Usage: " + EXECUTABLE_NAME + " [options]");
  cout << "\n";
  Log::println("==> Options:");
  Log::println("   self-uninstall - uninstalls the program");
  Log::println("   hlw - Prints Hello World!");
  Log::println("   time - Displays time");
  Log::println("   http - start http server");
}