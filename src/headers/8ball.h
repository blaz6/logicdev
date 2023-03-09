#pragma once
#include "Command.h"
#include "dpp/dpp.h"

class Ball : Command {
    public:
    ~Ball();

    static void execute(const dpp::slashcommand_t &event);
};