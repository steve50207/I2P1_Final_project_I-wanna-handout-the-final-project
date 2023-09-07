#include "scene.h"

ALLEGRO_BITMAP *menu= NULL;
ALLEGRO_FONT *menu_word1= NULL;
ALLEGRO_FONT *menu_word2= NULL;
ALLEGRO_FONT *menu_word3= NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *menu_Sound;

ALLEGRO_BITMAP *illustration =NULL;
ALLEGRO_SAMPLE *illustration_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *illustration_sound;

ALLEGRO_BITMAP *select_charater= NULL;
ALLEGRO_BITMAP *charater1= NULL;
ALLEGRO_BITMAP *charater2= NULL;
ALLEGRO_BITMAP *charater3= NULL;
ALLEGRO_FONT *select_character_word1= NULL;
ALLEGRO_FONT *select_character_word2= NULL;
ALLEGRO_FONT *select_character_word3= NULL;
ALLEGRO_SAMPLE *select_character_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *select_character_sound;

ALLEGRO_FONT *charater_score= NULL;
ALLEGRO_FONT *charater2_score=NULL;
ALLEGRO_FONT *charater_time= NULL;
ALLEGRO_SAMPLE *game_scene_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *game_scene_sound;

ALLEGRO_BITMAP *img_doc;
ALLEGRO_BITMAP *img_cof;
ALLEGRO_BITMAP *img_beer;
ALLEGRO_BITMAP *img_pills;


ALLEGRO_BITMAP *background= NULL;

ALLEGRO_BITMAP *win = NULL;
ALLEGRO_FONT *win_word =NULL;
ALLEGRO_SAMPLE *win_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *win_sound;

ALLEGRO_BITMAP *lose= NULL;
ALLEGRO_FONT *lose_word =NULL;
ALLEGRO_SAMPLE *lose_sample= NULL;
ALLEGRO_SAMPLE_INSTANCE *lose_sound;

// function of menu
void menu_init()
{
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    menu = al_load_bitmap("./image/scene/menu.png");
    menu_word1 = al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 30, 0);
    menu_word2 = al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 30, 0);
    menu_word3 = al_load_ttf_font("./font/MushroomKidsDemoRegular.ttf", 30, 0);
    song = al_load_sample("./sound/menu_music.wav");
    menu_Sound = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(menu_Sound, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(menu_Sound, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(menu_Sound, 1) ;
    al_play_sample_instance(menu_Sound);
}
void menu_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
    {
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
        {
            judge_next_window = true;
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            esc=1;
        }
    }


}
void menu_draw()
{
    al_draw_bitmap(menu, 0, 0, 0);
    al_draw_text(menu_word1, al_map_rgb(255, 255, 255), 50, 750, 0, "press Enter to start");
    al_draw_text(menu_word2, al_map_rgb(255, 255, 255), 50, 800, 0, "press C to credit");
    al_draw_text(menu_word3, al_map_rgb(255, 255, 255), 50, 850, 0, "press Esc to exit");
}
void menu_destroy()
{
    al_destroy_bitmap(menu);
    al_destroy_font(menu_word1);
    al_destroy_font(menu_word2);
    al_destroy_font(menu_word3);
    al_destroy_sample_instance(menu_Sound);
}


void illustration_init()
{
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    illustration = al_load_bitmap("./image/scene/illustration.png");

    illustration_sample = al_load_sample("./sound/menu_music.wav");
    illustration_sound = al_create_sample_instance(illustration_sample);
    al_set_sample_instance_playmode(illustration_sound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(illustration_sound, al_get_default_mixer());
    al_set_sample_instance_gain(illustration_sound, 1);
    al_play_sample_instance(illustration_sound);
}
void illustration_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}
void illustration_draw()
{
    al_draw_bitmap(illustration, 0, 0, 0);
}
void illustration_destroy()
{
    al_destroy_bitmap(illustration);
    al_destroy_sample_instance(illustration_sound);
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
    al_set_sample_instance_playmode(select_character_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(select_character_sound, al_get_default_mixer());
    al_set_sample_instance_gain(select_character_sound, 2);
    al_play_sample_instance(select_character_sound);

}

void select_charater_process(ALLEGRO_EVENT event)
{
    if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_A || event.keyboard.keycode == ALLEGRO_KEY_B|| event.keyboard.keycode == ALLEGRO_KEY_C)
        {
            judge_next_window= true;
            if(event.keyboard.keycode == ALLEGRO_KEY_A)
            {
                select_character =1;
            }
            if(event.keyboard.keycode == ALLEGRO_KEY_B) {
                select_character =2;

            }
            if(event.keyboard.keycode == ALLEGRO_KEY_C) {
                select_character =3;
            }

        }
    }
}

void select_charater_draw()
{

    al_draw_bitmap(select_charater, 0, 0, 0);
    al_draw_bitmap(charater1, 300, 450, 0);
    al_draw_bitmap(charater2, 600, 450, 0);
    al_draw_bitmap(charater3, 900, 450, 0);
    al_draw_text(select_character_word1, al_map_rgb(255, 255, 255), 255, 551, 0, "press A");
    al_draw_text(select_character_word2, al_map_rgb(255, 255, 255), 570, 551, 0, "press B");
    al_draw_text(select_character_word3, al_map_rgb(255, 255, 255), 870, 551, 0, "press C");
}

void select_charater_destroy()
{
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
void game_scene_init()
{
    character_init();
    character2_init();
    doc1_init();
    doc2_init();
    doc3_init();
    cof_init();
    beer_init();
    pills_init();
    past_exam_init();
    background = al_load_bitmap("./image/scene/gaming_1.png");
    charater_score = al_load_ttf_font("./font/Montserrat-Bold.ttf", 36, 0);
    charater_time = al_load_ttf_font("./font/Montserrat-Bold.ttf", 36, 0);
    charater2_score = al_load_ttf_font("./font/Montserrat-Bold.ttf", 36, 0);

    game_scene_sample = al_load_sample("./sound/game_bgm.wav");
    game_scene_sound = al_create_sample_instance(game_scene_sample);
    al_set_sample_instance_playmode(game_scene_sound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(game_scene_sound, al_get_default_mixer());
    al_set_sample_instance_gain(game_scene_sound, 1);
    al_play_sample_instance(game_scene_sound);
}

void game_scene_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    doc1_draw();
    doc2_draw();
    doc3_draw();
    cof_draw();
    beer_draw();
    pills_draw();
    past_exam_draw();
    character_draw();
    character2_draw();
    al_draw_text(charater_score, al_map_rgb(0, 0, 0), 35, 10, 0, score_string);
    al_draw_text(charater_time, al_map_rgb(0, 0, 0), 500, 10, 0, time_string);
    al_draw_text(charater2_score, al_map_rgb(0, 0, 0), 935, 10, 0, charater2_score_string);
}

void game_scene_destroy()
{
    al_destroy_bitmap(background);
    character_destory();
    character2_destory();
    doc1_destory();
    doc2_destory();
    doc3_destory();
    cof_destory();
    beer_destory();
    pills_destory();
    past_exam_destory();
    al_destroy_font(charater_score);
    al_destroy_font(charater_time);
    al_destroy_sample_instance(game_scene_sound);
}

void win_scene_init()
{
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    win = al_load_bitmap("./image/scene/wining.png");

    win_word= al_load_ttf_font("./font/pirulen.ttf", 40, 0);

    win_sample = al_load_sample("./sound/game_succeed.wav");
    win_sound = al_create_sample_instance(win_sample);
    al_set_sample_instance_playmode(win_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(win_sound, al_get_default_mixer());
    al_set_sample_instance_gain(win_sound, 3);
    al_play_sample_instance(win_sound);
}

void win_scene_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}

void win_scene_draw()
{
    al_draw_bitmap(win, 0, 0, 0);
    al_draw_text(win_word, al_map_rgb(255, 255, 255), 650, 315, 0, "YOU ARE PASSED");
}

void win_scene_destroy()
{
    al_destroy_bitmap(win);
    al_destroy_font(win_word);
    al_destroy_sample_instance(win_sound);
}

void lose_scene_init()
{
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    lose = al_load_bitmap("./image/scene/losing.png");

    lose_word= al_load_ttf_font("./font/pirulen.ttf", 40, 0);
    lose_sample = al_load_sample("./sound/game_fail.wav");

    lose_sound = al_create_sample_instance(lose_sample);
    al_set_sample_instance_playmode(lose_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(lose_sound, al_get_default_mixer());
    al_set_sample_instance_gain(lose_sound, 3);
    al_play_sample_instance(lose_sound);
}

void lose_scene_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}

void lose_scene_draw()
{
    al_draw_bitmap(lose, 0, 0, 0);
    al_draw_text(lose_word, al_map_rgb(255, 255, 255), 695, 280, 0, "YOU ARE FAILED");
}

void lose_scene_destroy()
{
    al_destroy_bitmap(lose);
    al_destroy_font(lose_word);
    al_destroy_sample_instance(lose_sound);
}
