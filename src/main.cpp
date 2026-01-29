//      (_||_/
//      (    )		Copyright (C) 2006 By Dominique Roux-Serret
//     ( o  0 )		roux-serret@ifrance.com
//-OOO°--(_)---°OOO---------------------------------------
//                  Copyright (C) 2023 By Johnny Jazeix
// .OOOo      oOOO. jazeix@gmail.com
//-(   )------(   )---------------------------------------
//  ( (        ) /  Copyright (C) 2026 By Mykyta Polishyk
//   (_)      (_/   zabidentwfan@ukr.net

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

#include "system.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "config.h.in"
#include "preference.hpp"
#include "level.hpp"
#include "game.hpp"
#include "utils.hpp"
#include <cstring>

std::string Title = "Li-ri V" + std::string(VERSION);
// Initialization of global objects
sNewPreference Pref; // Preference table.
// Game clock
float currentTime = 0; 
float previousTime = 0;
Level level;

#if defined(__unix__) || defined(__HAIKU__)
char DefPath[256]; // Default path
#endif

/*** Initialize preferences ***/
/******************************/
void InitPref()
{
#if defined(__unix__) || defined(__HAIKU__)
    DefPath[0] = 0;
#endif

    for (int i = 0; i < 8; i++) { // Empty the scores
        Pref.Sco[i].Score = 0;
        Pref.Sco[i].Name[0] = 0;
    }

    Utils::LoadPref();
}

/* Main program */
/****************/
int main(int narg, char *argv[]){
	eMenu RetM, RetMenu = mGame;
	// Initialize preferences
    InitPref();
#if defined(__unix__) || defined(__HAIKU__)
    if (narg > 1) {
        strcpy(DefPath, argv[1]);
    }
#endif
	Console.Log("Launched " + Title);
	Graphics = new GraphicsSystem(); // Initializating graphics system

    Pref.Level = 1;
	Input::Init();
	Data.LoadTextures();
	Graphics->SetViewport(800, 600);
	Graphics->SetOrtho(800, 600);

	Game game;

	// Updating content in window and cleaning input buffer
	while (!Graphics->ShouldWindowClose() || RetMenu != mQuit){
		Graphics->Clear(1,1,1);

		// Updating time
		previousTime = Graphics->GetWindowTime();
		// Tick
		//Console.Log("Tick: " + std::to_string(currentTime-previousTime));
		currentTime = Graphics->GetWindowTime();

		switch (RetMenu) {
        case mGame:
            RetM = game.Update();
            break;
        default:
            RetM = mQuit;
        }
        RetMenu = RetM;

		Input::Clean();
		Graphics->PollEvents();
	}

	return 0;
}