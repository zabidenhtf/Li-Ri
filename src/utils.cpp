//      (_||_/
//      (    )
//     ( o  0 )
//-OOO°--(_)---°OOO---------------------------------------
//                   Copyright (C) 2006 By Dominique Roux-Serret
// .OOOo      oOOO.  roux-serret@ifrance.com
//-(   )------(   )---------------------------------------
//  ( (        ) /   Copyright (C) 2023 By Johnny Jazeix
//   (_)      (_/    jazeix@gmail.com

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

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include "system.hpp"

#include "config.h"
#include "utils.hpp"
#include "preference.hpp"

#include "SimpleIni.h"

/*** Global variables ***/
/**************************/
extern sNewPreference Pref;
#if defined(__unix__) || defined(__HAIKU__)
extern char DefPath[]; // Default path in argument
#endif

/*** General defines ***/
/************************/
#ifdef __APPLE__
#define MAC_LINUX
#endif

#ifdef __unix__
#define MAC_LINUX
#endif

#ifdef ANDROID
#define MAC_LINUX
#endif

/*** Check if the file exists ***/
/********************************/
bool Utils::FileExists(std::string Path)
{
    return std::filesystem::exists(Path);
}

/*** Load a file in memory ***/
/*****************************/
long Utils::LoadFile(const char *Path, unsigned char *&Buf)
{
    std::ifstream file(Path, std::ios::binary | std::ios::ate);
    if (!file) {
        Console.Log(std::string("Failed to open ") + std::string(Path) + std::string(" file"));
        return -1;
    }

    std::streamsize size = file.tellg();
    if (size <= 0) return -1;

    file.seekg(0, std::ios::beg);
    Buf = new unsigned char[size];
    if (!file.read((char*)Buf, size)) {
        delete[] Buf;
        return -1;
    }
    return (long)size;
}

/*** Save a file ***/
/*******************/
bool Utils::SaveFile(const char *Path, char *Buf, long L)
{
    FILE *file;

    file = fopen(Path, "w");
    if (!file) {
        Console.Log(std::string("Failed to open ") + std::string(Path) + std::string(" File"));
        return false;
    }

    while (L > 512) {
        if (fwrite(Buf, 1, 512, file) != 512) {
            Console.Log(std::string("Failed to write in  ") + std::string(Path) + std::string(" File"));
            fclose(file);
            return false;
        }
        L -= 512;
        Buf += 512;
    }

    if (L > 0) {
        if (fwrite(Buf, 1, (size_t)L, file) != (size_t)L) {
            Console.Log(std::string("Failed to write in  ") + std::string(Path) + std::string(" File"));
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

/*** Add the path to the filename depending on the OS (sprites, levels) ***/
/**************************************************************************/
#if (defined(__unix__) || defined(ANDROID)) || defined(__HAIKU__) && !defined(__AMIGAOS4__)
// Version Linux
void Utils::GetPath(char *Path)
{
    char Provi[512];

    strcpy(Provi, Path);

#ifndef ANDROID
    if (DefPath[0]) {
        sprintf(Path, "%s%s", DefPath, Provi);
        if (Utils::FileExists(Path)) {
            return;
        }
    }
#endif

    // Android is directly the filename
    sprintf(Path, "%s", Provi);
    if (Utils::FileExists(Path)) {
        return;
    }

    sprintf(Path, "%s/%s", LIRI_DATA_DIR, Provi);
    if (Utils::FileExists(Path)) {
        return;
    }

    Console.Log("Failed to find path");
}
#endif

#ifdef __AMIGAOS4__
// Version AmigaOS4
void Utils::GetPath(char *Path)
{
    char Provi[512];

    strcpy(Provi, Path);

    sprintf(Path, "PROGDIR:%s", Provi);
    if (Utils::FileExists(Path)) {
        return;
    }

    Console.Log("Failed to find path");
    exit(-1);
}
#endif

#ifdef __APPLE__
// Version Mac OSX
void Utils::GetPath(char *Path)
{
    char Provi[512];

    strcpy(Provi, Path);

    sprintf(Path, "Li-ri.app/Contents/Resources/%s", Provi);
    if (Utils::FileExists(Path)) {
        return;
    }

    Console.Log("Failed to find path");
    exit(-1);
}
#endif

#ifdef _WIN32
// Windows version, direct path
void Utils::GetPath(char *Path)
{
    std::filesystem::path base =
        std::filesystem::current_path();
    std::filesystem::path full = base / Path;
    strcpy(Path, full.string().c_str());
}
#endif

/*** Load preferences ***/
/************************/
bool Utils::LoadPref()
{
    int L;
    unsigned char *Provi;

    char oldPathPref[512];
    sprintf(oldPathPref, "./li-ri.pref");

    char newPathPref[512];
    sprintf(newPathPref, "./li-ri.ini");

    // Load new config file if it exists
    if (Utils::FileExists(newPathPref)) {
        CSimpleIniA ini(true); // true for unicode
        SI_Error rc = ini.LoadFile(newPathPref);
        const char *pv;
        pv = ini.GetValue("main", "fullscreen");
        if (pv) {
            Pref.FullScreen = std::stoi(pv);
        }
        pv = ini.GetValue("main", "locale");
        if (pv) {
            Pref.Language = std::stoi(pv);
        }
        pv = ini.GetValue("main", "audioVolume");
        if (pv) {
            Pref.Volume = std::stof(pv);
        }
        pv = ini.GetValue("main", "musicVolume");
        if (pv) {
            Pref.VolumeM = std::stof(pv);
        }
        pv = ini.GetValue("main", "humanRightsQuiz");
        if (pv) {
            Pref.HumanRightsQuiz = std::stoi(pv);
        }
        pv = ini.GetValue("easy", "maxLevel");
        if (pv) {
            Pref.LevelMax[0] = std::stof(pv);
        }
        pv = ini.GetValue("normal", "maxLevel");
        if (pv) {
            Pref.LevelMax[1] = std::stof(pv);
        }
        pv = ini.GetValue("difficult", "maxLevel");
        if (pv) {
            Pref.LevelMax[2] = std::stof(pv);
        }
        for (int i = 0; i < 8; ++i) {
            std::string scoreKey = "score_" + std::to_string(i);
            std::string nameKey = "name_" + std::to_string(i);
            if (pv) {
                pv = ini.GetValue("highscore", scoreKey.c_str());
            }
            Pref.Sco[i].Score = std::stoi(pv);
            if (pv) {
                pv = ini.GetValue("highscore", nameKey.c_str(), Pref.Sco[i].Name);
            }
            strncpy(Pref.Sco[i].Name, pv, 80);
        }
        return true;
    }

    // In case we don't have yet a file in the new format, we check if we don't have a file in the previous format to restore it.
    if (Utils::FileExists(oldPathPref)) {
        L = Utils::LoadFile(oldPathPref, Provi);
        if (L > 0) {
            sOldPreference oldPref;
            memcpy((char *)&oldPref, Provi, L);
            delete[] Provi;
            Pref.FullScreen = oldPref.FullScreen;
            Pref.Language = oldPref.Langue;
            Pref.Volume = oldPref.Volume;
            Pref.VolumeM = oldPref.VolumeM;
            // Try to restore max difficulty from the level stored in conf
            Pref.LevelMax[0] = oldPref.Difficulte == Easy ? oldPref.NiveauMax : 0;
            Pref.LevelMax[1] = oldPref.Difficulte == Normal ? oldPref.NiveauMax : 0;
            Pref.LevelMax[2] = oldPref.Difficulte == Hard ? oldPref.NiveauMax : 0;
            for (int i = 0; i < 8; ++i) {
                Pref.Sco[i].Score = oldPref.Sco[i].Score;
                strncpy(Pref.Sco[i].Name, oldPref.Sco[i].Name, 80);
            }
            // TODO Delete old file at some file
            return true;
        }
    }

    return false;
}

/*** Save preferences ***/
/************************/
void Utils::SavePref()
{
    char PathPref[512];
    sprintf(PathPref, "./li-ri.ini");

    CSimpleIniA ini(true); // true for unicode
    ini.SetValue("main", "fullscreen", std::to_string(Pref.FullScreen).c_str());
    ini.SetValue("main", "locale", std::to_string(Pref.Language).c_str());
    ini.SetValue("main", "audioVolume", std::to_string(Pref.Volume).c_str());
    ini.SetValue("main", "musicVolume", std::to_string(Pref.VolumeM).c_str());
    ini.SetValue("main", "humanRightsQuiz", std::to_string(Pref.HumanRightsQuiz).c_str());
    ini.SetValue("easy", "maxLevel", std::to_string(Pref.LevelMax[0]).c_str());
    ini.SetValue("normal", "maxLevel", std::to_string(Pref.LevelMax[1]).c_str());
    ini.SetValue("difficult", "maxLevel", std::to_string(Pref.LevelMax[2]).c_str());
    for (int i = 0; i < 8; ++i) {
        std::string scoreKey = "score_" + std::to_string(i);
        std::string nameKey = "name_" + std::to_string(i);
        ini.SetValue("highscore", scoreKey.c_str(), std::to_string(Pref.Sco[i].Score).c_str());
        ini.SetValue("highscore", nameKey.c_str(), Pref.Sco[i].Name);
    }
    ini.SaveFile(PathPref);
}

/*void Utils::doScreenshot(SDL_Renderer *renderer)
{
    static int screenshotNumber = 0;
    char screenshotName[80];
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 24,
                                                          SDL_PIXELFORMAT_RGB24);
    SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGB24, surface->pixels, surface->pitch);
    sprintf(screenshotName, "screenshot%i.bmp", screenshotNumber++);
    SDL_SaveBMP(surface, screenshotName);
    SDL_FreeSurface(surface);
}*/
