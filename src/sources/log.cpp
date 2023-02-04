#include <iostream>
#include "../headers/log.h"

using std::string;

Log::Level Log::m_logLevel;
const string Log::RESET = "\033[0m";
const string Log::YELLOW = "\033[1;33m";
const string Log::GREEN = "\033[1;32m";
const string Log::BLUE = "\033[1;34m";
const string Log::RED = "\033[1;31m";
const string Log::CYAN = "\033[1;36m";

void Log::setLevel(Log::Level level) {
    m_logLevel = level;
}

void Log::warn(string warn) {
    if (m_logLevel >= WARNING_LEVEL)
        std::cout << YELLOW << "[WARNING] \t" << warn << RESET << "\n";
}

void Log::error(string error) {
    if (m_logLevel >= ERROR_LEVEL)
        std::cout << RED << "[ERROR] \t" << error << RESET << "\n";
}

void Log::info(string info) {
    if (m_logLevel >= INFO_LEVEL) 
        std::cout << CYAN << "[INFO] \t" << info << RESET << "\n";
}

void Log::println(string normal_string) {
    std::cout << BLUE << normal_string << RESET << "\n";
}