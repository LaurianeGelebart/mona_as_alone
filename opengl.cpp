#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "OPENGL";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 50.;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

const Uint8* keystate = SDL_GetKeyboardState(NULL);

struct Position
{
    float x;
    float y;
};

struct Character
{
    int width;
    int height;
    //Color color;
    Position start_pos;
    Position current_pos;
    Position end_pos;
    float jump_power;
    void move(int dx, int dy)
    {
        this->current_pos.x+=dx;
        this->current_pos.y+=dy;
    }

    void draw(int filled)
    {
        if(filled) 
        {
            glBegin(GL_QUADS);
        }
        else 
        {
            glBegin(GL_LINE_LOOP);
        }
        //glTexCoord2f(0.,0.);
        glVertex2f( this->current_pos.x-0.5*this->width, this->current_pos.y+0.5*this->height);
        //glTexCoord2f(1.,0.);
        glVertex2f( this->current_pos.x+0.5*this->width, this->current_pos.y+0.5*this->height);
        //glTexCoord2f(1.,1.);
        glVertex2f( this->current_pos.x+0.5*this->width, this->current_pos.y-0.5*this->height);
        //glTexCoord2f(0.,1.);
        glVertex2f( this->current_pos.x-0.5*this->width, this->current_pos.y-0.5*this->height);
        glEnd(); 
    }
};


void onWindowResized(unsigned int width, unsigned int height)
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


/* Objets cannoniques */
void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();

    glColor3fv(currentColor);
}

void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.0, 1.0);
    glVertex2f( 1.0, 1.0);
    glVertex2f( 1.0, 0.0);
    glVertex2f( 0.0, 0.0);
    glVertex2f( 0.0, 1.0);

    glEnd();
    
}
Character createCharacter(int height, int width, Position pos, Position final_pos)
{
    Character chara;
    chara.height = height;
    chara.width = width;
    chara.start_pos.x = pos.x;
    chara.start_pos.y=pos.y;
    chara.current_pos.x=chara.start_pos.x;
    chara.current_pos.y=chara.start_pos.y;
    chara.end_pos.x = final_pos.x;
    chara.end_pos.y = final_pos.y;
    return chara;
}

int main(int argc, char** argv) 
{
    //* Initialisation de la SDL */

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

    Character chara1 = createCharacter(2,3,pos_chara1,end_pos_chara1);
    
    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        drawOrigin();
        //drawRectangle(1,chara1);
        //drawSquare(1);
        chara1.draw(1);
 
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
			if(e.type == SDL_QUIT) 
			{
				loop = 0;
				break;
			}
		
			if(	e.type == SDL_KEYDOWN 
				&& (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
			{
				loop = 0; 
				break;
			}
            
            switch(e.type) 
            {
                case SDL_WINDOWEVENT:
                    switch (e.window.event) 
                    {
                        /* Redimensionnement fenetre */
                        case SDL_WINDOWEVENT_RESIZED:
                            onWindowResized(e.window.data1, e.window.data2);                
                            break;

                        default:
                            break; 
                    }
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);

                    if (e.key.keysym.sym == SDLK_UP)
                    {
                        chara1.move(0,1);
                    }
                    break;

                
                

                default:
                    break;
            }
        }
        if (keystate[SDL_SCANCODE_RIGHT])
        {
            chara1.move(1,0);
        }
        else if(keystate[SDL_SCANCODE_LEFT])
        {
            chara1.move(-1,0);
        }
        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associees a la SDL */ 
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
