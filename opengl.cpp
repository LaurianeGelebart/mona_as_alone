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
//#include "Quadtree.h"
// #include "makeLevel.h"
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
    Level* tab_level[12] ;

    ////////////////////////////////////////////
    //A mettre dans Make level 
    ////////////////////////////////////////////

    Character* chara1 = new Character(10,4,{2,50},{30,5});

    Character* chara2 = new Character(5,7,{20,50},{60,5});

    Character* tab_character[4] ; 
    tab_character[0] = chara1 ; 
    tab_character[1] = chara2 ; 
    Platform tab_square[12] ; 

    Platform square1 = Platform(40, 15, {20, 7.5});
    tab_square[0]=square1;


    Platform square11 = Platform(30, 2.5, {160+15*sin(0.0), 26.25});
    tab_square[10]=square11;  

    Platform square12 = Platform(20, 2.5, {190, 46.25+12.5*sin(0.0)});
    tab_square[11]=square12;  

    //Création du niveau 1
    Level* level1 = new Level(tab_square, tab_character, 12, 2);
    Level* level2 = new Level(tab_square, tab_character, 12, 2);
    tab_level[0] = level1 ;   
    tab_level[1] = level2 ; 
    //////////////////////////////////////////
    

  // makeLevel(tab_level);

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
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();       
 
        //dessine la scene
        if (environment.is_in_menu()){
            ((Menu*)environment.get_current_scene())->draw();
        } else {
            for (int i=0 ; i<((Level*)environment.get_current_scene())->get_nb_character() ; i++) {
                ((Level*)environment.get_current_scene())->tab_character[i]->set_old_position(tab_character[i]->get_current_pos()); 
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
            ((Level*)environment.get_current_scene())->set_alpha(SDL_GetTicks()*0.0005*2*M_PI); 
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
