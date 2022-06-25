#include "charater.h"

// the state of character
enum {STOP = 0, MOVE, getdoc, notgetdoc, getcof, notgetcof, getbeer, notgetbeer, getpills, notgetpills, getpast_exam, notgetpast_exam};
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
Character chara2;

ALLEGRO_SAMPLE *sample = NULL;
void character_init(){
    // load character images
    for(int i = 1 ; i <= 8 ; i++){
        char temp[50];
        sprintf( temp, "./image/character0%d/char0%d_move%d.png", select_character, select_character , i );
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
    sprintf(score_string,"P1 score : %2d", 0);     //add
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

    if((chara2.x-40<=chara.x&&chara.x<=chara2.x+40)&&(chara2.y-90<=chara.y&&chara.y<=chara2.y+85)){
         if(chara.x>chara2.x){
            chara.x=chara.x+5;
        }
        if(chara.x<chara2.x){
            chara.x=chara.x-5;
        }
        if(chara.y>chara2.y){
            chara.y=chara.y+5;
        }
        if(chara.y<chara2.y){
            chara.y=chara.y-5;
        }
    }

    elapsed_time = 61 - (al_get_time() - ts);               //add
    game_time = (int)elapsed_time;                          //add
    sprintf(score_string,"P1 score : %2d", score);             //add
    sprintf(time_string,"time = %2d", game_time);           //add
    if(game_time == 0 && score >= 60){
        judge_next_window =1;
        window = 5;
    }
     if(game_time == 0 && score < 60) {
        judge_next_window =1;
        window = 6;
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
////////////////////////////////////////////////////////////////chara2


ALLEGRO_SAMPLE *sample2 = NULL;
void character2_init(){
    // load character images
    for(int i = 1 ; i <= 8 ; i++){
        char temp[50];
        sprintf( temp, "./image/character0%d/char0%d_move%d.png", 2, 2 , i );
        chara2.img_move[i-1] = al_load_bitmap(temp);
    }

    // initial the geometric information of character
    chara2.width = al_get_bitmap_width(chara2.img_move[0]);
    chara2.height = al_get_bitmap_height(chara2.img_move[0]);
    chara2.x = (int)rand()%1000;
    chara2.y = (int)rand()%700+100;
    chara2.dir[0] = 1;
    chara2.dir[1] = 0;
    chara2.dir[2] = 0;
    chara2.dir[3] = 0;

    // initial the animation component
    chara2.state = STOP;
    chara2.anime = 0;
    chara2.anime_time = 30;

    //initial counting component
    ts = al_get_time();                         //add
    sprintf(charater2_score_string,"P2 score : %2d", 0);     //add
    //sprintf(time_string,"(2) time = %2d", 61);      //add

}
void charater2_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara2.anime++;
            chara2.anime %= chara2.anime_time;
        }
    // process the keyboard event
   }/*else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara2.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }*/
}
void charater2_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_I] ){
        if(charater2_change_direction==0){
            chara2.dir[0] = 0;
            chara2.dir[1] = 0;
            chara2.dir[2] = 1;
            chara2.dir[3] = 0;
            chara2.y -= (5+charater2_speed);
            chara2.state = MOVE;
        }else if(charater2_change_direction==1){
            chara2.dir[0] = 1;
            chara2.dir[1] = 0;
            chara2.dir[2] = 0;
            chara2.dir[3] = 0;
            chara2.y += (5+charater2_speed);
            chara2.state = MOVE;
        }
    }else if( key_state[ALLEGRO_KEY_J] ){
        if(charater2_change_direction==0){
            chara2.dir[0] = 0;
            chara2.dir[1] = 1;
            chara2.dir[2] = 0;
            chara2.dir[3] = 0;
            chara2.x -= (5+charater2_speed);
            chara2.state = MOVE;
        }else if(charater2_change_direction==1){
            chara2.dir[0] = 0;
            chara2.dir[1] = 0;
            chara2.dir[2] = 0;
            chara2.dir[3] = 1;
            chara2.x += (5+charater2_speed);
            chara2.state = MOVE;
        }
    }else if( key_state[ALLEGRO_KEY_K] ){
        if(charater2_change_direction==0){
            chara2.dir[0] = 1;
            chara2.dir[1] = 0;
            chara2.dir[2] = 0;
            chara2.dir[3] = 0;
            chara2.y += (5+charater2_speed);
            chara2.state = MOVE;
        }else if(charater2_change_direction==1){
            chara2.dir[0] = 0;
            chara2.dir[1] = 0;
            chara2.dir[2] = 1;
            chara2.dir[3] = 0;
            chara2.y -= (5+charater2_speed);
            chara2.state = MOVE;
        }
    }else if( key_state[ALLEGRO_KEY_L] ){
        if(charater2_change_direction==0){
            chara2.dir[0] = 0;
            chara2.dir[1] = 0;
            chara2.dir[2] = 0;
            chara2.dir[3] = 1;
            chara2.x += (5+charater2_speed);
            chara2.state = MOVE;
        }else if(charater2_change_direction==1){
            chara2.dir[0] = 0;
            chara2.dir[1] = 1;
            chara2.dir[2] = 0;
            chara2.dir[3] = 0;
            chara2.x -= (5+charater2_speed);
            chara2.state = MOVE;
        }
    }else if( chara2.anime == chara2.anime_time-1 ){
        chara2.anime = 0;
        chara2.state = STOP;
    }else if ( chara2.anime == 0 ){
        chara2.state = STOP;
    }
    //elapsed_time = 61 - (al_get_time() - ts);               //add
    //game_time = (int)elapsed_time;                          //add
    sprintf(charater2_score_string,"P2 score : %2d", ch2_score);             //add
    //sprintf(time_string,"time = %2d", game_time);           //add
    if(game_time == 0 && score >= 60){
        judge_next_window =1;
        window = 5;
    }
     if(game_time == 0 && score < 60) {
        judge_next_window =1;
        window = 6;
    }
    if((chara.x-40<=chara2.x&&chara2.x<=chara.x+40)&&(chara.y-90<=chara2.y&&chara2.y<=chara.y+85)){
        if(chara2.x>chara.x){
            chara2.x=chara2.x+5;
        }
        if(chara2.x<chara.x){
            chara2.x=chara2.x-5;
        }
        if(chara2.y>chara.y){
            chara2.y=chara2.y+5;
        }
        if(chara2.y<chara.y){
            chara2.y=chara2.y-5;
        }
    }

}
void character2_draw(){
    // with the state, draw corresponding image
    if( chara2.state == STOP ){
        if( chara2.dir[0]==1 &&  chara2.dir[1]==0 && chara2.dir[2]==0 && chara2.dir[3]==0)
            al_draw_bitmap(chara2.img_move[0], chara2.x, chara2.y, 0);
        else if( chara2.dir[0]==0 &&  chara2.dir[1]==1 && chara2.dir[2]==0 && chara2.dir[3]==0)
            al_draw_bitmap(chara2.img_move[2], chara2.x, chara2.y, 0);
        else if( chara2.dir[0]==0 &&  chara2.dir[1]==0 && chara2.dir[2]==1 && chara2.dir[3]==0)
            al_draw_bitmap(chara2.img_move[4], chara2.x, chara2.y, 0);
        else if( chara2.dir[0]==0 &&  chara2.dir[1]==0 && chara2.dir[2]==0 && chara2.dir[3]==1)
            al_draw_bitmap(chara2.img_move[6], chara2.x, chara2.y, 0);

    }else if( chara2.state == MOVE ){
        if( chara2.dir[0]==1 &&  chara2.dir[1]==0 && chara2.dir[2]==0 && chara2.dir[3]==0 ){
            if( chara2.anime < chara2.anime_time/2 ){
                al_draw_bitmap(chara2.img_move[0], chara2.x, chara2.y, 0);
            }else{
                al_draw_bitmap(chara2.img_move[1], chara2.x, chara2.y, 0);
            }
        }else if( chara2.dir[0]==0 &&  chara2.dir[1]==1 && chara2.dir[2]==0 && chara2.dir[3]==0 ){
            if( chara2.anime < chara2.anime_time/2 ){
                al_draw_bitmap(chara2.img_move[2], chara2.x, chara2.y, 0);
            }else{
                al_draw_bitmap(chara2.img_move[3], chara2.x, chara2.y, 0);
            }
        }else if( chara2.dir[0]==0 &&  chara2.dir[1]==0 && chara2.dir[2]==1 && chara2.dir[3]==0 ){
            if( chara2.anime < chara2.anime_time/2 ){
                al_draw_bitmap(chara2.img_move[4], chara2.x, chara2.y, 0);
            }else{
                al_draw_bitmap(chara2.img_move[5], chara2.x, chara2.y, 0);
            }
        }else if( chara2.dir[0]==0 &&  chara2.dir[1]==0 && chara2.dir[2]==0 && chara2.dir[3]==1 ){
            if( chara2.anime < chara2.anime_time/2 ){
                al_draw_bitmap(chara2.img_move[6], chara2.x, chara2.y, 0);
            }else{
                al_draw_bitmap(chara2.img_move[7], chara2.x, chara2.y, 0);
            }
        }
    }
}
void character2_destory(){
    al_destroy_bitmap(chara2.img_move[0]);
    al_destroy_bitmap(chara2.img_move[1]);
    al_destroy_bitmap(chara2.img_move[2]);
    al_destroy_bitmap(chara2.img_move[3]);
    al_destroy_bitmap(chara2.img_move[4]);
    al_destroy_bitmap(chara2.img_move[5]);
    al_destroy_bitmap(chara2.img_move[6]);
    al_destroy_bitmap(chara2.img_move[7]);
}


////////////////////////////////////////////////////////////////doc1

typedef struct doc
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of icon get/not get;
    ALLEGRO_BITMAP *img_doc;

}Doc;

Doc doc1;

ALLEGRO_SAMPLE *get_doc1_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *get_doc1_sound;

void doc1_init(){
    doc1.img_doc=al_load_bitmap("./image/score/document_blue.png");
    // initial the geometric information of character
    doc1.width = al_get_bitmap_width(doc1.img_doc);
    doc1.height = al_get_bitmap_height(doc1.img_doc);
    doc1.x = (int)rand()%1000;
    doc1.y = (int)rand()%700+100;
    // load effective sound
    get_doc1_sample = al_load_sample("./sound/picking_file.wav");
    get_doc1_sound  = al_create_sample_instance(get_doc1_sample);
    // initial the animation component
    doc1.state = notgetdoc;
}


void doc1_process(){

    if(doc1.x-67 <= chara.x && chara.x <= doc1.x+48 && doc1.y-100 <= chara.y && chara.y <= doc1.y+48){

        al_set_sample_instance_playmode(get_doc1_sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(get_doc1_sound, al_get_default_mixer());
        al_set_sample_instance_gain(get_doc1_sound, 10);
        al_play_sample_instance(get_doc1_sound);
        score+=5;
        if(changecolor==1)
        {
            score+=5;
        }
        printf("P1 %d\n",score);
        doc1.state=getdoc;
    }
    if(doc1.x-67 <= chara2.x && chara2.x <= doc1.x+48 && doc1.y-100 <= chara2.y && chara2.y <= doc1.y+48){

        al_set_sample_instance_playmode(get_doc1_sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(get_doc1_sound, al_get_default_mixer());
        al_set_sample_instance_gain(get_doc1_sound, 10);
        al_play_sample_instance(get_doc1_sound);
        ch2_score+=5;
        if(changecolor==1)
        {
            ch2_score+=5;
        }
        printf("P2 %d\n",ch2_score);
        doc1.state=getdoc;
    }
}

int doc1_count;
int doc1_closed;
void doc1_update(){
    doc1_count++;
    if( doc1.state == getdoc ){
        doc1_closed=1;
        doc1_init();
    }
    if(doc1_count%240==0){
        doc1_closed=0;
        doc1_init();
        //printf("%d\n",doc1_count);
    }
}
void doc1_draw(){
    if(doc1_closed==1){}
    if(doc1_closed==0||score==0){
        al_draw_bitmap(doc1.img_doc, doc1.x, doc1.y, 0);
    }
}
void doc1_destory(){
    al_destroy_bitmap(doc1.img_doc);
    al_destroy_sample_instance(get_doc1_sound);
}

////////////////////////////////////////////////////////////////doc2

Doc doc2;

ALLEGRO_SAMPLE *get_doc2_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *get_doc2_sound;

void doc2_init(){
    doc2.img_doc=al_load_bitmap("./image/score/document_green.png");
    // initial the geometric information of character
    doc2.width = al_get_bitmap_width(doc2.img_doc);
    doc2.height = al_get_bitmap_height(doc2.img_doc);
    doc2.x = (int)rand()%1000;
    doc2.y = (int)rand()%700+100;
    // load effective sound
    get_doc2_sample = al_load_sample("./sound/picking_file.wav");
    get_doc2_sound  = al_create_sample_instance(get_doc2_sample);
    // initial the animation component
    doc2.state = notgetdoc;
}


void doc2_process(){

    if(doc2.x-67 <= chara.x && chara.x <= doc2.x+48 && doc2.y-100 <= chara.y && chara.y <= doc2.y+48){

        al_set_sample_instance_playmode(get_doc2_sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(get_doc2_sound, al_get_default_mixer());
        al_set_sample_instance_gain(get_doc2_sound, 10);
        al_play_sample_instance(get_doc2_sound);
        if(changecolor==1){
            score+=10;
        }
        printf("P1 %d\n",score);
        doc2.state=getdoc;
    }
    if(doc2.x-67 <= chara2.x && chara2.x <= doc2.x+48 && doc2.y-100 <= chara2.y && chara2.y <= doc2.y+48){

        al_set_sample_instance_playmode(get_doc2_sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(get_doc2_sound, al_get_default_mixer());
        al_set_sample_instance_gain(get_doc2_sound, 10);
        al_play_sample_instance(get_doc2_sound);
        if(changecolor==1){
            ch2_score+=10;
        }
        printf("P2 %d\n",ch2_score);
        doc2.state=getdoc;
    }
}

int doc2_count;
int doc2_closed;
void doc2_update(){
    doc2_count++;
    if( doc2.state == getdoc ){
        doc2_closed=1;
        doc2_init();
    }
    if(doc2_count%240==0){
        doc2_closed=0;
        doc2_init();
        //printf("%d\n",doc2_count);
    }
}

void doc2_draw(){
    if(doc2_closed==1){}
    if(doc2_closed==0||score==0){
        if(changecolor==1){
            al_draw_bitmap(doc1.img_doc, doc2.x, doc2.y, 0);
        }else{
            al_draw_bitmap(doc2.img_doc, doc2.x, doc2.y, 0);
        }
    }
}

void doc2_destory(){
    al_destroy_bitmap(doc2.img_doc);
    al_destroy_sample_instance(get_doc2_sound);
}

////////////////////////////////////////////////////////////////doc3

Doc doc3;

ALLEGRO_SAMPLE *get_doc3_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *get_doc3_sound;

void doc3_init(){
    doc3.img_doc=al_load_bitmap("./image/score/document_white.png");
    // initial the geometric information of character
    doc3.width = al_get_bitmap_width(doc3.img_doc);
    doc3.height = al_get_bitmap_height(doc3.img_doc);
    doc3.x = (int)rand()%1000;
    doc3.y = (int)rand()%700+100;
    // load effective sound
    get_doc3_sample = al_load_sample("./sound/picking_file.wav");
    get_doc3_sound  = al_create_sample_instance(get_doc3_sample);
    // initial the animation component
    doc3.state = notgetdoc;
}


void doc3_process(){

    if(doc3.x-67 <= chara.x && chara.x <= doc3.x+48 && doc3.y-100 <= chara.y && chara.y <= doc3.y+48){

            al_set_sample_instance_playmode(get_doc3_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_doc3_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_doc3_sound, 10);
            al_play_sample_instance(get_doc3_sound);
            if(changecolor==1){
                 score+=10;
            }
            printf("P1 %d\n",score);
            doc3.state=getdoc;
    }
    if(doc3.x-67 <= chara2.x && chara2.x <= doc3.x+48 && doc3.y-100 <= chara2.y && chara2.y <= doc3.y+48){

            al_set_sample_instance_playmode(get_doc3_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_doc3_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_doc3_sound, 10);
            al_play_sample_instance(get_doc3_sound);
            if(changecolor==1){
                 ch2_score+=10;
            }
            printf("P2 %d\n",ch2_score);
            doc3.state=getdoc;
    }
}

int doc3_count;
int doc3_closed;
void doc3_update(){
    doc3_count++;
    if( doc3.state == getdoc ){
        doc3_closed=1;
        doc3_init();
    }
    if(doc3_count%240==0){
        doc3_closed=0;
        doc3_init();
        //printf("%d\n",doc3_count);
    }
}
void doc3_draw(){
        if(doc3_closed==1){}
        if(doc3_closed==0||score==0){
            if(changecolor==1){
                al_draw_bitmap(doc1.img_doc, doc3.x, doc3.y, 0);
            }else{
                al_draw_bitmap(doc3.img_doc, doc3.x, doc3.y, 0);
            }
      }
}
void doc3_destory(){
    al_destroy_bitmap(doc3.img_doc);
    al_destroy_sample_instance(get_doc3_sound);
}

///////////////////////////////////////////////////////////////////coffee

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

int chara1_cof_duration;
int chara2_cof_duration;

void cof_process(){

    if(cof.x-67 <= chara.x && chara.x <= cof.x+48 && cof.y-100 <= chara.y && chara.y <= cof.y+48){

            al_set_sample_instance_playmode(get_cof_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_cof_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_cof_sound, 8);
            al_play_sample_instance(get_cof_sound);
            printf("P1 get cof boost\n");
            cof.state=getcof;
            if(5+speed<9){
                speed+=2;
            }
            printf("P1 speed = %d\n", speed);
    }
    if(cof.x-67 <= chara2.x && chara2.x <= cof.x+48 && cof.y-100 <= chara2.y && chara2.y <= cof.y+48){

            al_set_sample_instance_playmode(get_cof_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_cof_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_cof_sound, 8);
            al_play_sample_instance(get_cof_sound);
            printf("P2 get cof boost\n");
            cof.state=getcof;
            if(5+charater2_speed<9){
                charater2_speed+=2;
            }
            printf("P2 speed = %d\n", charater2_speed);
    }
}


int cof_count;
int cof_closed;
void cof_update(){
    cof_count++;
    if( cof.state == getcof||cof_count==1500||cof_count==3300){
        cof_closed=1;
        cof_init();
    }
    if(cof_count==1200||cof_count==3000){
        cof_closed=0;
        cof_init();
    }
}
void cof_draw(){
    if(cof_closed==1||cof_count<1200){
        cof.x=-1000;
        cof.y=-1000;
    }
    if(cof_closed==0&&cof_count>=1200){
        al_draw_bitmap(cof.img_cof, cof.x, cof.y, 0);
    }
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
            printf("P2 get beer debuff\n");
            beer.state=getbeer;
            if(5+speed>1){
                speed-=2;
            }
            printf("P1 speed = %d\n", speed);
    }
     if(beer.x-67<= chara2.x && chara2.x <= beer.x+48 && beer.y-100 <= chara2.y && chara2.y <= beer.y+48){

            al_set_sample_instance_playmode(get_beer_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_beer_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_beer_sound, 8);
            al_play_sample_instance(get_beer_sound);
            printf("P2 get beer debuff\n");
            beer.state=getbeer;
            if(5+charater2_speed>1){
                charater2_speed-=2;
            }
            printf("P2 speed = %d\n", charater2_speed);
    }
}

int beer_count;
int beer_closed;
void beer_update(){
    beer_count++;
    if( beer.state == getbeer||beer_count==600||beer_count==2400){
        beer_closed=1;
        beer_init();
    }
    if(beer_count==300||beer_count==2100){
        beer_closed=0;
        beer_init();
    }
}
void beer_draw(){
    if(beer_closed==1||beer_count<300){
        beer.x=-1000;
        beer.y=-1000;
    }
    if(beer_closed==0&&beer_count>=300){
        al_draw_bitmap(beer.img_beer, beer.x, beer.y, 0);
    }
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

    //charater dir is left and collide with pill from right side
    if( chara.dir[1] ==1 && pills.x <= chara.x && chara.x <= pills.x+48 && pills.y-100 <= chara.y && chara.y <= pills.y+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);

            pills.state=getpills;
            printf("P1 get pills debuff\n");

            chara.x+=5;

            if(change_direction==false){
                change_direction =true;
            }else{
                change_direction =false;
            }
    //charater dir is right and collide with pill from left side
    }else if(chara.dir[3] ==1 && pills.x-67 <= chara.x && chara.x <= pills.x && pills.y-100 <= chara.y && chara.y <= pills.y+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);

            pills.state=getpills;
            printf("P1 get pills debuff\n");

            chara.x-=5;
            if(change_direction==false){
                change_direction =true;
            }else{
                change_direction =false;
            }
    //charater dir is down and collide with pill from top side
    }else if(chara.dir[0] ==1 && pills.y-100 <= chara.y && chara.y <= pills.y && pills.x-67 <= chara.x && chara.x <= pills.x+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);

            pills.state=getpills;
            printf("P1 get pills debuff\n");

            chara.y-=5;
            if(change_direction==false){
                change_direction =true;
            }else{
                change_direction =false;
            }
    //charater dir is up and collide with pill from bottom side
    }else if(chara.dir[2] ==1 && pills.y <= chara.y && chara.y <= pills.y+48 && pills.x-67 <= chara.x && chara.x <= pills.x+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);

            pills.state=getpills;
            printf("P1 get pills debuff\n");

            chara.y+=5;
            if(change_direction==false){
                change_direction =true;
            }else{
                change_direction =false;
            }
    }
    if( chara2.dir[1] ==1 && pills.x <= chara2.x && chara2.x <= pills.x+48 && pills.y-100 <= chara2.y && chara2.y <= pills.y+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);

            pills.state=getpills;
            printf("P2 get pills debuff\n");

            chara2.x+=5;

            if(charater2_change_direction==false){
                charater2_change_direction =true;
            }else{
                charater2_change_direction =false;
            }
    //charater dir is right and collide with pill from left side
    }else if(chara2.dir[3] ==1 && pills.x-67 <= chara2.x && chara2.x <= pills.x && pills.y-100 <= chara2.y && chara2.y <= pills.y+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);

            pills.state=getpills;
            printf("P2 get pills debuff\n");

            chara2.x-=5;
            if(charater2_change_direction==false){
                charater2_change_direction =true;
            }else{
                charater2_change_direction =false;
            }
    //charater dir is down and collide with pill from top side
    }else if(chara2.dir[0] ==1 && pills.y-100 <= chara2.y && chara2.y <= pills.y && pills.x-67 <= chara2.x && chara2.x <= pills.x+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);

            pills.state=getpills;
            printf("P2 get pills debuff\n");

            chara2.y-=5;
            if(charater2_change_direction==false){
                charater2_change_direction =true;
            }else{
                charater2_change_direction =false;
            }
    //charater dir is up and collide with pill from bottom side
    }else if(chara2.dir[2] ==1 && pills.y <= chara2.y && chara2.y <= pills.y+48 && pills.x-67 <= chara2.x && chara2.x <= pills.x+48){

            al_set_sample_instance_playmode(get_pills_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_pills_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_pills_sound, 5);
            al_play_sample_instance(get_pills_sound);

            pills.state=getpills;
            printf("P2 get pills debuff\n");

            chara2.y+=5;
            if(charater2_change_direction==false){
                charater2_change_direction =true;
            }else{
                charater2_change_direction =false;
            }
    }
}

int pills_count;
int pills_closed;
void pills_update(){
    pills_count++;
    if( pills.state == getpills||pills_count==1200||pills_count==3000){
        pills_closed=1;
        pills_init();
    }
    if(pills_count==900||pills_count==2700){
        pills_closed=0;
        pills_init();
    }
}
void pills_draw(){
    if(pills_closed==1||pills_count<900){
        pills.x=-1000;
        pills.y=-1000;
    }
    if(pills_closed==0&&pills_count>=900)
        al_draw_bitmap(pills.img_pills, pills.x, pills.y, 0);
}
void pills_destory(){
    al_destroy_bitmap(pills.img_pills);
    al_destroy_sample_instance(get_pills_sound);
}

//////////////////////////////////////////////////////////
typedef struct past_exam
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of icon get/not get;
    ALLEGRO_BITMAP *img_past_exam;

}Past_exam;
Past_exam past_exam;

ALLEGRO_SAMPLE *get_past_exam_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *get_past_exam_sound;

void past_exam_init(){
    past_exam.img_past_exam=al_load_bitmap("./image/booster/past_exam.png");
    // initial the geometric information of character
    past_exam.width = al_get_bitmap_width(past_exam.img_past_exam);
    past_exam.height = al_get_bitmap_height(past_exam.img_past_exam);
    past_exam.x = (int)rand()%1000;
    past_exam.y = (int)rand()%700+100;
    // load effective sound
    get_past_exam_sample = al_load_sample("./sound/picking_past_exam.wav");
    get_past_exam_sound  = al_create_sample_instance(get_past_exam_sample);
    // initial the animation component
    past_exam.state = notgetpast_exam;
}


void past_exam_process(){

    if(past_exam.x-67<= chara.x && chara.x <= past_exam.x+48 && past_exam.y-100 <= chara.y && chara.y <= past_exam.y+48){

            al_set_sample_instance_playmode(get_past_exam_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_past_exam_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_past_exam_sound, 5);
            al_play_sample_instance(get_past_exam_sound);
            printf("get past exam buff\n");
            past_exam.state=getpast_exam;

    }
    if(past_exam.x-67<= chara2.x && chara2.x <= past_exam.x+48 && past_exam.y-100 <= chara2.y && chara2.y <= past_exam.y+48){

            al_set_sample_instance_playmode(get_past_exam_sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(get_past_exam_sound, al_get_default_mixer());
            al_set_sample_instance_gain(get_past_exam_sound, 5);
            al_play_sample_instance(get_past_exam_sound);
            printf("(2)get past exam buff\n");
            past_exam.state=getpast_exam;

    }
}

int past_exam_count;
int past_exam_closed;
void past_exam_update(){
    past_exam_count++;
    if( past_exam.state == getpast_exam||past_exam_count%660==0){
        if(past_exam_count%660!=0&&past_exam.state == getpast_exam){
            changecolor=1;
        }
        else{
            changecolor=0;
        }
        past_exam_closed=1;
        past_exam_init();
    }
    if(past_exam_count%480==0){
        past_exam_closed=0;
        past_exam_init();
    }
}
void past_exam_draw(){
    if(past_exam_closed==1||past_exam_count<480){
        past_exam.x=-1000;
        past_exam.y=-1000;
    }
    if(past_exam_closed==0&&past_exam_count>=480)
        al_draw_bitmap(past_exam.img_past_exam, past_exam.x, past_exam.y, 0);
}
void past_exam_destory(){
    al_destroy_bitmap(past_exam.img_past_exam);
    al_destroy_sample_instance(get_past_exam_sound);
}
