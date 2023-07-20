#include <stdio.h>
#include <libdragon.h>
#include <math.h>

#include "../include/collision.h"
#include "../include/vec.h"
#include "../include/curve.h"
#include "../include/enemy.h"
#include "../include/game.h"
// #include "../include/globals.h"
#include "../include/game_constants.h"

static game_state global_state;

static color_t bk_color = {.r = 255, .g = 255, .b = 255, .a = 255};

void draw_player(sprite_t *sprite, vec2 pos){

    rdpq_set_mode_copy(true);
    
    surface_t player_surf = sprite_get_pixels(sprite);

    rdpq_tex_upload_sub(TILE0, &player_surf, &(rdpq_texparms_t){.s.translate = 0.f, .t.translate = 0.f}, 0, 0, 30, 25);

    rdpq_texture_rectangle(TILE0, pos.x, pos.y, pos.x + 30, pos.y + 25, 0, 0);
}

void init(){

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    rdpq_mode_antialias(false);

    controller_init();

    global_state.initialized = false;
    game_state_init(&global_state); // initialize the global game state info & memory

    rdpq_debug_start();
    debug_init(DEBUG_FEATURE_ALL);

}

int main(void)
{
    init();

    sprite_t *player_sprite = sprite_load("rom:/ship_placeholder.sprite");

    while(1) {
        surface_t *disp = display_lock();
        if(!disp) continue;

        rdpq_attach(disp, NULL);

        controller_scan();
        SI_controllers_state_t controller = get_keys_pressed();
        
        rdpq_set_mode_fill(bk_color);
        rdpq_fill_rectangle(0,0,320,240);

        game_state_tick(&global_state, &controller);

        draw_player(player_sprite, global_state.player_pos);
        
        rdpq_detach_show();
    }
}