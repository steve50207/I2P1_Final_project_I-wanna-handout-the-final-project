#include "charater.h"

// the state of character
enum {STOP = 0, MOVE, getdoc, notgetdoc, getcof, notgetcof, getbeer, notgetbeer, getpills, notgetpills};
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
    chara.x = (int)rand()%1000;
    chara.y = (int)rand()%700+100;
    chara.dir[0] = 1;
    chara.dir[1] = 0;
    chara.dir[2] = 0;
    chara.dir[3] = 0;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;

    //initial counting component
    ts = al_get_time();                         //add
    sprintf(score_string,"score = %2d", 0);     //add
    sprintf(time_string,"time = %2d", 61);      //add

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
        if(change_direction==0){
            chara.dir[0] = 0;
            chara.dir[1] = 0;
            chara.dir[2] = 1;
            chara.dir[3] = 0;
            chara.y -= (5+speed);
            chara.state = MOVE;
        }else if(change_direction==1){
            chara.dir[0] = 1;
            chara.dir[1] = 0;
            chara.dir[2] = 0;
            chara.dir[3] = 0;
            chara.y += (5+speed);
            chara.state = MOVE;
        }
    }else if( key_state[ALLEGRO_KEY_A] ){
        if(change_direction==0){
            chara.dir[0] = 0;
            chara.dir[1] = 1;
            chara.dir[2] = 0;
            chara.dir[3] = 0;
            chara.x -= (5+speed);
            chara.state = MOVE;
        }else if(change_direction==1){
            chara.dir[0] = 0;
            chara.dir[1] = 0;
            chara.dir[2] = 0;
            chara.dir[3] = 1;
            chara.x += (5+speed);
            chara.state = MOVE;
        }
    }else if( key_state[ALLEGRO_KEY_S] ){
        if(change_direction==0){
            chara.dir[0] = 1;
            chara.dir[1] = 0;
            chara.dir[2] = 0;
            chara.dir[3] = 0;
            chara.y += (5+speed);
            chara.state = MOVE;
        }else if(change_direction==1){
            chara.dir[0] = 0;
            chara.dir[1] = 0;
            chara.dir[2] = 1;
            chara.dir[3] = 0;
            chara.y -= (5+speed);
            chara.state = MOVE;
        }
    }else if( key_state[ALLEGRO_KEY_D] ){
        if(change_direction==0){
            chara.dir[0] = 0;
            chara.dir[1] = 0;
            chara.dir[2] = 0;
            chara.dir[3] = 1;
            chara.x += (5+speed);
            chara.state = MOVE;
        }else if(change_direction==1){
            chara.dir[0] = 0;
            chara.dir[1] = 1;
            chara.dir[2] = 0;
            chara.dir[3] = 0;
            chara.x -= (5+speed);
            chara.state = MOVE;
        }
    }else if( chara.anime == chara.anime_time-1 ){
        chara.anime = 0;
        chara.state = STOP;
    }else if ( chara.anime == 0 ){
        chara.state = STOP;
    }
    elapsed_time = 61 - (al_get_time() - ts);               //add
    game_time = (int)elapsed_time;                          //add
    sprintf(score_string,"score = %2d", score);             //add
    sprintf(time_string,"time = %2d", game_time);           //add
    if(game_time== 0 && score < 60) {
        judge_next_window =1;
        window =5;
    }
    if(game_time == 0 && score >= 60){
        judge_next_window=1;
        window =4;
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

typedef struct doc
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of icon get/not get;
    ALLEGRO_BITMAP *img_doc;

}Doc;
Doc doc;

ALLEGRO_SAMPLE *get_doc_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *get_doc_sound;
int doc_count;
void doc_init(){
    doc.img_doc=al_load_bitmap("./image/score/document_blue.png");
    // initial the geometric information of character
    doc.width = al_get_bitmap_width(doc.img_doc);
    doc.height = al_get_bitmap_height(doc.img_doc);
    doc.x = (int)rand()%1000;
    doc.y = (int)rand()%700+100;
    // load effective sound
    get_doc_sample = al_load_sample("./sound/picking_file.wav");
    get_doc_sound  = al_create_sample_instance(get_doc_sample);
    // initial the animation component
    doc.state = notgetdoc;
}


void doc_process(){

    if(doc.x-67 <= chara.x && chara.x <= doc.x+48 && doc.y-100 <= chara.y && chara.y <= doc.y+48){

            al_set_sample_instance_playmode(get_doc_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_doc_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_doc_sound, 10);
            al_play_sample_instance(get_doc_sound);
            score+=5;
            printf("%d\n",score);
            doc.state=getdoc;
    }
}
int closed;
void doc_update(){
    doc_count++;
    if( doc.state == getdoc ){
        closed=1;
        doc_init();
    }
    if(doc_count%300==0){
        closed=0;
        doc_init();
        printf("%d\n",doc_count);
    }
}
void doc_draw(){
        if(closed==1){}
        if(closed==0||score==0){
            al_draw_bitmap(doc.img_doc, doc.x, doc.y, 0);
        }
}
void doc_destory(){
    al_destroy_bitmap(doc.img_doc);
    al_destroy_sample_instance(get_doc_sound);
}

///////////////////////////////////////////////////////////////////coffee
int cof_count;
typedef struct coffee
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of icon get/not get;
    ALLEGRO_BITMAP *img_cof;

}Coffee;
Coffee cof;

ALLEGRO_SAMPLE *get_cof_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *get_cof_sound;

void cof_init(){
    cof.img_cof=al_load_bitmap("./image/booster/coffee1.png");
    // initial the geometric information of character
    cof.width = al_get_bitmap_width(cof.img_cof);
    cof.height = al_get_bitmap_height(cof.img_cof);
    cof.x = (int)rand()%1000;
    cof.y = (int)rand()%700+100;
    // load effective sound
    get_cof_sample = al_load_sample("./sound/drinking_coffee.wav");
    get_cof_sound  = al_create_sample_instance(get_cof_sample);
    // initial the animation component
    cof.state = notgetcof;
}


void cof_process(){

    if(cof.x-67 <= chara.x && chara.x <= cof.x+48 && cof.y-100 <= chara.y && chara.y <= cof.y+48){

            al_set_sample_instance_playmode(get_cof_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_cof_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_cof_sound, 8);
            al_play_sample_instance(get_cof_sound);
            printf("get cof boost\n");
            cof.state=getcof;
            speed+=2;
            printf("speed = %d\n", speed);
    }
}

void cof_update(){
    cof_count++;
    if( cof.state == getcof){
        cof_init();
    }
    if(cof_count%600==0){
        cof_init();
    }
}
void cof_draw(){
        al_draw_bitmap(cof.img_cof, cof.x, cof.y, 0);
}
void cof_destory(){
    al_destroy_bitmap(cof.img_cof);
    al_destroy_sample_instance(get_cof_sound);
}

//////////////////////////////////////////////////////////////////beer
typedef struct beer
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of icon get/not get;
    ALLEGRO_BITMAP *img_beer;

}Beer;
Beer beer;

ALLEGRO_SAMPLE *get_beer_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *get_beer_sound;
int beer_count;
void beer_init(){
    beer.img_beer=al_load_bitmap("./image/debuff/beer3.png");
    // initial the geometric information of character
    beer.width = al_get_bitmap_width(beer.img_beer);
    beer.height = al_get_bitmap_height(beer.img_beer);
    beer.x = (int)rand()%1000;
    beer.y = (int)rand()%700+100;
    // load effective sound
    get_beer_sample = al_load_sample("./sound/drinking_alcohol.wav");
    get_beer_sound  = al_create_sample_instance(get_beer_sample);
    // initial the animation component
    beer.state = notgetbeer;
}


void beer_process(){

    if(beer.x-67<= chara.x && chara.x <= beer.x+48 && beer.y-100 <= chara.y && chara.y <= beer.y+48){

            al_set_sample_instance_playmode(get_beer_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_beer_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_beer_sound, 8);
            al_play_sample_instance(get_beer_sound);
            printf("get beer debuff\n");
            beer.state=getbeer;
            speed-=2;
            printf("speed = %d\n", speed);
    }
}

void beer_update(){
    beer_count++;
    if( beer.state == getbeer){
        beer_init();
    }
    if(beer_count%450==0){
        beer_init();
    }
}
void beer_draw(){
        al_draw_bitmap(beer.img_beer, beer.x, beer.y, 0);
}
void beer_destory(){
    al_destroy_bitmap(beer.img_beer);
    al_destroy_sample_instance(get_beer_sound);
}

//////////////////////////////////////////////////////////////////pill
typedef struct pill
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of icon get/not get;
    ALLEGRO_BITMAP *img_pills;

}Pill;
Pill pills;

ALLEGRO_SAMPLE *get_pills_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *get_pills_sound;
int pills_count;
void pills_init(){
    pills.img_pills=al_load_bitmap("./image/debuff/pills2.png");
    // initial the geometric information of character
    pills.width = al_get_bitmap_width(pills.img_pills);
    pills.height = al_get_bitmap_height(pills.img_pills);
    pills.x = (int)rand()%1000;
    pills.y = (int)rand()%700+100;
    // load effective sound
    get_pills_sample = al_load_sample("./sound/taking_pills.wav");
    get_pills_sound  = al_create_sample_instance(get_pills_sample);
    // initial the animation component
    pills.state = notgetpills;
}


void pills_process(){

    if(pills.x-67<= chara.x && chara.x <= pills.x+48 && pills.y-100 <= chara.y && chara.y <= pills.y+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);
            printf("get pills debuff\n");
            pills.state=getpills;
            if(change_direction==false){
                change_direction =true;
            }else{
                change_direction =false;
            }

    }
}

void pills_update(){
    pills_count++;
    if( pills.state == getpills){
        pills_init();
    }
    if(pills_count%150==0){
        pills_init();
    }
}
void pills_draw(){
        al_draw_bitmap(pills.img_pills, pills.x, pills.y, 0);
}
void pills_destory(){
    al_destroy_bitmap(pills.img_pills);
    al_destroy_sample_instance(get_pills_sound);
}
