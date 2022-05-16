#ifndef MENU_H
#define MENU_H 


class Menu : public Scene
{
    private:
       

    public:
        void draw();
        int event();
        Menu(Scene** tab_level, Scene* menu) {
            //
        }; 
        
}; 

#endif