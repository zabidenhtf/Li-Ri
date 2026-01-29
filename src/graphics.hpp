//      (_||_/
//      (    )
//     ( o  0 )
//-OOO°--(_)---°OOO---------------------------------------
//                   Copyright (C) 2026 By Mykyta Polishyk
// .OOOo      oOOO.  zabidentwfan@ukr.net
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
#include <GLFW/glfw3.h>
#include "system.hpp"

#include <vector>
#include <string>

#pragma once

/* Texture structure */
struct GFXTexture{
	GLuint RawData;
	int Width;
	int Height;
};

/* Graphics system class define */
/*************************/
class GraphicsSystem{
public:
	GraphicsSystem(); // Constructor
	void CreateWindowAndContext(); // Creating window, and context
	void SetViewport(int W, int H);
	void SetOrtho(int W, int H);
	void PollEvents(); // Snaping and polling events
	bool ShouldWindowClose();
	void EnableTexture(int Num); // Loading texture from vector
	int GetTextureWidth(int Num);
	int GetTextureHeight(int Num);
	void LoadTexture(std::string path); // Loading PNG texture, and converting it to GL texture
	void BeginQuad();
	void SetColor(float R, float G, float B, float A); // Set renderer draw color
	void DrawQuad(float X, float Y, float W, float H, float angle);
	void End();
	float GetWindowTime(); // Get time after program launch
	float GetScreenAspect(); // Get screen aspect
	void Clear(float R, float G, float B); // Cleaning window with color
	void Terminate();
	// TODO: add draw loading function
	GLFWwindow* GetWindow(){return root;}; // Return window object (helpful for input)
private:
	std::vector<GFXTexture> textures;
	int Width; // Width of screen
	int Height; // Height of screen
	GLFWwindow *root = nullptr; // GLFW window pointer
};

extern GraphicsSystem* Graphics; // Global GFX object