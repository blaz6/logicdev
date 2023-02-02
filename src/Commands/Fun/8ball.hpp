#pragma once
#include "../Command.hpp"
#include <dpp/dpp.h>

class Ball : Command {
    public:
    ~Ball() {
        set_name("8ball");
        set_description("pokaže prihodnost");
    }

    static void execute(const dpp::slashcommand_t& event) {
        dpp::embed embed = dpp::embed()
                    .set_color(dpp::colors::blue_aquamarine)
                    .set_title("text")
                    .set_description("This should work")
                    .set_timestamp(time(nullptr));

        event.reply(dpp::message(event.command.channel_id, embed));
    }
};
