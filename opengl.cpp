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

float alpha=0.0;

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
    Square tab_square[12]; 

    //////////////////////////////////////////
    Square square1;
    square1.width =40;
    square1.height=15;
    square1.pos_square.x=20;
    square1.pos_square.y=7.5;
    tab_square[0]=square1;

    Square square2;
    square2.width =35;
    square2.height=15;
    square2.pos_square.x=72.5;
    square2.pos_square.y=7.5;
    tab_square[1]=square2;

    Square square3;
    square3.width =20;
    square3.height=32.5;
    square3.pos_square.x=160;
    square3.pos_square.y=48.75;
    tab_square[2]=square3;

    Square square4;
    square4.width =40;
    square4.height=27.5;
    square4.pos_square.x=110;
    square4.pos_square.y=13.75;
    tab_square[3]=square4;

    Square square5;
    square5.width =50;
    square5.height=15;
    square5.pos_square.x=105;
    square5.pos_square.y=57.5;
    tab_square[4]=square5;

    Square square6;
    square6.width =80;
    square6.height=25;
    square6.pos_square.x=40;
    square6.pos_square.y=62.5;
    tab_square[5]=square6;

    Square square7;
    square7.width =10;
    square7.height=2.5;
    square7.pos_square.x=145;
    square7.pos_square.y=38.75;
    tab_square[6]=square7;

    Square square8;
    square8.width =30;
    square8.height=27.5;
    square8.pos_square.x=205;
    square8.pos_square.y=13.75;
    tab_square[7]=square8;

    Square square9;
    square9.width =10;
    square9.height=5;
    square9.pos_square.x=175;
    square9.pos_square.y=62.25;
    tab_square[8]=square9;

    Square square10;
    square10.width =30;
    square10.height=2.5;
    square10.pos_square.x=(160+15*sin(alpha));
    square10.pos_square.y=26.25;
    tab_square[9]=square10;

    Square square11;
    square10.width =30;
    square10.height=2.5;
    square10.pos_square.x=160; //+15*sin(alpha)); avec alpha=elapsedTime
    square10.pos_square.y=26.25;
    tab_square[10]=square11;
    //////////////////////////////////////////

    //Création du niveau 1
    Level level1 ; 
    level1.init_level(tab_square, tab_character, 1, 12); 

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
        Square square10;
        square10.width =30;
        square10.height=2.5;
        square10.pos_square.x=(160+15*sin(alpha));
        square10.pos_square.y=26.25;
        tab_square[9]=square10;

        level1.draw();
        
 
        //Echange du front et du back buffer : mise a jour de la fenetre/
        SDL_GL_SwapWindow(window);
        
        /* Boucle traitant les evenements */
        loop = level1.event(); 

        //Calcul du temps ecoule
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        alpha = elapsedTime/100.0;

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
