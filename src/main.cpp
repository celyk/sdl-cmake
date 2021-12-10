#include<SDL.h>

float clamp(float x, float e0, float e1){
	return (((x<e0)?e0:x)>e1)?e1:x;
}
float smoothstep(float x, float e0, float e1){
	x = clamp((x-e0)/(e1-e0),0.f,1.f);
	return x*x*(3.f-2.f*x);
}

int main(int argc, char* argv[]){
	SDL_Window* sdl_window;
	SDL_Renderer* sdl_renderer;

	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) < 0 ) {
		SDL_Log("SDL init failed: %s", SDL_GetError());
		SDL_ClearError();
	}

	Uint32 flags = SDL_WINDOW_BORDERLESS|SDL_WINDOW_FULLSCREEN_DESKTOP;

	sdl_window = SDL_CreateWindow("hi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, flags);
	if( !sdl_window ) {
		SDL_Log("Creating window failed: %s", SDL_GetError());
		SDL_ClearError();
	}

	SDL_ShowCursor(SDL_DISABLE);

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
	float t = 0.f;


	bool window_should_close = false;
	float t0 = 0.f;
	SDL_Event sdl_event;
	while( t0>=0.f ){
		while(SDL_PollEvent(&sdl_event)){
			if(sdl_event.type == SDL_QUIT) { 
				window_should_close = true;
			}
		}
		if(window_should_close) t0-=.0004f;
		else if( t0<1. )t0+=.0004f;

		t = SDL_GetTicks()/1000.;
		SDL_SetWindowOpacity(sdl_window, smoothstep(t0,0.f,1.f));

		SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
		SDL_RenderClear(sdl_renderer);
		SDL_RenderPresent(sdl_renderer);7
	}
	
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();

	return 0;
}