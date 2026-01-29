//      (_||_/
//      (    )		Copyright (C) 2006 By Dominique Roux-Serret
//     ( o  0 )		roux-serret@ifrance.com
//-OOO°--(_)---°OOO---------------------------------------
//                  Copyright (C) 2023 By Johnny Jazeix
// .OOOo      oOOO. jazeix@gmail.com
//-(   )------(   )---------------------------------------
//  ( (        ) /  Copyright (C) 2026 By Mykyta Polishyk
//   (_)      (_/   zabidentwfan@ukr.net

#include "system.hpp"
#include "graphics.hpp"

// Creating global objects
ConsoleSystem Console;
DataSystem Data; 

/* Simple write */
void ConsoleSystem::Log(std::string text, bool newline){
	if (newline == true){
		std::cout << text << "\n";
	}
	else{
		std::cout << text;
	}
}

/* Writing with categories for debug */
void ConsoleSystem::DebugLog(std::string category, std::string text, bool newline){

}

void DataSystem::LoadTextures(){
	// Loading textures
	Graphics->LoadTexture("Data/Locomotive.png");
	Graphics->LoadTexture("Data/CoalWagon.png");
	Graphics->LoadTexture("Data/LogsWagon.png");
	Graphics->LoadTexture("Data/CargoWagon.png");
	Graphics->LoadTexture("Data/EngineWagon.png");
	Graphics->LoadTexture("Data/CisternWagon.png");
	Graphics->LoadTexture("Data/Wagon.png");
	Graphics->LoadTexture("Data/PlusLong.png");
	Graphics->LoadTexture("Data/PlusCourt.png");
	Graphics->LoadTexture("Data/Speed.png");
	Graphics->LoadTexture("Data/Life.png");
	Graphics->LoadTexture("Data/LifeIcon.png");
	Graphics->LoadTexture("Data/Rail.png");
	Graphics->LoadTexture("Data/Title.png");
	Graphics->LoadTexture("Data/Copyright.png");
	Graphics->LoadTexture("Data/GameBackground.png");
	Graphics->LoadTexture("Data/Decoration.png");
	Graphics->LoadTexture("Data/Cursor.png");
	Graphics->LoadTexture("Data/ArrowLeft.png");
	Graphics->LoadTexture("Data/ArrowRight.png");
	Graphics->LoadTexture("Data/Arrows.png");
	Graphics->LoadTexture("Data/Earth.png");
	Graphics->LoadTexture("Data/Music.png");
	Graphics->LoadTexture("Data/Sound.png");
	Graphics->LoadTexture("Data/Fullscreen.png");
	Graphics->LoadTexture("Data/Window.png");
	Graphics->LoadTexture("Data/Keys.png");
	Graphics->LoadTexture("Data/SettingsMenu.png");
	Graphics->LoadTexture("Data/Menu.png");
	Graphics->LoadTexture("Data/BackgroundHeader.png");
	Graphics->LoadTexture("Data/BackgroundButton.png");
	Graphics->LoadTexture("Data/MenuBackground.png");
	Graphics->LoadTexture("Data/GameBackground.png");
}