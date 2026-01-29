//      (_||_/
//      (    )		 Copyright (C) 2023 By Johnny Jazeix
//     ( o  0 )		 jazeix@gmail.com
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
#include "input.hpp"

std::vector<int> KeyBuffer; // Buffer to save keys
std::vector<char> CharBuffer; // Buffer to save letters 

/* Callback */
/************/
void Input::Callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (action == GLFW_PRESS) {
		Console.Log("Pressed " + std::to_string(key));
		// Saving keys and letters to buffers
		KeyBuffer.push_back(key);
		CharBuffer.push_back(char(key));
	}
}

/* Constructor */
/***************/
void Input::Init(){
	Console.Log("Input initializated");
	glfwSetKeyCallback(Graphics->GetWindow(), Input::Callback);
}

void Input::Clean(){
	KeyBuffer.clear();
	CharBuffer.clear();
}