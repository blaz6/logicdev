#pragma once
#include "string"

using std::string;

class Command {
private:
    static string name;
    static string description;

public:
    static void set_name(string new_name);

    static void set_description(string new_description);

    static string get_name();

    static string get_description();
};