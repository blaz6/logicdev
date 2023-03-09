#pragma once
#include "Command.h"
#include "dpp/dpp.h"

class Register : Command {
public:
    ~Register();
    static void execute(const dpp::slashcommand_t &event, dpp::cluster &client);
};
