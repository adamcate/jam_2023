#include <stdio.h>
#include <libdragon.h>
#include "../include/collision.h"

int main(void)
{
    console_init();

    debug_init_usblog();
    console_set_debug(true);
    circle_t c1 = {.x = 0, .y = 0, .r = 5}, c2 = {.x = 10, .y = 0, .r = 4};
    printf("Does circle collide? %i\n", (int)circle_overlaps(c1, c2));

    while(1) {}
}