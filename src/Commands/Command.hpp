#pragma once
#include <utility>

#include "dpp/dpp.h"
#include "filesystem"

namespace fs = std::filesystem;
using std::string;

class Command {
private:
   static string name;
   static string description;
public:
    static void set_name(string new_name) {
        name = std::move(new_name);
    }
    static void set_description(string new_description) {
        description = std::move(new_description);
    }

    static string get_name() {
        return name;
    }

    static string get_description() {
        return description;
    }
};