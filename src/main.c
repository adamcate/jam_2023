#include <stdio.h>
#include <libdragon.h>
#include <math.h>

#include "../include/collision.h"
#include "../include/vec.h"
#include "../include/curve.h"
#include "../include/enemy.h"
// #include "../include/globals.h"

static uint32_t rand_state = 1;
static uint32_t rand(void) {
	uint32_t x = rand_state;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 5;
	return rand_state = x;
}

// RANDN(n): generate a random number from 0 to n-1
#define RANDN(n) ({ \
	__builtin_constant_p((n)) ? \
		(rand()%(n)) : \
		(uint32_t)(((uint64_t)rand() * (n)) >> 32); \
})

static color_t bk_color = {.r = 127, .g = 127, .b = 127, .a = 255};
static const vec2 player_pos_initial = {.x = 160, .y = 120};

#define NUM_BULLETS 20
#define NUM_ENEMIES 100
#define ENEMY_PLACEHOLDER_HEALTH 1
#define ENEMY_PLACEHOLDER_RAD 10
#define ENEMY_PLACEHOLDER_MAX_COUNT 100
#define ENEMY_PLACEHOLDER_FRAME_COUNT 2
#define ENEMY_PLACEHOLDER_VEL_Y 1

#define BULLET_VEL_Y 2.5f
#define AUTOFIRE_FRAME_COUNT 2
#define AUTOFIRE_RELEASE_DELAY 2

struct bullet_tracker{
    bool player_bullet_enabled[NUM_BULLETS];
    vec2 player_bullet_positions[NUM_BULLETS];
    int on_screen;
    int frame_counter;
} player_bullets;

struct enemy_tracker_s{
    enemy enemies[NUM_ENEMIES];
    int on_screen;
    int frame_counter;
} enemy_tracker;


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

void draw_temp_enemies(struct enemy_tracker_s * e_tracker, struct bullet_tracker *b_tracker){
    bool enemy_added = false;

    rdpq_set_mode_fill((color_t){.r=255,.a=255});

    
    for(int i = 0; i < ENEMY_PLACEHOLDER_MAX_COUNT; ++i){
        if(!e_tracker->enemies[i].enabled && !enemy_added && e_tracker->frame_counter == ENEMY_PLACEHOLDER_FRAME_COUNT){

            e_tracker->enemies[i].root_position = (vec2){.x=RANDN(300),.y=230-RANDN(30)};
            e_tracker->enemies[i].enabled = true;
            e_tracker->on_screen++;
            enemy_added = true;
        }
        if(e_tracker->enemies[i].enabled){
            e_tracker->enemies[i].root_position.y -= ENEMY_PLACEHOLDER_VEL_Y;

            rdpq_fill_rectangle(e_tracker->enemies[i].root_position.x, 240 - e_tracker->enemies[i].root_position.y,
            e_tracker->enemies[i].root_position.x + 2 * ENEMY_PLACEHOLDER_RAD, 240 - e_tracker->enemies[i].root_position.y + 2 * ENEMY_PLACEHOLDER_RAD);
            if(e_tracker->enemies[i].root_position.y <= 0) {
                e_tracker->enemies[i].enabled = false;
                e_tracker->on_screen--;
            }
        }

    }
    
    for(int i = 0; i < NUM_BULLETS; ++i){
        if(!b_tracker->player_bullet_enabled[i]) continue;

        for(int j = 0; j < ENEMY_PLACEHOLDER_MAX_COUNT; ++j){
            if(!e_tracker->enemies[j].enabled) continue;

            if(circle_overlaps((circle_t){.r=ENEMY_PLACEHOLDER_RAD, .x = e_tracker->enemies[j].root_position.x + ENEMY_PLACEHOLDER_RAD, 
                .y = e_tracker->enemies[j].root_position.y - ENEMY_PLACEHOLDER_RAD}, 
                (circle_t){.r=2,.x=b_tracker->player_bullet_positions[i].x+2,.y=b_tracker->player_bullet_positions[i].y-2}))
                {
                    e_tracker->enemies[j].enabled = false;
                    b_tracker->player_bullet_enabled[i] = false;
                    b_tracker->on_screen--;
                    e_tracker->on_screen--;
                    break;
                }
        }
    }

    if(e_tracker->frame_counter == ENEMY_PLACEHOLDER_FRAME_COUNT)    e_tracker->frame_counter = 0;
    
    e_tracker->frame_counter++;
}

void init(){
    memset(player_bullets.player_bullet_positions, 0, sizeof(vec2) * NUM_BULLETS); // initialize test bullet array
    memset(player_bullets.player_bullet_enabled, 0, sizeof(bool) * NUM_BULLETS); // initialize test bullet array
    enemy_tracker = (struct enemy_tracker_s){.frame_counter = 0, .on_screen = 0};
    
    enemy template_enemy = {.enabled = false, .root_position = (vec2){0,0}, .type=ENEMY_PLACEHOLDER, 
    .enemy_data.placeholder_data.collider=(circle_t){.r=ENEMY_PLACEHOLDER_RAD}};
    
    for(int i = 0; i < NUM_ENEMIES; ++i)
        enemy_tracker.enemies[i] = template_enemy;

    player_bullets.on_screen = 0;
    player_bullets.frame_counter = 0;

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    rdpq_mode_antialias(false);

    controller_init();
    rdpq_debug_start();
    debug_init(DEBUG_FEATURE_ALL);

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
        draw_temp_enemies(&enemy_tracker, &player_bullets);
        debugf("bullets: %i, enemies: %i \n", player_bullets.on_screen, enemy_tracker.on_screen);
        rdpq_detach_show();
    }
}