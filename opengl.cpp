#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
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

    Menu* menu = new Menu();
    Level* tab_level[12] ;


    ////////////////////////////////////////////
    //A mettre dans Make level 
    ////////////////////////////////////////////
    Position pos_chara1;    
    pos_chara1.x =2;
    pos_chara1.y =5;
    Position end_pos_chara1;
    end_pos_chara1.x =30; 
    end_pos_chara1.y =0.5;
    Vect acc1;
    acc1.x=0;
    acc1.y=1;
    Character* chara1 = new Character(10,4,pos_chara1,end_pos_chara1);

    Position pos_chara2;    
    pos_chara1.x =2;
    pos_chara1.y =50;
    Character* chara2 = new Character(5,7,pos_chara1,end_pos_chara1);

    Character* tab_character[4] ; 
    tab_character[0] = chara1 ; 
    tab_character[1] = chara2 ; 
    Square tab_square[12] ; 


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
    square11.width =30;
    square11.height=2.5;
    square11.pos_square.x=160; //+15*sin(alpha)); avec alpha=elapsedTime
    square11.pos_square.y=26.25;
    tab_square[10]=square11;

    //Création du niveau 1
    Level* level1 = new Level(tab_square, tab_character, 12, 2);
    Level* level2 = new Level(tab_square, tab_character, 12,  2);
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
            //printf("\n%p----------2------------\n",((Level*)environment.get_current_scene())->tab_character[0]);
            ((Level*)environment.get_current_scene())->get_current_character()->set_position(); 
            for (int i=0 ; i<((Level*)environment.get_current_scene())->get_nb_character() ; i++) {
                ((Level*)environment.get_current_scene())->tab_character[i]->gravity(); 
            } // printf("%p\n", tab_level);
            ((Level*)environment.get_current_scene())->draw();
        }
        //printf("%p :: %p :: %p :: %p\n", environment.get_current_scene(), menu, level1, level2);
        
        /*glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID);
       
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);*/    
     
        //Echange du front et du back buffer : mise a jour de la fenetre
        SDL_GL_SwapWindow(window);

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
    /*glDeleteTextures(1,&textureID); //appeler sur les objets avec une methode freesurface
    SDL_FreeSurface(surface);*/
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
