#include "charater.h"

// the state of character
enum {STOP = 0, MOVE};
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;
Character chara;
ALLEGRO_SAMPLE *sample = NULL;
void character_init(){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/character01/char01_move%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
    }

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = (int)rand()%1200;
    chara.y = (int)rand()%900;
    chara.dir = false;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;

}
void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        chara.y -= 5;
        //character_xposition=chara.x;
        //character_yposition=chara.y;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_A] ){
        chara.dir = false;
        chara.x -= 5;
        //character_xposition=chara.x;
        //character_yposition=chara.y;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        chara.y += 5;
        //character_xposition=chara.x;
        //character_yposition=chara.y;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        chara.dir = true;
        chara.x += 5;
        //character_xposition=chara.x;
        //character_yposition=chara.y;
        chara.state = MOVE;
    }else if( chara.anime == chara.anime_time-1 ){
        chara.anime = 0;
        chara.state = STOP;
    }else if ( chara.anime == 0 ){
        chara.state = STOP;
    }
}
void character_draw(){
    // with the state, draw corresponding image
    if( chara.state == STOP ){
        if( chara.dir )
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
    }else if( chara.state == MOVE ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }
        }
    }
}
void character_destory(){
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
}
