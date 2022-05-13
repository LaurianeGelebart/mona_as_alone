#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Variables, structures et fonctions de base
#include "basics.h"

//Class
#include "Character.h"
#include "Menu.h"
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
  

    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

    Position pos_chara1;    //faire fonction pour ça
    pos_chara1.x =0.5;
    pos_chara1.y =0.5;
    Position end_pos_chara1;
    end_pos_chara1.x =30;
    end_pos_chara1.y =0.5;
    Vect acc1;
    acc1.x=0;
    acc1.y=1;

    Character chara1 ; 
    chara1.init_Character(2,3,pos_chara1,end_pos_chara1);
    Character tab_character[4] ; 
    tab_character[0] = chara1 ; 
    Square tab_square[4] ; 

    //Création du niveau 1
    Level level1 ; 
    level1.init_level(tab_square, tab_character, 1); 

    /* ------------------------------ LOOP ------------------------------ */
    int loop = 1;
    while(loop) 
    {
        //Recuperation du temps au debut de la boucle
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        drawOrigin();

        level1.draw();
        
 
        //Echange du front et du back buffer : mise a jour de la fenetre/
        SDL_GL_SwapWindow(window);
        
        /* Boucle traitant les evenements */
        loop = level1.event(); 

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
