#include "Menu.h"
#include "Level.h"
#include "makeLevel.h"
#include "Character.h"

void makeMenu(Menu* menu){}

void makeLevel(Level** tab_level){

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
    Character* tab_character[4] ; 
    tab_character[0] = chara1 ; 
    Square tab_square[12] ; 

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
    square10.pos_square.x=160+15*sin(1);
    square10.pos_square.y=26.25;
    tab_square[9]=square10;

    Square square11;
    square11.width =30;
    square11.height=2.5;
    square11.pos_square.x=160; //+15*sin(alpha)); avec alpha=elapsedTime
    square11.pos_square.y=26.25;
    tab_square[10]=square11;
    //////////////////////////////////////////

    //Création du niveau 1
    Level* level1 = new Level(tab_square, tab_character, 12, 1);
    Level* level2 = new Level(tab_square, tab_character, 12,  1);
    tab_level[0] = level1 ;   
    tab_level[1] = level2 ; 

    printf("\n%p----------2------------\n",tab_character[0]);

}
