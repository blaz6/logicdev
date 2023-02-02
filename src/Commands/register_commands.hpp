#pragma once
#include "dpp/dpp.h"
#include "../headers/all_commands.h"
#include "filesystem"
#include "map"
#include "Command.hpp"
#include "Dev/register.hpp"

//void registerCommands(dpp::cluster client) {
//    std::vector<std::string> files;
//    fs::path path = __FILE__;
//    for (const auto &entry : fs::directory_iterator(path.remove_filename().string() + "/Commands")) {
//        if (fs::is_regular_file(entry)) continue;
//        for (const auto &file : fs::directory_iterator(entry.path())) {
//            files.push_back(file.path().filename().string().substr(0, file.path().filename().string().length() - 4));
//        }
//    }
//
//    Ping p;p.~Ping();
//    std::cout << Command::get_name() << " : " << Command::get_description() << std::endl;
//    client.global_command_create(dpp::slashcommand(Command::get_name(), Command::get_description(), client.me.id));
//
//    Register r;r.~Register();
//    std::cout << Command::get_name() << " : " << Command::get_description() << std::endl;
//    client.global_command_create(dpp::slashcommand(Command::get_name(), Command::get_description(), client.me.id));
//}