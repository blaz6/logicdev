#include <utility>
#include <iostream>
#include <filesystem>
#include "../headers/Command.h"
#include "string"

namespace fs = std::filesystem;
using std::string;

string Command::name;
string Command::description;

void Command::set_name(string new_name) {
    name = std::move(new_name);
}

void Command::set_description(string new_description) {
    description = std::move(new_description);
}

string Command::get_name() {
    return name;
}

string Command::get_description() {
    return description;
}