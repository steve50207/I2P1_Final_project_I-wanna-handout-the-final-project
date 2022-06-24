#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 1200;
const int HEIGHT = 900;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
int score = 0;
int ch2_score=0;                    //add
char score_string[50]={'\0'};        //add
char charater2_score_string[50]={'\0'};
double ts = 0;                       //add
double elapsed_time = 0;             //add
int game_time = 0;                   //add
char time_string[50]={'\0'};         //add
int speed = 0;
int charater2_speed=0;                      //add
bool change_direction = false;       //add
bool charater2_change_direction =false;
int changecolor = 0;                 //add
int window = 1;                      //add
int select_character = 0;            //add
int esc = 0;                         //add
