#include<SDL.h>

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

	bool window_should_close = false;
	SDL_Event sdl_event;
	while(SDL_PollEvent(&sdl_event)){
		if(sdl_event.type == SDL_QUIT) { 
			window_should_close = true;
		}
	}
	
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();

	return 0;
}