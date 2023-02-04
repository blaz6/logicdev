#include "filesystem"
#include "map"
#include "dpp/dpp.h"
#include "string"
#include "../headers/register.h"
#include "../headers/ping.h"
#include "../headers/8ball.h"
#include "../headers/Command.h"

void register_commands(dpp::cluster &client)
{
    if (dpp::run_once<struct register_bot_commands>())
    {
        Ping p; p.~Ping();
        std::cout << Command::get_name() << " : " << Command::get_description() << std::endl;
        client.global_command_create(dpp::slashcommand(Command::get_name(), Command::get_description(), client.me.id));

        Register r; r.~Register();
        std::cout << Command::get_name() << " : " << Command::get_description() << std::endl;
        client.global_command_create(dpp::slashcommand(Command::get_name(), Command::get_description(), client.me.id));

        Ball b; b.~Ball();
        dpp::slashcommand c = dpp::slashcommand(Command::get_name(), Command::get_description(), client.me.id);
        c.add_option(dpp::command_option(dpp::command_option_type::co_string, "vprašanje", "vprašanje"));

        std::cout << Command::get_name() << " : " << Command::get_description() << std::endl;
        client.global_command_create(c);
    }
}