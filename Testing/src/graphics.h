//      (_||_/
//      (    )       Graphics class (by Mykyta Polishyk)
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

#ifndef GRAPHICS_DOM_
#define GRAPHICS_DOM_

#include <SDL2/SDL_error.h> // for SDL_GetError
#include <SDL2/SDL_hints.h> // for SDL_SetHint, SDL_HINT_RENDER_SCALE_QUALITY
#include <SDL2/SDL_log.h> // for SDL_LogError, SDL_LOG_CATEGORY_APPLICATION
#include <SDL2/SDL_mouse.h> // for SDL_ShowCursor
#include <SDL2/SDL_render.h> // for SDL_CreateRenderer, SDL_DestroyRenderer
#include <SDL2/SDL_timer.h> // for SDL_GetTicks
#include <SDL2/SDL_video.h> // for SDL_CreateWindow, SDL_DestroyWindow
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>

/* Graphics class define */
/*************************/
class Graphics{
public:
	Graphics();
	void Initialize();
	void Update();
	void DrawRect(int X, int Y, int W, int H, int Angle, SDL_Texture Texture, int R, int G, int B);
	void Destroy();
private:
	/*** Variables ***/
	bool Running = true;
    std::vector<SDL_Texture> Textures { nullptr }; // Textures
	SDL_Window *sdlWindow; // Screen video pointer
	SDL_Renderer *sdlRenderer; // Screen video pointer
}
