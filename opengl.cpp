#include <SDL2/SDL.h>
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
  


    Position pos_chara1;    //faire fonction pour ça
    pos_chara1.x =2;
    pos_chara1.y =5;
    Position end_pos_chara1;
    end_pos_chara1.x =30;
    end_pos_chara1.y =0.5;
    Vect acc1;
    acc1.x=0;
    acc1.y=1;

    Character* chara1 = new Character(10,4,pos_chara1,end_pos_chara1);
    Character* tab_character[4] ; 
    tab_character[0] = chara1 ; 
    Square tab_square[4] ; 
    Menu* menu = new Menu();
    Level* tab_level[3] ;

    printf("%p\n", menu);

    //Création du niveau 1
    Level* level1 = new Level(tab_square, tab_character, 1);
    Level* level2 = new Level(tab_square, tab_character, 1);
    tab_level[0] = level1 ; 
    Game_Environment environment = Game_Environment(tab_level, menu);
    environment.change_to_level(0); 

    environment.onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);
    /* ------------------------------ LOOP ------------------------------ */

    while(environment.is_playing()) 
    {
        environment.manageEvents();

        //Recuperation du temps au debut de la boucle
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();       
 
        //Echange du front et du back buffer : mise a jour de la fenetre/
        
        /* Boucle traitant les evenements */
        //loop = scene->get_current_scene()->event(); 
        
        //dessine la scene
        // level1->draw();
        if (environment.is_in_menu()){
            ((Menu*)environment.get_current_scene())->draw();
        } else {
            ((Level*)environment.get_current_scene())->get_current_character()->set_position();
            ((Level*)environment.get_current_scene())->draw();
        }
        printf("%p :: %p :: %p :: %p\n", environment.get_current_scene(), menu, level1, level2);

        SDL_GL_SwapWindow(window);
        //Calcul du temps ecoule
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

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
