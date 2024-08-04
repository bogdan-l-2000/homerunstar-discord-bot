#include "homerunstarBot.h"
#include <iostream>
#include <dpp/dpp.h>


using namespace std;

 
int main(int argc, char *argv[]) {
    dpp::cluster bot(BOT_TOKEN);
 
    bot.on_log(dpp::utility::cout_logger());
 
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ig") {
            event.reply(INSTAGRAM_URL);
        } else if (event.command.get_command_name() == "yt") {
            event.reply(YOUTUBE_URL);
        } else if (event.command.get_command_name() == "sc") {
            event.reply(SOUNDCLOUD_URL);
        } else if (event.command.get_command_name() == "join") {
            dpp::guild* g = dpp::find_guild(event.command.guild_id);
            
            auto current_vc = event.from->get_voice(event.command.guild_id);

            bool join_vc = true;

            if (current_vc) {
                auto users_vc = g->voice_members.find(event.command.get_issuing_user().id);

                if (users_vc != g->voice_members.end() && current_vc->channel_id == users_vc->second.channel_id) {
                    join_vc = false;
                } else {
                    event.from->disconnect_voice(event.command.guild_id);

                    join_vc = true;
                }
            }

            if (join_vc) {
                if (!g->connect_member_voice(event.command.get_issuing_user().id)) {
                    event.reply("You don't seem to be in a voice channel.");
                    return;
                }
                event.reply("Joined the channel!");
            } else {
                event.reply("Already joined the channel!");
            }
        } else if (event.command.get_command_name() == "leave") {
            event.from->disconnect_voice(event.command.guild_id);
            event.reply("Left the channel! See you next time.");
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
            bot.global_command_create(dpp::slashcommand("join", "Joins your voice channel.", bot.me.id));
            bot.global_command_create(dpp::slashcommand("leave", "Leaves your voice channel.", bot.me.id));
            cout << "Commands created!" << endl;
        }
        cout << "Bot is ready!" << endl;
    });
 
    bot.start(dpp::st_wait);
}