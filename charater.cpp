#include "charater.h"

// the state of character
enum {STOP = 0, MOVE};
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int dir[4]; // down: 0, left: 1, up: 2, right: 3
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[8];
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;
Character chara;
ALLEGRO_SAMPLE *sample = NULL;
void character_init(){
    // load character images
    for(int i = 1 ; i <= 8 ; i++){
        char temp[50];
        sprintf( temp, "./image/character01/char01_move%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
    }

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = (int)rand()%1200;
    chara.y = (int)rand()%900;
    chara.dir[0] = 1;
    chara.dir[1] = 0;
    chara.dir[2] = 0;
    chara.dir[3] = 0;

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
        chara.dir[0] = 0;
        chara.dir[1] = 0;
        chara.dir[2] = 1;
        chara.dir[3] = 0;
        chara.y -= 5;
        //character_xposition=chara.x;
        //character_yposition=chara.y;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_A] ){
        chara.dir[0] = 0;
        chara.dir[1] = 1;
        chara.dir[2] = 0;
        chara.dir[3] = 0;
        chara.x -= 5;
        //character_xposition=chara.x;
        //character_yposition=chara.y;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        chara.dir[0] = 1;
        chara.dir[1] = 0;
        chara.dir[2] = 0;
        chara.dir[3] = 0;
        chara.y += 5;
        //character_xposition=chara.x;
        //character_yposition=chara.y;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        chara.dir[0] = 0;
        chara.dir[1] = 0;
        chara.dir[2] = 0;
        chara.dir[3] = 1;
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
        if( chara.dir[0]==1 &&  chara.dir[1]==0 && chara.dir[2]==0 && chara.dir[3]==0)
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
        else if( chara.dir[0]==0 &&  chara.dir[1]==1 && chara.dir[2]==0 && chara.dir[3]==0)
            al_draw_bitmap(chara.img_move[2], chara.x, chara.y, 0);
        else if( chara.dir[0]==0 &&  chara.dir[1]==0 && chara.dir[2]==1 && chara.dir[3]==0)
            al_draw_bitmap(chara.img_move[4], chara.x, chara.y, 0);
        else if( chara.dir[0]==0 &&  chara.dir[1]==0 && chara.dir[2]==0 && chara.dir[3]==1)
            al_draw_bitmap(chara.img_move[6], chara.x, chara.y, 0);

    }else if( chara.state == MOVE ){
        if( chara.dir[0]==1 &&  chara.dir[1]==0 && chara.dir[2]==0 && chara.dir[3]==0 ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }
        }else if( chara.dir[0]==0 &&  chara.dir[1]==1 && chara.dir[2]==0 && chara.dir[3]==0 ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[2], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[3], chara.x, chara.y, 0);
            }
        }else if( chara.dir[0]==0 &&  chara.dir[1]==0 && chara.dir[2]==1 && chara.dir[3]==0 ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[4], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[5], chara.x, chara.y, 0);
            }
        }else if( chara.dir[0]==0 &&  chara.dir[1]==0 && chara.dir[2]==0 && chara.dir[3]==1 ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[6], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[7], chara.x, chara.y, 0);
            }
        }
    }
}
void character_destory(){
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_bitmap(chara.img_move[2]);
    al_destroy_bitmap(chara.img_move[3]);
    al_destroy_bitmap(chara.img_move[4]);
    al_destroy_bitmap(chara.img_move[5]);
    al_destroy_bitmap(chara.img_move[6]);
    al_destroy_bitmap(chara.img_move[7]);
}
