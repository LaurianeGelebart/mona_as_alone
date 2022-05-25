#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "gameEnv.h"
#include "constants.h"
#include "Menu.h"
#include "Win.h"

Game_Environment::Game_Environment(Level** tab_level, Menu* menu, Win* win){
	this->menu = menu ; 
	this->tab_level =tab_level ;
	this->win = win ;
	this->current_scene = menu ;
	this->game_loop = 1 ;
	}

Game_Environment::Game_Environment(){}

void Game_Environment::change_to_menu(){
	this->current_scene = this->menu ; 
}

void Game_Environment::change_to_win(){
	this->current_scene = this->win ; 
}

void Game_Environment::change_to_level(int level){
	this->current_scene = this->tab_level[level] ; 
	((Level*)this->get_current_scene())->reset_level(); 
}

Scene * Game_Environment::get_current_scene(){ 
	return this->current_scene ; 
} 

int Game_Environment::is_playing(){
	return this->game_loop;
}

int Game_Environment::is_in_menu(){
	return this->current_scene == this->menu;
}

int Game_Environment::is_in_win(){
	return this->current_scene == this->win;
}

void Game_Environment::is_win(){
	printf("\n %d", ((Level*)this->get_current_scene())->get_nb_character_end()); 
	if (((Level*)this->get_current_scene())->get_nb_character_end() == ((Level*)this->get_current_scene())->get_nb_character()){ 
		this->change_to_win();
	}
}
GLuint Game_Environment::gentexture(std::string path)
{
	
	SDL_Surface *surface = IMG_Load(path.c_str());
	if(surface == NULL){
		printf("Erreur chargement image\n");
	return EXIT_FAILURE;
	}
	GLuint textureID;
	glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB,
        surface->w, surface->h, 0,
        GL_RGB, GL_UNSIGNED_BYTE, surface->pixels
    );
    glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}

void Game_Environment::manageEvents(){

	SDL_Event e;
	while(SDL_PollEvent(&e)) 
	{

		switch(e.type) 
		{
			//Quitter le jeu --> l'utilisateur ferme la fenetre
			case SDL_QUIT :
				this->game_loop = 0;
			break;

			//Event Fenetre 
			case SDL_WINDOWEVENT:
				switch (e.window.event) 
				{
					//Redimensionnement fenetre
					case SDL_WINDOWEVENT_RESIZED:
						onWindowResized(e.window.data1, e.window.data2);                
						break;

					default:
						break; 
				}
			break;
			
			//Touche clavier
			case SDL_KEYDOWN:

				//printf("%p :: %p\n", this->menu, this->current_scene); //DEBUG

				//Quitter le jeu --> l'utilisateur appuie sur Q ou Echap 
				if (e.key.keysym.sym == SDLK_q)
				{
					this->game_loop = 0;
				}
				//Passage à un niveau --> l'utilisateur appuie sur entrée pour valider
				if (this->is_in_menu() && (e.key.keysym.sym == SDLK_RETURN))
				{
					this->change_to_level(this->menu->get_selected_level());
				}
				//Passage au lorsque l'utilisateur à gagné --> l'utilisateur appuie sur entrée pour valider
				else if (this->is_in_win() && (e.key.keysym.sym == SDLK_RETURN))
				{
					this->change_to_menu();
				}
				//Passage au menu --> l'utilisateur appuie sur M ou echap
				else if(!this->is_in_menu() && !this->is_in_win() && (e.key.keysym.sym == SDLK_m || e.key.keysym.sym == SDLK_ESCAPE))
				{
					this->change_to_menu();
				} 
				//Si l'event n'est pas connu ici on cherche dans ceux de la scène courante
				else {
					 if (this->is_in_menu()){
						((Menu*)this->get_current_scene())->manageEvents(e);
					} else if (!this->is_in_win() && !this->is_in_menu()){
						((Level*)this->get_current_scene())->manageEvents(e);
					}
				}
			break;

			default:
			break;
		}
	}	
}


void Game_Environment::onWindowResized(unsigned int width, unsigned int height)
{ 
    float aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1) 
    {
        gluOrtho2D(
        0, GL_VIEW_SIZE * aspectRatio, 
        0, GL_VIEW_SIZE);
    }
    else
    {
        gluOrtho2D(
        0, GL_VIEW_SIZE,
       0, GL_VIEW_SIZE / aspectRatio);
    }
}
