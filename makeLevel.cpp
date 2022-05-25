#include "Menu.h"
#include "Level.h"
#include "makeLevel.h"
#include "Character.h"
#include "Platform.h"

void makeMenu(Menu* menu){}

void makeLevel(Level** tab_level,Character** tab_character ){

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

    //Character* tab_character[4] ; 
    
    tab_character[0] = chara1 ; 
    tab_character[1] = chara2 ; 

    ////////////////////////////////////
    //NIVEAU1
    ////////////////////////////////////
    Platform tab_square1[10] ; 

    Platform square11 = Platform(70, 49.5, {35, 2.25});
    tab_square1[0]=square11;

    Platform square12 = Platform(75, 27, {122.5, 13.5});
    tab_square1[1]=square12;

    Platform square13 = Platform(15, 72, {167.5, 36});
    tab_square1[2]=square13;

    Platform square14 = Platform(60, 13.5, {130, 65.5});
    tab_square1[3]=square14;

    Platform square15 = Platform(15, 108, {92.5, 113});
    tab_square1[4]=square15;

    Platform square16 = Platform(55, 13.5, {27.5, 119.25});
    tab_square1[5]=square16;

    Platform square17 = Platform(25, 4.5, {77.5, 61});
    tab_square1[6]=square17;

    Platform square18 = Platform(25, 4.5, {77.5, 96.75});
    tab_square1[7]=square18;

    Platform square19 = Platform(15, 4.5, {222.5, 6.75});
    tab_square1[8]=square19;

    Platform square110 = Platform(15, 4.5, {182.5, 38.25});
    tab_square1[9]=square110;

    ////////////////////////////////////
    //NIVEAU2
    ////////////////////////////////////
    Platform tab_square2[9] ; 

    Platform square21 = Platform(150, 20, {75, 10});
    tab_square2[0]=square21;

    Platform square22 = Platform(10, 5, {115, 22.5});
    tab_square2[1]=square22;

    Platform square23 = Platform(10, 25, {135, 32.5});
    tab_square2[2]=square23;

    Platform square24 = Platform(10, 35, {145, 37.5});
    tab_square2[3]=square24;

    Platform square25 = Platform(60, 5, {80, 82.5});
    tab_square2[4]=square25;

    Platform square26 = Platform(40, 50, {80, 55});
    tab_square2[5]=square26;

    Platform square27 = Platform(40, 10, {20, 75});
    tab_square2[6]=square27;

    Platform square28 = Platform(10, 5, {55, 52.5});
    tab_square2[7]=square28;

    Platform square29 = Platform(20, 5, {130, 72.5});
    tab_square2[8]=square29;

    ////////////////////////////////////
    //NIVEAU3
    ////////////////////////////////////
    Platform tab_square3[12] ; 

    Platform square31 = Platform(40, 15, {20, 7.5});
    tab_square3[0]=square31;

    Platform square32 = Platform(35, 15, {72.5, 7.5});
    tab_square3[1]=square32;

    Platform square33 = Platform(20, 32.5, {160, 48.75});
    tab_square3[2]=square33;

    Platform square34 = Platform(40, 27.5, {110, 13.75});
    tab_square3[3]=square34;

    Platform square35 = Platform(50, 15, {105, 57.5});
    tab_square3[4]=square35;

    Platform square36 = Platform(80, 25, {40, 62.5});
    tab_square3[5]=square36;

    Platform square37 = Platform(10, 2.5, {145, 38.75});
    tab_square3[6]=square37;

    Platform square38 = Platform(30, 27.5, {205, 13.75});
    tab_square3[7]=square38;

    Platform square39 = Platform(10, 5, {175, 62.25});
    tab_square3[8]=square39;

    Platform square310 = Platform(12.5, 2.5, {136, 51});
    tab_square3[9]=square310;

    Platform square311 = Platform(30, 2.5, {160, 26.25}); 
    tab_square3[10]=square311;  

    Platform square312 = Platform(20, 2.5, {190, 46.25}); 
    tab_square3[11]=square312;  
    ////////////////////////////////////////////

    //Création des niveaux
    Level* level1 = new Level(tab_square1, tab_character, 10, 1);
    Level* level2 = new Level(tab_square2, tab_character, 9, 2);
    Level* level3 = new Level(tab_square3, tab_character, 12, 2); //bien penser à refaire un nouveau perso
    tab_level[0] = level1 ;   
    tab_level[1] = level2 ;
    tab_level[2] = level3 ;  
    //////////////////////////////////////////

}