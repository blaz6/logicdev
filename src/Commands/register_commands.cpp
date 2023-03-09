#include "../headers/8ball.h"
#include "../headers/Command.h"
#include "../headers/ping.h"
#include "../headers/register.h"
#include "../headers/log.h"
#include "dpp/dpp.h"
#include "filesystem"
#include "map"
#include "string"

void register_commands(dpp::cluster &client) {
    Log::println("==> Registering Commands");
  if (dpp::run_once<struct register_bot_commands>()) {
    Ping p; p.~Ping();
    std::cout << "\033[1;38;5;200m" << Command::get_name() << "\033[0m"
              << " : "
              << "\033[1;35m" << Command::get_description() << "\033[0m"
              << "\n";
    client.global_command_create(dpp::slashcommand(
        Command::get_name(), Command::get_description(), client.me.id));

    Register r; r.~Register();
    std::cout << "\033[1;38;5;200m" << Command::get_name() << "\033[0m"
              << " : "
              << "\033[1;35m" << Command::get_description() << "\033[0m"
              << "\n";
    client.global_command_create(dpp::slashcommand(
        Command::get_name(), Command::get_description(), client.me.id));

    Ball b; b.~Ball();
    dpp::slashcommand c = dpp::slashcommand(
        Command::get_name(), Command::get_description(), client.me.id);
    c.add_option(dpp::command_option(dpp::command_option_type::co_string,
                                     "vprašanje", "vprašanje", true));

    std::cout << "\033[1;38;5;200m" << Command::get_name() << "\033[0m"
              << " : "
              << "\033[1;35m" << Command::get_description() << "\033[0m"
              << "\n";
    client.global_command_create(c);
  }
}