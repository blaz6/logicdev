#pragma once
#include "Command.h"
#include "dpp/dpp.h"

class Ping : Command {
    public:
    ~Ping();

    static void execute(const dpp::slashcommand_t &event);
};