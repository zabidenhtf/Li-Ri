//      (_||_/
//      (    )       Input class (by Mykyta Polishyk)
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


#include <SDL2/SDL_events.h> // for SDL_PollEvent, SDL_PRESSED, SDL_Event
#include <SDL2/SDL_keycode.h> // for SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_UP

/* Input class define */
/**********************/
class Input{
public:
	Input();
	void PollEvents();
	void Callback();
	bool GetClose();
	SDL_Scancode KeyPressedDown();
private:
	bool ShouldClose;
	SDL_Scancode LastKey;
    SDL_Event sdlEvent; // Event listener
}