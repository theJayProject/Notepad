#include <iostream>
#include "SDL.h"
#include <SDL_ttf.h>
#define MY_FONT "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
int main(int argc, char** argv) {
	//Error handling
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	std::cout << "Failed to initialise SDL Library\n";
	return -1;
}
	//Creating Window
	SDL_Window* window = SDL_CreateWindow("Noted",
		10, 10, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//Creating Window Surface
	SDL_Surface* window_surface = SDL_GetWindowSurface(window);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	//Error handling
	if (!window) {
		std::cout << "Failed to create window\n";
		return -1;
	}
	

//Adding Ability to add Text
	std::string text;
	SDL_StartTextInput();
	//ADDING YOUR OWN FONT AND IT NOT LOADING
	TTF_Font* font = TTF_OpenFont(MY_FONT, 64);
	//	Error handling
	if (!font) {
		printf("Failed to load font: %s\n", TTF_GetError());
		//		return -1;
	}
	if (TTF_Init() < 0) {
		printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
		return -1;
	}  
	// Create surface with rendered text
	TTF_Font* font;
	SDL_Color textColor = { 0, 0, 0, 255 }; // black color
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello World!", textColor);

	if (!textSurface) {
		printf("Failed to create text surface: %s\n", TTF_GetError());
		return -1;
	}
	// Create texture from surface
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (!textTexture) {
		printf("Failed to create text texture: %s\n", SDL_GetError());
		return -1;
	}



//Event Updates
	bool keep_window_open = true;
	while (keep_window_open) {
	
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0){
			{
				switch (e.type) {
				case (SDL_TEXTINPUT || SDL_KEYDOWN):
					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
						text = text.substr(0, text.length() - 1);
					}
					else if (e.type == SDL_TEXTINPUT) {
						text += e.text.text;
					}
					std::cout << text << "\n";
				case SDL_QUIT:
					keep_window_open = false;
					break;
						

				}
			}
			SDL_UpdateWindowSurface(window);
		}
	}
	SDL_StopTextInput();
	return 0;
}