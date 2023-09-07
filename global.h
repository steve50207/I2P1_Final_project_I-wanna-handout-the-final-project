#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "algif5/src/algif.h"
// note that you can't assign initial value here!
extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool judge_next_window;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
extern int score;
extern int ch2_score;
extern char score_string[50];
extern char charater2_score_string[50];
extern double ts;
extern double elapsed_time;
extern int game_time;
extern char time_string[50];
extern int speed;
extern int charater2_speed;
extern bool change_direction;
extern bool charater2_change_direction;
extern int changecolor;
extern int window;
extern int select_character;
extern int esc;

#endif
