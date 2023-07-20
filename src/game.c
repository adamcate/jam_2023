#include "../include/game.h"
#include "../include/game_constants.h"

static void game_state_mempool_free(game_state *state){
    mem_zone_free_all(&state->enemy_bullet_pool);
    mem_zone_free_all(&state->enemy_data_pool);
}


void game_state_reset(game_state *state){
    state->curr_screen = GAME_STATE_MAIN_MENU;

    state->score = 0;
    state->stage_number = 0;
    state->lives = initial_lives;
    state->continues = num_continues;

    state->player_pos = player_initial_pos;
    memset(state->player_bullets, 0, sizeof(bullet) * MAX_PLAYER_BULLETS);
    
    game_state_mempool_free(state);
}

void game_state_init(game_state *state){
    assertf(!state->initialized, "ERROR: tried to initalize game state twice\n");
    
    state->initialized = true;
    state->curr_screen = GAME_STATE_STARTUP;

    state->score = 0;
    state->stage_number = 0;
    state->lives = initial_lives;
    state->continues = num_continues;

    state->player_pos = player_initial_pos;
    memset(state->player_bullets, 0, sizeof(bullet) * MAX_PLAYER_BULLETS);

    mem_zone_init(&state->enemy_bullet_pool, enemy_bullet_pool_size);
    mem_zone_init(&state->enemy_data_pool, enemy_data_pool_size);
}

void game_state_tick(game_state *state, SI_controllers_state_t *controller){
    vec2 dir = {
        .x=((int)controller->c[0].right-(int)controller->c[0].left),
        .y=((int)controller->c[0].up-(int)controller->c[0].down)
    };

    state->player_vel = vec2_mult_coeff(dir, player_mov_vel);
    state->player_pos = vec2_add(state->player_pos, state->player_vel);
}