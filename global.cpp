#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 1200;
const int HEIGHT = 900;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
int score = 0;                       //add
char score_string[50]={'\0'};        //add
double ts = 0;                       //add
double elapsed_time = 0;             //add
int game_time = 0;                   //add
char time_string[50]={'\0'};         //add
