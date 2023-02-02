#pragma once
#include "../Command.hpp"
#include <dpp/dpp.h>

class Ping : Command {
    public:
    ~Ping() {
        set_name("ping");
        set_description("Pings the server.");
    }

    static void execute(const dpp::slashcommand_t& event) {
        dpp::embed embed = dpp::embed()
                    .set_color(dpp::colors::blue_aquamarine)
                    .set_title("This is the answer to the ping command")
                    .set_description("This should work")
                    .set_timestamp(time(nullptr));

        event.reply(dpp::message(event.command.channel_id, embed));
    }
};
