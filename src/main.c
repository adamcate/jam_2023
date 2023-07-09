#include <stdio.h>
#include <libdragon.h>
#include <math.h>

#include "../include/collision.h"
#include "../include/vec.h"
#include "../include/curve.h"
// #include "../include/globals.h"

static color_t bk_color = {.r = 127, .g = 127, .b = 127, .a = 255};
static const vec2 player_pos_initial = {.x = 160, .y = 120};

#define NUM_BULLETS 10
#define BULLET_VEL_Y 5.f
#define AUTOFIRE_FRAME_COUNT 10
#define AUTOFIRE_RELEASE_DELAY 8

struct bullet_tracker{
    bool player_bullet_enabled[NUM_BULLETS];
    vec2 player_bullet_positions[NUM_BULLETS];
    int on_screen;
    int frame_counter;
} player_bullets;


void draw_player(sprite_t *sprite, vec2 pos){

    rdpq_set_mode_copy(true);
    
    surface_t player_surf = sprite_get_pixels(sprite);

    rdpq_tex_upload_sub(TILE0, &player_surf, &(rdpq_texparms_t){.s.translate = 0.f, .t.translate = 0.f}, 0, 0, 32, 24);

    rdpq_texture_rectangle(TILE0, pos.x, 240 - pos.y, pos.x + 32, 240 - pos.y + 24, 0, 0);
}

void draw_bullets(struct bullet_tracker * bt, struct controller_data * controller, vec2 player_pos){
    
    if(controller->c[0].A && bt->on_screen < NUM_BULLETS && !bt->frame_counter++){

        for(int i = 0; i < NUM_BULLETS; ++i){
            if(!bt->player_bullet_enabled[i]){
                bt->player_bullet_positions[i] = vec2_add(player_pos,(vec2){.x=14});
                bt->player_bullet_enabled[i] = true;

                ++bt->on_screen;

                break;
            }
        }

    } else if(bt->frame_counter > AUTOFIRE_RELEASE_DELAY && !controller->c[0].A ){
        bt->frame_counter = 0;
    }

    rdpq_set_mode_fill((color_t){.r=255,.g=255,.b=255,.a=255});

    for(int i = 0; i < NUM_BULLETS; ++i){
        if(bt->player_bullet_enabled[i]){
            rdpq_fill_rectangle(bt->player_bullet_positions[i].x,240 - bt->player_bullet_positions[i].y,
            bt->player_bullet_positions[i].x + 2, 240 - (bt->player_bullet_positions[i].y) + 2);

            bt->player_bullet_positions[i].y += BULLET_VEL_Y;

            if(bt->player_bullet_positions[i].y > 240){ 
                bt->player_bullet_enabled[i] = false;
                --bt->on_screen;
            }

        }
    }
    if(bt->frame_counter > AUTOFIRE_FRAME_COUNT) bt->frame_counter = 0;
}

void init(){
    memset(player_bullets.player_bullet_positions, 0, sizeof(vec2) * NUM_BULLETS); // initialize test bullet array
    memset(player_bullets.player_bullet_enabled, 0, sizeof(bool) * NUM_BULLETS); // initialize test bullet array
    player_bullets.on_screen = 0;
    player_bullets.frame_counter = 0;

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    rdpq_mode_antialias(false);

    controller_init();
    rdpq_debug_start();

}

int main(void)
{
    init();

    sprite_t *player_sprite = sprite_load("rom:/ship_placeholder.sprite");
    vec2 player_pos = player_pos_initial;

    while(1) {
        surface_t *disp = display_lock();
        if(!disp) continue;

        rdpq_attach(disp, NULL);

        controller_scan();
        struct controller_data controller = get_keys_pressed();
        if(controller.c[0].left) player_pos.x -= 2;
        if(controller.c[0].right) player_pos.x += 2;
        if(controller.c[0].up) player_pos.y += 2;
        if(controller.c[0].down) player_pos.y -= 2;

        rdpq_set_mode_fill(bk_color);
        rdpq_fill_rectangle(0,0,320,240);
        
        draw_player(player_sprite, player_pos);
        draw_bullets(&player_bullets, &controller, player_pos);

        rdpq_detach_show();
    }
}