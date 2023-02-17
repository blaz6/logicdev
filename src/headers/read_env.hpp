#pragma once
#include "iostream"
#include "map"
#include "fstream"
#include "sstream"

inline std::map<std::string, std::string> read_dotenv(const std::string& filename) {
    std::ifstream file(filename);
    std::map<std::string, std::string> env_vars;

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::istringstream line_stream(line);
            std::string key, value;
            if (std::getline(line_stream, key, '=')) {
                std::getline(line_stream, value);
                env_vars[key] = value;
            }
        }
        file.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    return env_vars;
}