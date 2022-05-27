#include "Menu.h"
#include "Level.h"
#include "makeLevel.h"
#include "Character.h"
#include "Platform.h"
#include "gameEnv.h"

void makeMenu(Menu* menu){}

void makeLevel(Level** tab_level,Character** tab_character ){

    ////////////////////////////////////////////
    
    Character* chara1 = new Character(11,7,1.0,{10,30},{10,20});  
    chara1->set_textID(Game_Environment::gentexture("images/character1.png"));

    Character* chara2 = new Character(5,7,1.7,{30,50},{30,17});
    chara2->set_textID(Game_Environment::gentexture("images/character2.png"));

    Character* chara3 = new Character(3,15,3.0,{20,50},{80,80});
    chara3->set_textID(Game_Environment::gentexture("images/character3.png"));

    tab_character[0] = chara1 ; 
    tab_character[1] = chara2 ; 
    tab_character[2] = chara3 ; 
    

    ////////////////////////////////////
    //NIVEAU1
    ////////////////////////////////////
    Platform* tab_square1 = new Platform[16]; 

    tab_square1[0]=Platform(70, 49.5, {35, 2.25});
    tab_square1[1]=Platform(75, 27, {122.5, 13.5});
    tab_square1[2]=Platform(15, 72, {167.5, 36});
    tab_square1[3]=Platform(60, 13.5, {130, 65.5});
    tab_square1[4]=Platform(15, 48, {92.5, 83});
    tab_square1[5]=Platform(55, 13.5, {27.5, 119.25});
    tab_square1[6]=Platform(25, 4.5, {77.5, 61});
    tab_square1[7]=Platform(25, 4.5, {77.5, 96.75});
    tab_square1[8]=Platform(15, 4.5, {212, 0});
    tab_square1[9]=Platform(15, 4.5, {182.5, 15});
    tab_square1[10]=Platform(200, 10, {120, -17.25});
    tab_square1[11]=Platform(15, 4.5, {212, 30});
    tab_square1[12]=Platform(15, 4.5, {182.5, 45});
    tab_square1[13]=Platform(28, 4.5, {212, 60});
    tab_square1[14]=Platform(2, 112.5, {1, 58});
    tab_square1[15]=Platform(22, 112.5, {228, 58});
    Square background1 = Square(270, 140, {128, 56});
    background1.set_textID(Game_Environment::gentexture("images/level1.png"));

    ////////////////////////////////////
    //NIVEAU2
    ////////////////////////////////////
    Platform* tab_square2 = new Platform[10]; 

    tab_square2[0]=Platform(150, 20, {75, 10});
    tab_square2[1]=Platform(10, 6, {115, 22.5});
    tab_square2[2]=Platform(10, 25, {135, 27});
    tab_square2[3]=Platform(10, 35, {145, 32.5});
    tab_square2[4]=Platform(70, 5, {80, 87});
    tab_square2[5]=Platform(40, 39, {80, 50});
    tab_square2[6]=Platform(40, 10, {20, 75});
    tab_square2[7]=Platform(10, 5, {55, 39.5});
    tab_square2[8]=Platform(20, 5, {125, 72}); //plateforme
    tab_square2[9]=Platform(5, 125, {1, 60});
    
   
    Square background2 = Square(270, 140, {128, 65});
    background2.set_textID(Game_Environment::gentexture("images/level2.png"));

    ////////////////////////////////////
    //NIVEAU3
    ////////////////////////////////////
    Platform* tab_square3 = new Platform[13]; 

    tab_square3[0]= Platform(40, 15, {20, 7.5});
    tab_square3[1]= Platform(35, 15, {72.5, 7.5});
    tab_square3[2]= Platform(20, 32.5, {160, 48.75});
    tab_square3[3]= Platform(40, 27.5, {110, 13.75});
    tab_square3[4]= Platform(50, 15, {105, 57.5});
    tab_square3[5]= Platform(80, 25, {40, 62.5});
    tab_square3[6]= Platform(10, 2.5, {145, 38.75});
    tab_square3[7]= Platform(30, 27.5, {205, 13.75});
    tab_square3[8]= Platform(10, 5, {175, 62.25});
    tab_square3[9]= Platform(12.5, 2.5, {136, 53});
    tab_square3[10]= Platform(30, 2.5, {160, 26.25}); 
    tab_square3[11]= Platform(20, 2.5, {190, 46.25});

    tab_square3[12]=Platform(5, 125, {1, 60});
    Square background3 = Square(270, 140, {128, 57.5});
    background3.set_textID(Game_Environment::gentexture("images/level3.png"));

    //Création des niveaux
    Level* level1 = new Level(tab_square1, tab_character, 16, 1, background1);
    Level* level2 = new Level(tab_square2, tab_character, 10, 2, background2);
    Level* level3 = new Level(tab_square3, tab_character, 13, 3, background3); //bien penser à refaire un nouveau perso
    tab_level[0] = level1 ;   
    tab_level[1] = level2 ;
    tab_level[2] = level3 ;  
    //////////////////////////////////////////
}