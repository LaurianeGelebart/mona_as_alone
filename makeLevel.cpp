#include "Menu.h"
#include "Level.h"
#include "makeLevel.h"
#include "Character.h"
#include "Platform.h"
#include "gameEnv.h"

void makeMenu(Menu* menu){}

void makeLevel(Level** tab_level,Character** tab_character ){

    ////////////////////////////////////////////
    
    Character* chara1 = new Character(11,7,2,{10,30},{10,20});  
    chara1->set_textID(Game_Environment::gentexture("images/character1.png"));

    Character* chara2 = new Character(5,7,1,{30,50},{30,17});
    chara2->set_textID(Game_Environment::gentexture("images/character2.png"));

    Character* chara3 = new Character(3,15,3.5,{20,50},{80,80});
    chara3->set_textID(Game_Environment::gentexture("images/character3.png"));

    tab_character[0] = chara1 ; 
    tab_character[1] = chara2 ; 
    tab_character[2] = chara3 ; 

    ////////////////////////////////////
    //NIVEAU1
    ////////////////////////////////////
    Platform* tab_square1 = new Platform[10]; 

    tab_square1[0]=Platform(70, 49.5, {35, 2.25});
    tab_square1[1]=Platform(75, 27, {122.5, 13.5});
    tab_square1[2]=Platform(15, 72, {167.5, 36});
    tab_square1[3]=Platform(60, 13.5, {130, 65.5});
    tab_square1[4]=Platform(15, 108, {92.5, 113});
    tab_square1[5]=Platform(55, 13.5, {27.5, 119.25});
    tab_square1[6]=Platform(25, 4.5, {77.5, 61});
    tab_square1[7]=Platform(25, 4.5, {77.5, 96.75});
    tab_square1[8]=Platform(15, 4.5, {222.5, 6.75});
    tab_square1[9]=Platform(15, 4.5, {182.5, 38.25});
    Square background1 = Square(270, 140, {128, 57.5});
    background1.set_textID(Game_Environment::gentexture("images/level1.png"));

    ////////////////////////////////////
    //NIVEAU2
    ////////////////////////////////////
    Platform* tab_square2 = new Platform[9]; 

    tab_square2[0]=Platform(150, 20, {75, 10});
    tab_square2[1]=Platform(10, 5, {115, 22.5});
    tab_square2[2]=Platform(10, 25, {135, 32.5});
    tab_square2[3]=Platform(10, 35, {145, 37.5});
    tab_square2[4]=Platform(60, 5, {80, 82.5});
    tab_square2[5]=Platform(40, 50, {80, 55});
    tab_square2[6]=Platform(40, 10, {20, 75});
    tab_square2[7]=Platform(10, 5, {55, 52.5});
    tab_square2[8]=Platform(20, 5, {130, 72.5});
    Square background2 = Square(270, 140, {128, 57.5});
    background2.set_textID(Game_Environment::gentexture("images/level2.png"));

    ////////////////////////////////////
    //NIVEAU3
    ////////////////////////////////////
    Platform* tab_square3 = new Platform[12]; 

    tab_square3[0]= Platform(40, 15, {20, 7.5});
    tab_square3[1]= Platform(35, 15, {72.5, 7.5});
    tab_square3[2]= Platform(20, 32.5, {160, 48.75});
    tab_square3[3]= Platform(40, 27.5, {110, 13.75});
    tab_square3[4]= Platform(50, 15, {105, 57.5});
    tab_square3[5]= Platform(80, 25, {40, 62.5});
    tab_square3[6]= Platform(10, 2.5, {145, 38.75});
    tab_square3[7]= Platform(30, 27.5, {205, 13.75});
    tab_square3[8]= Platform(10, 5, {175, 62.25});
    tab_square3[9]= Platform(12.5, 2.5, {136, 51});
    tab_square3[10]= Platform(30, 2.5, {160, 26.25}); 
    tab_square3[11]= Platform(20, 2.5, {190, 46.25});
    Square background3 = Square(270, 140, {128, 57.5});
    background3.set_textID(Game_Environment::gentexture("images/level3.png"));

    //Création des niveaux
    Level* level1 = new Level(tab_square1, tab_character, 10, 1, background1);
    Level* level2 = new Level(tab_square2, tab_character, 9, 2, background2);
    Level* level3 = new Level(tab_square3, tab_character, 12, 3, background3); //bien penser à refaire un nouveau perso
    tab_level[0] = level1 ;   
    tab_level[1] = level2 ;
    tab_level[2] = level3 ;  
    //////////////////////////////////////////
}