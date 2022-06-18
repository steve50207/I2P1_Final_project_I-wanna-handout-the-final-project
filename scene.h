#include "global.h"
#include "charater.h"

void opening_init();
void opening_draw();
void opening_destroy();

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void select_charater_init();
void select_charater_process(ALLEGRO_EVENT event);
void select_charater_draw();
void select_charater_destroy();

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();

void win_scene_init();
void win_scene_draw();
void win_scene_destroy();

void lose_scene_init();
void lose_scene_draw();
void lose_scene_destroy();
