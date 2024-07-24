#include <mpv/client.h>
#include <ncurses.h>

#include "utils/mainwindow.h"
#include "widgets/selectmenu.h"
#include "widgets/playerbox.h"

int main()
{
    struct mainwindow main = main_init();
    struct selectmenu menu = menu_create(0, 0, main.height - 3, main.width - 1, "Stations");
    struct playerbox player = player_create(menu.y + menu.height, 0, main.width - 1);

    menu_add(&menu, "Code Radio", "https://coderadio-admin-v2.freecodecamp.org/listen/coderadio/radio.mp3");
    menu_add(&menu, "Chillofi", "http://streams.dez.ovh:8000/radio.mp3");
    menu_focus(&menu);

    while (true)
    {
        int in = getch();

        if (in == 'q')
        {
            break;
        }

        struct selectitem *item = menu_update(&menu, in);

        if (item != NULL)
        {
            player_play(&player, item);
        }

        player_update(&player, in);
    }

    return main_close();
}
