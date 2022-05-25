#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "Scene.h"

//Variables, structures et fonctions de base
#include "constants.h"

//Class
#include "Character.h"
#include "Menu.h"
#include "gameEnv.h"
#include "Level.h"
#include "Quadtree.h"
#include "makeLevel.h"
#include "Square.h"
#include "Platform.h"
#include "geometry.h"

int main(int argc, char** argv) 
{
    
    //* Initialisation de SDL */
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        const char* error = SDL_GetError();
        fprintf(
            stderr, 
            "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }
	
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Window* window;
    {
        window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(NULL == window) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation de la fenetre : %s\n", error);

            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
    
    SDL_GLContext context;
    {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        context = SDL_GL_CreateContext(window);
    
        if(NULL == context) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation du contexte OpenGL : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }    

    Menu* menu = new Menu();
    Level* tab_level[3] ;
    //Node* tree = quadtree ( WINDOW_WIDTH, WINDOW_HEIGHT);
    //Character** tab_character = new Character*[4];

    ////////////////////////////////////////////
    //A mettre dans Make level 
    ////////////////////////////////////////////

    Character* chara1 = new Character(11,7,{10,30},{30,5});  
    chara1->set_textID(Game_Environment::gentexture("images/character1.png"));

    Character* chara2 = new Character(5,7,{30,50},{60,5});
    chara2->set_textID(Game_Environment::gentexture("images/character2.png"));

    Character* tab_character[4] ; 
    tab_character[0] = chara1 ; 
    tab_character[1] = chara2 ; 
    
    Platform tab_square3[12] ; 
    
    Platform square31 = Platform(40, 15, {20, 7.5});
    tab_square3[0]=square31;

    Platform square32 = Platform(35, 15, {72.5, 7.5});
    tab_square3[1]=square32;

    Platform square33 = Platform(20, 32.5, {160, 48.75});
    tab_square3[2]=square33;

    Platform square34 = Platform(46, 27.5, {110, 13.75});
    tab_square3[3]=square34;

    Platform square35 = Platform(50, 15, {105, 57.5});
    tab_square3[4]=square35;

    Platform square36 = Platform(80, 25, {40, 62.5});
    tab_square3[5]=square36;

    Platform square37 = Platform(10, 2.5, {145, 38.75});
    tab_square3[6]=square37;

    Platform square38 = Platform(30, 27.5, {205, 13.75});
    tab_square3[7]=square38;

    Platform square39 = Platform(10, 5, {175, 62.25});
    tab_square3[8]=square39;

    Platform square310 = Platform(12.5, 2.5, {136, 51});
    tab_square3[9]=square310;

    Platform square311 = Platform(30, 2.5, {(float) (160+15*sin(0.0)), 26.25});
    tab_square3[10]=square311;  

    Platform square312 = Platform(20, 2.5, {190,(float) (46.25+12.5*sin(0.0))});
    tab_square3[11]=square312;

    //Création du niveau 1
    Level* level1 = new Level(tab_square3, tab_character, 12, 2);
    Level* level2 = new Level(tab_square3, tab_character, 12, 2);
    Level* level3 = new Level(tab_square3, tab_character, 12, 1);
    tab_level[0] = level1 ;   
    tab_level[1] = level2 ;   
    tab_level[2] = level3 ; 
    //////////////////////////////////////////
 
    //makeLevel(tab_level, tab_character);

    Game_Environment environment = Game_Environment(tab_level, menu);
    environment.change_to_level(0); 

    environment.onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);
    /* ------------------------------ LOOP ------------------------------ */
    while(environment.is_playing()) 
    {
        
        /* Boucle traitant les evenements */
        environment.manageEvents();

        //Recuperation du temps au debut de la boucle
        Uint32 startTime = SDL_GetTicks();
        
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();       
 
        //dessine la scene
        if (environment.is_in_menu()){
            ((Menu*)environment.get_current_scene())->draw();
        } else {
            for (int i=0 ; i<((Level*)environment.get_current_scene())->get_nb_character() ; i++) {
                ((Level*)environment.get_current_scene())->tab_character[i]->gravity(); 
            } 
            ((Level*)environment.get_current_scene())->get_current_character()->set_position(); 
            for (int i=0 ; i<((Level*)environment.get_current_scene())->get_nb_character() ; i++) {
                    ((Level*)environment.get_current_scene())->collisions(tab_character[i]);
                    for (int j=0; j<((Level*)environment.get_current_scene())->get_nb_character() ; j++) {
                        if (j!=i){
                            ((Level*)environment.get_current_scene())->collisions(tab_character[i]);
                        }
                    }
            }  
            ((Level*)environment.get_current_scene())->draw();
            environment.is_win();
        }

        //Echange du front et du back buffer : mise a jour de la fenetre
        SDL_GL_SwapWindow(window);

        //Calcul du temps ecoule
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if (!(environment.is_in_menu())){
            ((Level*)environment.get_current_scene())->set_alpha(SDL_GetTicks()*0.00025*2*M_PI); 
        }        

        //Si trop peu de temps s'est ecoule, on met en pause le programme 
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
    /* ------------------------------ FIN LOOP ------------------------------ */


    /* Liberation des ressources associees a la SDL */
    
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
