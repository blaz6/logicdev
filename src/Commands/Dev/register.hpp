#pragma once
#include "../Command.hpp"
#include <dpp/dpp.h>
#include "../register_commands.hpp"

class Register : Command {
    public:
    ~Register() {
        set_name("register");
        set_description("registers commands");
    }

    static void execute(const dpp::slashcommand_t& event) {
        //registerCommands(client);
        dpp::embed embed = dpp::embed()
                    .set_color(dpp::colors::blue_aquamarine)
                    .set_title("registered commands")
                    .set_description("This should work")
                    .set_timestamp(time(nullptr));

        event.reply(dpp::message(event.command.channel_id, embed));
    }
};
