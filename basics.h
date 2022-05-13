#ifndef BASICS_H
#define BASICS_H

struct Position
{
    float x;
    float y;
};

struct Color
{
    float r;
    float g;
    float b;
};

struct Square
{
    int width; 
    int height; 
    Position pos_square; 
};

struct Vect{
	float x;
	float y;
};

const double dt = 0.001;
const double g = 2.0;

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 50.;  

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "OPENGL";

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void onWindowResized(unsigned int width, unsigned int height);
void drawOrigin(); 
void drawSquare(int filled);  

#endif
