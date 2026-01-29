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
#include "graphics.hpp"
#include <fstream>
#include <png.h>
#include <cstring>

extern std::string Title;
GraphicsSystem* Graphics;

/* Constructor */
/***************/
GraphicsSystem::GraphicsSystem(){
	// Now width and height is static
	Width = 800;
	Height = 600;
	// After creating window and context
	CreateWindowAndContext();
}

/* Creating window, and GL context */
/***********************************/
void GraphicsSystem::CreateWindowAndContext(){
	if (glfwInit()){ // Initializating GLFW
		Console.Log("GLFW initializated");
	}
	else{
		Console.Log("Failed to initializate GLFW");
	}
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); 
    root = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
    if (root){
    	Console.Log("GLFW window created");
    }
    else{
    	Console.Log("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(root); // Setting root as current GL context

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicsSystem::SetViewport(int W, int H){
	glViewport(0,0,W,H);
}

void GraphicsSystem::SetOrtho(int W, int H){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, W, H, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Polling events */
/******************/
void GraphicsSystem::PollEvents(){
	if (root){ // Safety
	    glfwPollEvents();
	    glfwSwapBuffers(root);
	}
}

bool GraphicsSystem::ShouldWindowClose(){
	if (root){ // Safety
		return glfwWindowShouldClose(root);
	}
	else{
		return true;
	}
}

/* Loading GL texture from vector */
/**********************************/
void GraphicsSystem::EnableTexture(int Num){
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[Num].RawData);
}

int GraphicsSystem::GetTextureWidth(int Num){
	return textures[Num].Width;
}

int GraphicsSystem::GetTextureHeight(int Num){
	return textures[Num].Height;
}

/* Loading PNG texture, and converting it to GL texture */
/********************************************************/
void GraphicsSystem::LoadTexture(std::string path){
	GFXTexture buffer;

    // Reading PNG
    std::ifstream file(path, std::ios::binary);
    if (!file) {
    	Console.Log("Failed to open " + path + " PNG");
        return;
    }
    std::vector<unsigned char> file_data((std::istreambuf_iterator<char>(file)),
                                         std::istreambuf_iterator<char>());
    file.close();

    // Check PNG
    if (file_data.size() < 8 || png_sig_cmp(file_data.data(), 0, 8)) {
        Console.Log("File is not PNG");
        return;
    }

    // Reading signature
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) { png_destroy_read_struct(&png_ptr, nullptr, nullptr); return; }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        Console.Log("Failed to read " + path + " PNG");
        return;
    }
    // Reading image
    struct MemReader { const unsigned char* data; size_t size; size_t offset; };
    MemReader reader = { file_data.data() + 8, file_data.size() - 8, 0 }; // Signature check
    png_set_sig_bytes(png_ptr, 8);
    // Reading PNG
    auto png_read_from_memory = [](png_structp png_ptr, png_bytep out_bytes, png_size_t byte_count_to_read) {
        MemReader* r = (MemReader*)png_get_io_ptr(png_ptr);
        if (r->offset + byte_count_to_read > r->size)
            png_error(png_ptr, "Read beyond end of buffer");
        memcpy(out_bytes, r->data + r->offset, byte_count_to_read);
        r->offset += byte_count_to_read;
    };

    png_set_read_fn(png_ptr, &reader, png_read_from_memory);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    buffer.Width  = png_get_image_width(png_ptr, info_ptr);
    buffer.Height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth  = png_get_bit_depth(png_ptr, info_ptr);

    if (bit_depth == 16) png_set_strip_16(png_ptr);
    if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY) png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png_ptr);

    png_read_update_info(png_ptr, info_ptr);

    std::vector<png_byte> image_data(buffer.Width * buffer.Height * 4);
    std::vector<png_bytep> row_pointers(buffer.Height);
    for (int y = 0; y < buffer.Height; y++)
        row_pointers[y] = image_data.data() + y * buffer.Width * 4;

    png_read_image(png_ptr, row_pointers.data());
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    // GL Textures
    glGenTextures(1, &buffer.RawData);
    glBindTexture(GL_TEXTURE_2D, buffer.RawData);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, buffer.Width, buffer.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.data());

    Console.Log("Loaded " + path + " image");
    textures.push_back(buffer);
}

void GraphicsSystem::BeginQuad(){
	glBegin(GL_QUADS);
}

void GraphicsSystem::DrawQuad(float X, float Y, float W, float H, float angle){
	glTexCoord2f(0,0); glVertex2f(X,Y);
	glTexCoord2f(1,0); glVertex2f(X+W,Y);
	glTexCoord2f(1,1); glVertex2f(X+W,Y+H);
	glTexCoord2f(0,1); glVertex2f(X,Y+H);
}

/* Set renderer draw color */
/***************************/
void GraphicsSystem::SetColor(float R, float G, float B, float A){
	glColor4f(R,G,B,A);
}

void GraphicsSystem::End(){
	glEnd();
}

/* Cleaning window with color */
/******************************/
void GraphicsSystem::Clear(float R, float G, float B){
    glClearColor(R, G, B, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

/* Get time after program launch */
/*********************************/
float GraphicsSystem::GetWindowTime(){
	return glfwGetTime();
}

/* Get screen aspect */
/*********************/
float GraphicsSystem::GetScreenAspect(){
	return static_cast<float>(Width) / static_cast<float>(Height);
}