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
extern int score;               //add
extern char score_string[50];   //add
extern double ts;               //add
extern double elapsed_time;     //add
extern int game_time;           //add
extern char time_string[50];    //add
extern int speed;               //add
extern bool change_direction;   //add
extern int changecolor;         //add
extern int window;              //add
extern int select_character;    //add
extern int esc;                 //add

#endif
