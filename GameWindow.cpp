#include "GameWindow.h"

bool draw = false;

const char *title = "I wanna handout the final project!";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;

int Game_establish() {
    int msg = 0;

    game_init();

    game_begin();

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }

    game_destroy();
    return 0;
}

void game_init() {
    printf( "Game Initializing...\n" );
    al_init();
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/character01/char01_move1.png");
    al_set_display_icon(display, icon);
}

void game_begin() {
    // Load sound
    al_reserve_samples(20);
    al_start_timer(fps);
    // initialize the menu before entering the loop
    menu_init();

}

void game_update(){

    if( judge_next_window ==1 && window ==1 ){
        // not back menu anymore, therefore destroy it
        menu_destroy();
        // initialize next scene
        illustration_init();
        judge_next_window = false;
        window = 2;

    }else if( judge_next_window ==1 && window == 2 ){
        illustration_destroy();
        select_charater_init();
        judge_next_window = false;
        window = 3;
    }else if(judge_next_window ==1 && window == 3){
        select_charater_destroy();
        game_scene_init();
        judge_next_window = false;
        window = 4;
    }else if(window == 4){
        charater_update();
        charater2_update();
        doc1_update();
        doc2_update();
        doc3_update();
        cof_update();
        beer_update();
        pills_update();
        past_exam_update();
    }

    if(judge_next_window ==1 && window == 5){

        game_scene_destroy();
        win_scene_init();
        judge_next_window =false;

    }else if(judge_next_window ==1 && window == 6){

        game_scene_destroy();
        lose_scene_init();
        judge_next_window =false;

    }
}

int process_event(){
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    // process the event of other component
    if( window == 1 ){
        menu_process(event);
        if( esc == 1)return -1;
    }else if( window == 2 ){
        illustration_process(event);
    }else if( window == 3 ){
        select_charater_process(event);

    }else if(window == 4){
        charater_process(event);
        charater2_process(event);
        doc1_process();
        doc2_process();
        doc3_process();
        cof_process();
        beer_process();
        pills_process();
        past_exam_process();
    }else if(window == 5){
        win_scene_process(event);
        if(judge_next_window == 1)return -1;
    }else if(window == 6){
        lose_scene_process(event);
        if(judge_next_window == 1)return -1;
    }

    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            draw = true;
    if(draw) game_update();
    return 0;
}

void game_draw(){
    if( window == 1 ){
        menu_draw();
    }else if( window == 2){
        illustration_draw();
    }else if( window == 3 ){
        select_charater_draw();
    }else if( window == 4 ){
        game_scene_draw();
    }else if(window == 5){
        win_scene_draw();
    }else if(window == 6){
        lose_scene_draw();
    }

    al_flip_display();
}

int game_run() {
    int error = 0;
    if( draw ){
        game_draw();
        draw = false;
    }
    if ( !al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    return error;
}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    win_scene_destroy();
    lose_scene_destroy();
}
