#include "global.h"
#include "charater.h"

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void illustration_init();
void illustration_process(ALLEGRO_EVENT event);
void illustration_draw();
void illustration_destroy();

void select_charater_init();
void select_charater_process(ALLEGRO_EVENT event);
void select_charater_draw();
void select_charater_destroy();

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();

void win_scene_init();
void win_scene_process(ALLEGRO_EVENT event);
void win_scene_draw();
void win_scene_destroy();

void lose_scene_init();
void lose_scene_process(ALLEGRO_EVENT event);
void lose_scene_draw();
void lose_scene_destroy();
