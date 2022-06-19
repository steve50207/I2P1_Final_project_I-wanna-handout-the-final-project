#include "scene.h"

ALLEGRO_BITMAP *menu= NULL;
ALLEGRO_FONT *menu_word1= NULL;
ALLEGRO_FONT *menu_word2= NULL;
ALLEGRO_FONT *menu_word3= NULL;

ALLEGRO_BITMAP *select_charater= NULL;
ALLEGRO_BITMAP *charater1= NULL;
ALLEGRO_BITMAP *charater2= NULL;
ALLEGRO_BITMAP *charater3= NULL;
ALLEGRO_FONT *select_character_word1= NULL;
ALLEGRO_FONT *select_character_word2= NULL;
ALLEGRO_FONT *select_character_word3= NULL;
ALLEGRO_SAMPLE *select_character_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *select_character_sound;

ALLEGRO_FONT *charater_score= NULL;         //add
ALLEGRO_FONT *charater_time= NULL;          //add
ALLEGRO_SAMPLE *game_scene_sample= NULL;    //add
ALLEGRO_SAMPLE_INSTANCE *game_scene_sound;  //add

ALLEGRO_BITMAP *img_doc;


ALLEGRO_BITMAP *background= NULL;

ALLEGRO_BITMAP *win = NULL;

ALLEGRO_BITMAP *lose= NULL;


// function of menu
void menu_init(){
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    menu = al_load_bitmap("./image/scene/menu.png");
    menu_word1 = al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 30, 0);
    menu_word2 = al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 30, 0);
    menu_word3 = al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 30, 0);
}
void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;

}
void menu_draw(){
    al_draw_bitmap(menu, 0, 0, 0);
    al_draw_text(menu_word1, al_map_rgb(255, 255, 255), 50, 750, 0, "press Enter to start");
    al_draw_text(menu_word2, al_map_rgb(255, 255, 255), 50, 800, 0, "press C to credit");
    al_draw_text(menu_word3, al_map_rgb(255, 255, 255), 50, 850, 0, "press Esc to exit");
}
void menu_destroy(){
    al_destroy_bitmap(menu);
    al_destroy_font(menu_word1);
    al_destroy_font(menu_word2);
    al_destroy_font(menu_word3);
}

void select_charater_init()
{
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    select_charater = al_load_bitmap("./image/scene/select_character.png");

    charater1 = al_load_bitmap("./image/character01/char01_move1.png");
    charater2 = al_load_bitmap("./image/character02/char02_move1.png");
    charater3 = al_load_bitmap("./image/character03/char03_move1.png");
    select_character_word1= al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 50, 0);
    select_character_word2= al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 50, 0);
    select_character_word3= al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 50, 0);
    select_character_sample = al_load_sample("./sound/select_character.wav");
    select_character_sound = al_create_sample_instance(select_character_sample);

}

void select_charater_process(ALLEGRO_EVENT event){
    if(event.type == ALLEGRO_EVENT_KEY_UP)
        if(event.keyboard.keycode == ALLEGRO_KEY_A||
           event.keyboard.keycode == ALLEGRO_KEY_B||
           event.keyboard.keycode == ALLEGRO_KEY_C)
            judge_next_window= true;
}
void select_charater_draw(){

    al_draw_bitmap(select_charater, 0, 0, 0);
    al_draw_bitmap(charater1, 300, 450, 0);
    al_draw_bitmap(charater2, 600, 450, 0);
    al_draw_bitmap(charater3, 900, 450, 0);
    al_draw_text(select_character_word1, al_map_rgb(255, 255, 255), 280, 600, 0, "press A");
    al_draw_text(select_character_word2, al_map_rgb(255, 255, 255), 580, 600, 0, "press B");
    al_draw_text(select_character_word3, al_map_rgb(255, 255, 255), 880, 600, 0, "press C");

    al_set_sample_instance_playmode(select_character_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(select_character_sound, al_get_default_mixer());
    al_set_sample_instance_gain(select_character_sound, 3);
    al_play_sample_instance(select_character_sound);
}

void select_charater_destroy(){
    al_destroy_bitmap(select_charater);
    al_destroy_bitmap(charater1);
    al_destroy_bitmap(charater2);
    al_destroy_bitmap(charater3);
    al_destroy_font(select_character_word1);
    al_destroy_font(select_character_word2);
    al_destroy_font(select_character_word3);
    al_destroy_sample_instance(select_character_sound);
}

// function of game_scene
void game_scene_init(){
    character_init();
    doc_init();
    background = al_load_bitmap("./image/scene/gaming_1.png");
    charater_score = al_load_ttf_font("./font/Montserrat-Bold.ttf", 50, 0);            //add
    charater_time = al_load_ttf_font("./font/Montserrat-Bold.ttf", 50, 0);             //add

    game_scene_sample = al_load_sample("./sound/game_bgm.wav");
    game_scene_sound = al_create_sample_instance(game_scene_sample);
}
void game_scene_draw(){
    al_draw_bitmap(background, 0, 0, 0);
    doc_draw();
    character_draw();
    al_draw_text(charater_score, al_map_rgb(0, 0, 0), 35, 10, 0, score_string);         //add
    al_draw_text(charater_time, al_map_rgb(0, 0, 0), 935, 10, 0, time_string);          //add
    al_set_sample_instance_playmode(game_scene_sound, ALLEGRO_PLAYMODE_LOOP);           //add
    al_attach_sample_instance_to_mixer(game_scene_sound, al_get_default_mixer());       //add
    al_set_sample_instance_gain(game_scene_sound, 3);                                   //add
    al_play_sample_instance(game_scene_sound);                                          //add

}
void game_scene_destroy(){
    al_destroy_bitmap(background);
    character_destory();
    doc_destory();
    al_destroy_font(charater_score);                                                    //add
    al_destroy_font(charater_time);                                                     //add
    al_destroy_sample_instance(game_scene_sound);                                       //add
}
