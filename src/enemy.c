#include "../include/enemy.h"
#include "../include/collision.h"


void disable_enemy(enemy *instance, game_state *state){
    instance->enabled = false;
    instance->frame_timer = 0;
}

void update_enemy(enemy *instance, game_state *state){
    if(!instance->enabled) return;
    
    instance->frame_timer++;

    switch(instance->type){
        case ENEMY_PLACEHOLDER:
            instance->root_position = vec2_sub(instance->root_position, (vec2){.y=2}); // move enemy down screen
            circle_t enemy_collider = instance->enemy_data.placeholder_data.collider;
            enemy_collider.x = instance->root_position.x;
            enemy_collider.y = instance->root_position.y;

            if(instance->root_position.y <= 0) {
                disable_enemy(instance, state);
                return;
            }
            for(int i = 0; i < MAX_PLAYER_BULLETS; ++i){
                if(!state->player_bullets[i].enabled) continue;
                if(circle_overlaps(enemy_collider,(circle_t){.r=state->player_bullets[i].collider.r,.x=state->player_bullets[i].position.x, .y=state->player_bullets[i].position.y})){
                    disable_enemy(instance, state);
                    return;
                }
            } 
            break;
        default:
            return;
    }
}