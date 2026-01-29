//      (_||_/
//      (    )		Copyright (C) 2006 By Dominique Roux-Serret
//     ( o  0 )		roux-serret@ifrance.com
//-OOO°--(_)---°OOO---------------------------------------
//                  Copyright (C) 2023 By Johnny Jazeix
// .OOOo      oOOO. jazeix@gmail.com
//-(   )------(   )---------------------------------------
//  ( (        ) /  Copyright (C) 2026 By Mykyta Polishyk
//   (_)      (_/   zabidentwfan@ukr.net

#include "iostream"
#include "string"

#pragma once

enum e_Sprite { // Sprites list
    locomotive = 0,
    coal_wagon,
    logs_wagon,
    cargo_wagon,
    engine_wagon,
    cistern_wagon,
    wagon,
    pluslong,
    pluscourt,
    speed,
    life,
    //new_wagon,
    life_icon,
    rail,
    //dir,
    //lettres,
    //digits, // TODO: Its not modern and it must to be replaced on Freetype
    title,
    copyright,
    deco,
    cursor,
    arrow_left,
    arrow_right,
    arrows,
    earth,
    music,
    sound,
    fscreen,
    window,
    keys,
    settings_menu,
    menu,
    background_header,
    background_button,
    menu_background,
    game_background,

    //loading,
    // This too
    T_level,
    T_lives,
    T_options,
    T_score,
    T_press_any_key,
    T_continue,
    T_moptions,
    T_exit_game,
    T_play,
    T_scores,
    T_better_scores,
    T_quit,
    T_new_game,
    T_old_level,
    T_menu,
    T_easy,
    T_normal,
    T_hard,
/*#ifndef DCHILDREN
    T_question,
    T_tart1,
    T_tart2,
    T_tart3,
    T_tart4,
    T_tart5,
    T_tart6,
    T_tart7,
    T_tart8,
    T_tart9,
    T_tart10,
    T_tart11,
    T_tart12,
    T_tart13,
    T_tart14,
    T_tart15,
    T_tart16,
    T_tart17,
    T_tart18,
    T_tart19,
    T_tart20,
    T_tart21,
    T_tart22,
    T_tart23,
    T_tart24,
    T_tart25,
    T_tart26,
    T_tart27,
    T_tart28,
    T_tart29,
    T_tart30,
    T_art1,
    T_art2,
    T_art3,
    T_art4,
    T_art5,
    T_art6,
    T_art7,
    T_art8,
    T_art9,
    T_art10,
    T_art11,
    T_art12,
    T_art13,
    T_art14,
    T_art15,
    T_art16,
    T_art17,
    T_art18,
    T_art19,
    T_art20,
    T_art21,
    T_art22,
    T_art23,
    T_art24,
    T_art25,
    T_art26,
    T_art27,
    T_art28,
    T_art29,
    T_art30,
#endif*/
    T_Langue,

    T_ENDTEXT
};

/* Console interface define */
/****************************/
struct ConsoleSystem{
	void Log(std::string text, bool newline=true);
	void DebugLog(std::string category, std::string text, bool newline);
};

/* Data system define */
/**********************/
struct DataSystem
{
	void LoadTextures();
	// Todo: Add audio loading and fonts loading stuff
};

extern ConsoleSystem Console;
extern DataSystem Data;