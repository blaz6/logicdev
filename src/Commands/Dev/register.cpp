#include "dpp/dpp.h"
#include "../../headers/register_commands.h"
#include "../../headers/register.h"

Register::~Register() {
    set_name("register");
    set_description("registers commands");
}

void Register::execute(const dpp::slashcommand_t &event, dpp::cluster &client) {
    register_commands(client);
    dpp::embed embed = dpp::embed().set_color(0x213482).set_title(
            "registered commands").set_description("\n").set_timestamp(time(nullptr));

    event.reply(dpp::message(event.command.channel_id, embed));
}
