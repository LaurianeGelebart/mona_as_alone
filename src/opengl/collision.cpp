#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <math.h>

typedef struct{
	double x;
	double y;
} vec;

SDL_Rect newRect(int posx, int posy, int sizex, int sizey);
void sdlInit(SDL_Window**, SDL_Surface**, int, int);
SDL_Surface* loadimg(std::string path, SDL_PixelFormat* format);

const int SCR_W = 600;
const int SCR_H = 300;

void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_QUADS);
    }
    else 
    {
        glBegin(GL_LINE_LOOP);
    }
    glTexCoord2f(0.,0.);
    glVertex2f( -0.5 , 0.5);
    glTexCoord2f(1.,0.);
    glVertex2f( 0.5 , 0.5);
    glTexCoord2f(1.,1.);
    glVertex2f( 0.5 , -0.5);
    glTexCoord2f(0.,1.);
    glVertex2f( -0.5 , -0.5);
    glEnd(); 
}

int main(int nbarg, char** arglist){
	SDL_Window* window = NULL;
	SDL_Surface* scrSurface = NULL;

	sdlInit(&window, &scrSurface, SCR_W, SCR_H);

	bool quit = false;
	SDL_Event e;
	IMG_Init(IMG_INIT_PNG);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL){
		printf("Error creating renderer\n");
		exit(5);
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/// Image loading
	SDL_Surface* img = loadimg("FirstPic.png", scrSurface->format);
	SDL_Texture* imgtexture = SDL_CreateTextureFromSurface(renderer, img);
	//

	int groundrectsize = SCR_W;
	int sqrectsize = 25; // std::min(SCR_H, SCR_W);
	SDL_Rect groundRect = newRect(SCR_W/2-groundrectsize/2, 3*SCR_H/4, groundrectsize, groundrectsize);
	SDL_Rect squareRect = newRect((SCR_W-sqrectsize)/2, (SCR_H-sqrectsize)/2, sqrectsize, sqrectsize);

	vec acc, speed, pos;
	acc.x = 0;
	acc.y = 9.8;
	speed.x = 0;
	speed.y = 0;
	pos.x = (SCR_W-sqrectsize)/2;
	pos.y = (SCR_H-sqrectsize)/2-50;
	bool in_jump = false;
	bool isFalling = false;
	int jump = 0;
	const int jumpHeight = 10;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	double dt = 0.001; //s
	double t = 0;

	while (!quit){

		//usleep(dt*1000000);
		t+=dt;

		while(SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_UP && !injump){
					speed.y = -55;
					injump = true;
					isFalling = true;	
				}
			}
		}


		if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT]){
			if (keystate[SDL_SCANCODE_LEFT]){
				speed.x = -100;
			}
			if (keystate[SDL_SCANCODE_RIGHT]){
				speed.x = 100;
			}
		} else {
			speed.x = 0;
		}


		speed.x += dt*acc.x;
		speed.y += dt*acc.y;
		pos.x += dt*speed.x;
		pos.y += dt*speed.y;


		if (pos.y+squareRect.h > groundRect.y){ //not going under the ground
			pos.y -= dt*speed.y;
			speed.y=0;
			injump = false;
		}

		squareRect.x = pos.x;
		squareRect.y = pos.y;

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, imgtexture, NULL, &squareRect);
		SDL_RenderCopy(renderer, imgtexture, NULL, &groundRect);

		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

SDL_Rect newRect(int posx, int posy, int sizex, int sizey){
	SDL_Rect r;
	r.h = sizey;
	r.w = sizex;
	r.x = posx;
	r.y = posy;
	return r;
}

void sdlInit(SDL_Window** window, SDL_Surface** scrSurface, int width, int height){
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("Error initializing : %s\n", SDL_GetError());
	} else {
		*window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (*window==NULL){
			printf("Error creating window : %s\n", SDL_GetError());
		} else {
			*scrSurface = SDL_GetWindowSurface(*window);
		}
	}
}

SDL_Surface* loadimg(std::string path, SDL_PixelFormat* format){
	SDL_Surface* img = IMG_Load(path.c_str());
	if (img != NULL){
		// img = SDL_ConvertSurface(img, format, 0);
		// if (img == NULL){
		// 	printf("error optimising surface : %s\n", SDL_GetError());
		// 	exit(2);
		// }
	} else {
		printf("error loading image : %s\n", SDL_GetError());
		exit(1);
	}
	return img;
}