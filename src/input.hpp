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
#include "system.hpp"
#include "graphics.hpp"

#include <vector>

#pragma once

// TODO: make input system objective
extern std::vector<int> KeyBuffer; // Buffer to save keys
extern std::vector<char> CharBuffer; // Buffer to save letters 

/* Input system namespace define */
/*****************************/
namespace Input{
	void Callback(GLFWwindow* window, int key, int scancode, int action, int mods); // Callback
	void Init(); // Constructor
	void Clean();
}
