#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gameEnv.h"
#include "constants.h"
#include "Menu.h"

Game_Environment::Game_Environment(Level** tab_level, Menu* menu):menu(menu), tab_level(tab_level), current_scene(menu), game_loop(1){}

Game_Environment::Game_Environment(){}

void Game_Environment::change_to_menu(){
	this->current_scene = this->menu ; 
}

void Game_Environment::change_to_level(int level){
	this->current_scene = this->tab_level[level] ; 
}
Scene * Game_Environment::get_current_scene(){ 
	return this->current_scene ; 
} 

void Game_Environment::manageEvents(){
	 //printf("%p\n", tab_level);

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
				//Passage au menu --> l'utilisateur appuie sur M ou echap
				else if(!this->is_in_menu() && (e.key.keysym.sym == SDLK_m || e.key.keysym.sym == SDLK_ESCAPE))
				{
					this->change_to_menu();
				} 
				//Si l'event n'est pas connu ici on cherche dans ceux de la scène courante
				else {
					 if (this->is_in_menu()){
						((Menu*)this->get_current_scene())->manageEvents(e);
					} else {
						((Level*)this->get_current_scene())->manageEvents(e);
					}
				}
			break;

			default:
			break;
		}
	}
}

int Game_Environment::is_playing(){
	return this->game_loop;
}

int Game_Environment::is_in_menu(){
	return this->current_scene == this->menu;
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