//      (_||_/
//      (    )  
//     ( o  0 )
//-OOO°--(_)---°OOO---------------------------------------
//                   Copyright (C) 2026 By Johnny Jazeix
// .OOOo      oOOO.  jazeix@gmail.com
//-(   )------(   )---------------------------------------
//  ( (        ) /
//   (_)      (_/

//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 or version 3 of the License.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License along
//    with this program; if not, write to the Free Software Foundation, Inc.,
//    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#include "graphics.h"
#include "preference.h"

/*** Global variables ***/
/************************/
extern sNewPreference Pref;
extern int NSprites;
extern sNewPreference Pref;

static const char *OrdreTexte = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-!?*+<>%$()&;";
static const char *OrdreTexte2 = "abcdefghijklmnopqrstuvwxyz0123456789,_|?*+<>%$[]&;";
static int TextAtlas[256];

char Langue[31][16]; // Mémorise les noms des langues
int NTextes = 0;
bool shouldDrawLoading = false;

/* Constructor */
/***************/
Graphics::Graphics(){
	
	Initialize();
}

/* Window initialization */
/*************************/
void Graphics::Initialize(){
	if (Running == true){
		// Hints
		SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	    // Initiliase SDL
	    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
	        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError());
	        exit(-1);
	    }
	    // Close the program properly when quitting
	    atexit(SDL_Quit);

	    // Set resolution
	    int vOption = SDL_WINDOW_RESIZABLE;
	    if (Pref.FullScreen) {
	        vOption |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	    }

	    sdlWindow = SDL_CreateWindow("Li-ri", 0, 0, 800, 600, vOption);
	    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	    SDL_RenderSetLogicalSize(sdlRenderer, 800, 600);

	    SDL_ShowCursor(0); // Hide cursor
	}
}

/* Quad/Rect draw function */
/***************************/
void Graphics::DrawRect(int X, int Y, int W, int H, int Angle, SDL_Texture Texture, int R, int G, int B){
	SDL_Rect destination = {X,Y,W,H};
	SDL_Point center = {W/2,H/2}; // Rotation center

	// Render
	SDL_RenderCopyEx(sdlRenderer, Texture, nullptr, destination, angle, &center, SDL_FLIP_NONE);
}

int Graphics::GetTime(){
	return SDL_GetTicks();
}

void Graphics::Update(){
    SDL_RenderPresent(sdlRenderer);

	while (SDL_PollEvent(&event)) {
	    if (event.type == SDL_QUIT) {
	        Running = false;
	    }
	}
}



void Graphics::Destroy(){
	// Destroying window and render
	SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);

    Mix_Quit();
    SDL_Quit();
}