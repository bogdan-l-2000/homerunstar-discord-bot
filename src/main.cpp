#include "homerunstarBot.h"
#include <iostream>
#include <dpp/dpp.h>


using namespace std;

 
int main(int argc, char *argv[]) {
    dpp::cluster bot(BOT_TOKEN);
 
    bot.on_log(dpp::utility::cout_logger());
 
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        cout << event.command.get_command_name() << endl;
        if (event.command.get_command_name() == "ig") {
            event.reply(INSTAGRAM_URL);
        } else if (event.command.get_command_name() == "yt") {
            event.reply(YOUTUBE_URL);
        } else if (event.command.get_command_name() == "sc") {
            event.reply(SOUNDCLOUD_URL);
        }
    });
 
    bot.on_ready([&bot, &argc, &argv](const dpp::ready_t& event) {
        if (argc == 2 && strncmp(argv[1], "delete", min(static_cast<int>(strlen(argv[1])), 6)) == 0) {
            /* Now, we're going to wipe our commands */
            bot.global_bulk_command_delete();
            cout << "Commands deleted!" << endl;
        }
        if (argc == 2 && strncmp(argv[1], "create", min(static_cast<int>(strlen(argv[1])), 6)) == 0) {
            bot.global_command_create(dpp::slashcommand("ig", "Instagram URL", bot.me.id));
            bot.global_command_create(dpp::slashcommand("yt", "YouTube URL", bot.me.id));
            bot.global_command_create(dpp::slashcommand("sc", "Soundcloud URL", bot.me.id));
            cout << "Commands created!" << endl;
        }
        cout << "Bot is ready!" << endl;
    });
 
    bot.start(dpp::st_wait);
}