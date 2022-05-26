#include <SDL2/SDL.h>

#include <stdio.h> //DEBUG

#include "Level.h"
#include "Square.h"
#include "Character.h"
#include "geometry.h"
#include "Platform.h"
#include "Camera2D.h"
#include "makeLevel.h"
#include "gameEnv.h"
#include "Quadtree.h"

Level::Level(Square* tab_square, Character* tab_character[], int nb_square, int nb_character, Square background)
{
    this->tab_square = tab_square;
    this->nb_square = nb_square;
    this->tab_character = tab_character;
    this->nb_character = nb_character ; 
    this->selected_character = 0;
    this->current_character = tab_character[this->selected_character]; 
    this->nb_character_end = 0 ;
    this->alpha = 0.0;

    this->background = background ; 

    for (int i=0 ; i<this->nb_square ; i++){
        this->tab_square[i].set_textID(Game_Environment::gentexture("images/plateforme.png"));
    }
}

int Level::get_nb_square()
{
    return this->nb_square;
}

void Level::set_current_character(int new_current)
{
    this->current_character = tab_character[new_current];
}

Character* Level::get_current_character(){  
    return this->current_character;
}

void Level::set_nb_character_end(int nb_character_end)
{
    this->nb_character_end = nb_character_end;
}

int Level::get_nb_character_end()
{
    return this->nb_character_end;
}

void Level::set_alpha(float alpha)
{
    this->alpha = alpha;
}

int Level::get_nb_character(){  
    return this->nb_character;
}

void Level::reset_level(){
    this->selected_character = 0;
    this->current_character = tab_character[this->selected_character]; 
    this->nb_character_end = 0 ;
    this->alpha = 0.0;
    for (int i=0 ; i < this->nb_character; i++){
        (this->tab_character[i])->set_pos_x((this->tab_character[i])->get_start_pos().x); 
        (this->tab_character[i])->set_pos_y((this->tab_character[i])->get_start_pos().y); 
        (this->tab_character[i])->set_has_win(0); 
    }
}

void Level::manageEvents(SDL_Event e)
{   
    if (e.key.keysym.sym == SDLK_SPACE) {
        this->selected_character = (this->selected_character+1)%this->nb_character; 
        this->set_current_character(this->selected_character);
    }else {
        this->current_character->manageEvents(e);
    }

    verif_end_pos(); 
 
}

void Level::verif_end_pos(){
    int c_posX = current_character->get_current_pos().x ; 
    int c_posY = current_character->get_current_pos().y ; 
    int e_posX = current_character->get_pos_end().x ; 
    int e_posY = current_character->get_pos_end().y ; 

    if( (c_posX == e_posX && c_posY == e_posY) && !(current_character->get_has_win())){
        current_character->set_has_win(1); 
        this->nb_character_end += 1 ;
    }
}

void Level::draw()
{
    if (this->nb_character == 2){
        tab_square[11].set_pos_y(46.25+12.5*sin(this->alpha));
        tab_square[10].set_pos_x(160+15*sin(this->alpha));  
    }
    else if (this->nb_character == 1){
        tab_square[8].set_pos_y(72.5+10*sin(this->alpha));
    } 
    
    this->level_cam.set_position({current_character->get_current_pos().x-30,current_character->get_current_pos().y});
   
    glPushMatrix();
    glTranslatef(-level_cam.pos.x,-level_cam.pos.y*0.2,0);

    this->background.draw_square();

    this->current_character->draw_indice();
    for (int i=0 ; i < this->nb_character; i++){
        this->tab_character[i]->get_end_zone().draw_square();
        this->tab_character[i]->draw_character(); 
        
    }
    for (int i=0 ; i<this->nb_square ; i++){
        this->tab_square[i].draw_square(); 
    }
    glPopMatrix();
    
}

void Level::collisions(Character* chara){

    //collisions character/platform
    for (int j=0 ; j< this->nb_square ; j++) {   
        switch (this->verif_intersection(chara,tab_square[j])) {
            case 4 : 
                //pas de collision
            break ; 
            case 0:
                 chara->set_pos_y(this->tab_square[j].get_current_pos().y + this->tab_square[j].get_height()*0.5+chara->get_height()*0.5)  ;
                 chara->set_speed_y(0);
                 chara->set_jump(0);          
            break;
            case 1:
                chara->set_pos_x(this->tab_square[j].get_current_pos().x + this->tab_square[j].get_width()*0.5+chara->get_width()*0.5)  ;
                chara->set_speed_x(-chara->get_speed_x());
            break;
            case 2:
                chara->set_pos_y(this->tab_square[j].get_current_pos().y - this->tab_square[j].get_height()*0.5-chara->get_height()*0.5)  ;
            break;
            case 3:
                chara->set_pos_x(this->tab_square[j].get_current_pos().x - (this->tab_square[j].get_width()*0.5 + chara->get_width()*0.5))  ;
                chara->set_speed_x(-chara->get_speed_x());
            break;
        }
    } 
    //collisions character/character
    for (int j=0 ; j< this->nb_character ; j++) {
        if (selected_character != j){
        switch (this->verif_intersection(chara,*(Square*)tab_character[j])) {
            case 4 : 
                //pas de collision
            break ; 
            case 0:
                 chara->set_pos_y(this->tab_character[j]->get_current_pos().y+(*(Square*)this->tab_character[j]).get_height()*0.5+chara->get_height()*0.5)  ;
                 chara->set_speed_y(0);
                 chara->set_jump(0);                 
            break;
            case 1:
                chara->set_pos_x(this->tab_character[j]->get_current_pos().x+(*(Square*)this->tab_character[j]).get_width()*0.5+chara->get_width()*0.5)  ;
                chara->set_speed_x(-chara->get_speed_x());
            break;
            case 2:
                chara->set_pos_y(this->tab_character[j]->get_current_pos().y-(*(Square*)this->tab_character[j]).get_height()*0.5-chara->get_height()*0.5)  ;
                chara->set_speed_y(0);
            break;
            case 3:
                chara->set_pos_x(this->tab_character[j]->get_current_pos().x - (*(Square*)this->tab_character[j]).get_width()*0.5-chara->get_width()*0.5)  ;
                chara->set_speed_x(-chara->get_speed_x());
            break;
        }
        }
    }
}

bool Level::opposite_side(Position A,Position B,Position M,Position P){
    Position AB = B-A;
    Position AM = M-A;
    Position AP = P-A;
    float r1 = AB ^ AM;
    float r2 = AB ^ AP;
    return (r1*r2 < 0) ;    // retourne vrai si les signes de r1 et r2 sont +    // retourne vrai si les signes de r1 et r2 sont -

}

int Level::verif_intersection(Character* R1,Square R2){

   Position tab_R1[4] = {R1->get_left_upper_corner() , R1->get_right_upper_corner(), R1->get_right_lower_corner(), R1->get_left_lower_corner()} ; 
   Position tab_R2[4] = {R2.get_left_upper_corner() , R2.get_right_upper_corner(), R2.get_right_lower_corner(), R2.get_left_lower_corner()} ; 

   float deplacement = 100; 
   int indice = 4 ; 
   float temp=0;

   for (int i=0 ; i<4 ; i++){
        for (int j=0 ; j<4 ; j++){
            if (opposite_side(tab_R2[j%4],tab_R2[(j+1)%4],tab_R1[i%4],tab_R1[(i+1)%4])  &&  opposite_side(tab_R1[i%4],tab_R1[(i+1)%4],tab_R2[j%4],tab_R2[(j+1)%4])){
                switch (j){
                    case 0:
                    temp = R2.get_current_pos().y+0.5*R2.get_height()+0.5*R1->get_height()-R1->get_current_pos().y;
                    if (deplacement>temp){
                        deplacement = temp;
                        indice = j;
                    }
                    break;
                    case 1:
                    temp = R2.get_current_pos().x+0.5*R2.get_width()+0.5*R1->get_width()-R1->get_current_pos().x;
                    if (deplacement>temp){
                        deplacement = temp;
                        indice = j;
                    }
                    break;
                    case 2:
                    temp = R1->get_current_pos().y - (R2.get_current_pos().y-0.5*R2.get_height()-0.5*R1->get_height());
                    if (deplacement>temp){
                        deplacement = temp;
                        indice = j;
                    }
                    break;
                    case 3:
                    temp = R1->get_current_pos().x - (R2.get_current_pos().x-0.5*R2.get_width()-0.5*R1->get_width());
                    if (deplacement>temp){
                        deplacement = temp;
                        indice = j;
                    }
                    break;

                }
                        
            }
 
        }   
    }
       return indice;
   }

