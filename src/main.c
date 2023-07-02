#include <stdio.h>
#include <libdragon.h>

float player_x = 0, player_y = 0;

int main(void)
{
    console_init();

    debug_init_usblog();
    console_set_debug(true);

    printf("Hello world!\n");

    while(1) {}
}