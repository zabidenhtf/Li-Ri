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

#include <cstdlib>

#include "game.hpp"
#include "level.hpp"
#include "utils.hpp"

/*** Variables globales ***/
/**************************/
extern sNewPreference Pref;

extern int currentTime;
extern int previousTime;

extern Level level;

static int NumRail[] = { -1, -1, -1, 0, -1, 1, 2, 3, -1, 4, 5, 6, 7, 8, 9, 10 };

int MasqueK; // Masque pour les touches de déplacement

/*** Constructeur et Destructeur ***/
/***********************************/
Game::Game()
{
    Touche[0] = D_Top;
    Touche[1] = D_Bottom;
    Touche[2] = D_Left;
    Touche[3] = D_Right;
}

/*** Update ***/
/**************/
eMenu Game::Update()
{
    eMenu mRet;
    int NumN = Pref.Level;

    Help = true;
    Load(NumN); // Charge le tableau
    Pause = true;

    DureeJeu = 0;
    Key = 0;

    // Met le options de départ du joueur
    Pref.Lives = N_LIVES_COUNT;
    Pref.Score = 0;

    // Prend les evenements
    while (true); {
       /*bool doScreenshot = false;
       SDL_RenderClear(sdlRenderer);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            //m_gamepad.GetEvent(event); // Handle gamepad

            switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_ENTER) {
                }
                else if (event.window.event == SDL_WINDOWEVENT_LEAVE) { // Si désactive l'ecran
                    Pause = true; // Met en Pause
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.state == SDL_PRESSED) {
                    // Add a Pause event if we click on the top right loco
                    int const Px = event.button.x;
                    int const Py = event.button.y;
                    if (Px >= 680 && Py <= 90) {
                        mRet = m_menu->SDLMain_InGame();
                        if (mRet == mGame) {
                            DrawLevel(NumN);
                            SDL_RenderPresent(sdlRenderer);
                            Pause = true;
                        }
                        else {
                            return mRet;
                        }
                    }
                    else if (Pause) {
                        Pause = false;
                    }
                    else {
                        TourneFleche();
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.state == SDL_PRESSED) {
                    if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_AC_BACK) {
                        mRet = m_menu->SDLMain_InGame();
                        if (mRet == mGame) {
                            DrawLevel(NumN);
                            SDL_RenderPresent(sdlRenderer);
                            Pause = true;
                        }
                        else {
                            return mRet;
                        }
                    }
                    else {
                        Key = event.key.keysym.sym;

                        if (event.key.repeat == 0) {
                            // The text says: "press any key to start"
                            // so we allow any key press (except Escape)
                            // to start the game
                            if (Pause) {
                                Pause = false;
                                break;
                            }
                            switch (Key) {
                            case SDLK_UP:
                                BufTouche(D_Top);
                                MasqueK |= 1;
                                break;
                            case SDLK_DOWN:
                                BufTouche(D_Bottom);
                                MasqueK |= 2;
                                break;
                            case SDLK_LEFT:
                                BufTouche(D_Left);
                                MasqueK |= 4;
                                break;
                            case SDLK_RIGHT:
                                BufTouche(D_Right);
                                MasqueK |= 8;
                                break;
                            case SDLK_F12: // Save screenshot
                                doScreenshot = true;
                                break;
                            case 'p':
                            case 'P':
                                if (Pause == false) {
                                    Pause = true;
                                }
                                break;
                            case ' ':
                                if (Pause) {
                                    Pause = false;
                                }
                                break;
                            case 'h':
                            case 'H':
                                Help = !Help;
                                break;
                            }
                        }
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        MasqueK &= 14;
                        break;
                    case SDLK_DOWN:
                        MasqueK &= 13;
                        break;
                    case SDLK_LEFT:
                        MasqueK &= 11;
                        break;
                    case SDLK_RIGHT:
                        MasqueK &= 7;
                        break;
                    default:
                        break;
                    }
                    if (!MasqueK) {
                        Key = 0;
                    }
                    break;
                case SDL_QUIT:
                    return mQuit;
                    break;
                }
            }
        }*/

        // Gère les Horloges et la pose
        //Sleeping();
        if (Pause == true || Lo.Mort > currentTime) {
            previousTime = currentTime;
        }
        DureeJeu += currentTime - previousTime;

        // Fait l'affichage
        DrawLevel(NumN);

        // Fait avancer la loco
        if (Lo.Mort == -1 && Pause == false) {
            Lo.Avance(currentTime - previousTime, DureeJeu, Touche, T);
        }

        // Test la fin d'une partie
        if (Lo.Mort > -1 && Lo.Mort < currentTime) { // Si est Mort test si doit continuer ou quitter
            if (Pref.Lives < 0) {
                return mScoreEdit; // Si mort fini
            }
            if (Lo.Gagne) {
/*#ifndef DCHILDREN
                if (Pref.HumanRightsQuiz && m_menu->SDLMain_HR() == mQuit) {
                    return mQuit;
                }
#endif*/
                NumN++;
                if (level.N == NumN) {
                    Pref.Score += Pref.Lives * 100;
                    return mScoreEdit;
                }
                if (Pref.LevelMax[Pref.Difficulty] < NumN) {
                    Pref.LevelMax[Pref.Difficulty] = NumN;
                }
            }
            //m_sounds.NextMusic();
            DureeJeu = 0;
            Pause = true;
            Key = MasqueK = 0;
            Load(NumN);
        }

    }

    return mQuit;
}

/*** Charge un tableau ***/
/*************************/
bool Game::Load(int NivN)
{
    int i;

    Pref.Level = NivN;

    // Recopie le tableau
    for (i = 0; i < LT * HT; i++) {
        T[i] = (int)level.T[NivN].T[i];
    }

    // Laisse ou efface la vie suivant le niveau
    switch (Pref.Difficulty) {
    case Easy:
        i = 5;
        break;
    case Normal:
        i = 9;
        break;
    default:
        i = 15;
    }
    if ((rand() % i) != 0) {
        for (i = 0; i < LT * HT; i++) {
            if (T[i] == C_Live) {
                T[i] = C_Rail;
            }
        }
    }

    // Initialise la locomotive
    Lo.Init(level.T[NivN].DepX + level.T[NivN].DepY * LT, level.T[NivN].DepDir);
    BufTouche(level.T[NivN].DepDir);
    MasqueK = 0;

    // Met la vitesse suivant difficulté
    switch (Pref.Difficulty) {
    case Easy:
        Pref.Speed = Pref.SpeedAverage = SPEED_MIN;
        break;
    case Hard:
        Pref.Speed = Pref.SpeedAverage = SPEED_MAX;
        break;
    default:
        Pref.Speed = Pref.SpeedAverage = SPEED_AVERAGE;
    }

    return DrawLevel(NivN);
}

/*** Dessine le fond de l'ecran de jeu ***/
/*****************************************/
bool Game::DrawLevel(int NivN)
{
    int i, x, y, m, cx, cy;

    // Fabrique le fond du jeu
    Graphics->EnableTexture(game_background);
    Graphics->BeginQuad();
    Graphics->DrawQuad(0,0,800,600,0);
    Graphics->End();

    // Affiche le circuit
    for (i = 0; i < LT * HT; i++) {
        if (T[i] >= C_Rail && T[i] < C_Fin) {
            y = i / LT * D_Case + D_Case / 2;
            x = i % LT * D_Case + D_Case / 2;

            m = 0;
            cx = i % LT;
            cy = i / LT;
            if (cy > 0 && T[i - LT] >= C_Rail && T[i - LT] < C_Fin) {
                m += 8;
            }
            if (cy < HT - 1 && T[i + LT] >= C_Rail && T[i + LT] < C_Fin) {
                m += 4;
            }
            if (cx > 0 && T[i - 1] >= C_Rail && T[i - 1] <= C_Fin) {
                m += 2;
            }
            if (cx < LT - 1 && T[i + 1] >= C_Rail && T[i + 1] <= C_Fin) {
                m += 1;
            }

            Graphics->EnableTexture(rail);
            Graphics->BeginQuad();
            Graphics->DrawQuad(x, y, Graphics->GetTextureWidth(rail), Graphics->GetTextureHeight(rail),0);
            Graphics->End();
        }
    }

    // Affiche les décorations
/*#ifndef DCHILDREN
    for (i = 0; i < level.T[NivN].NDeco; i++) {
        Sprites[deco].Draw(level.T[NivN].Deco[i].x, level.T[NivN].Deco[i].y, level.T[NivN].Deco[i].NumSpr,
                           Sprites[fjeu].Image[0]);
    }
#endif

    // Affiche les textes suivant la langue
    DrawText(740, 110, T_level, Sprites[fjeu].Image[0]);
    DrawText(740, 180, T_score, Sprites[fjeu].Image[0]);
    DrawText(740, 260, T_options, Sprites[fjeu].Image[0]);
    DrawText(740, 340, T_lives, Sprites[fjeu].Image[0]);

    DrawNumber(740, 140, Pref.Level + 1, Sprites[fjeu].Image[0]);*/

    return true;
}

/*** Fait tourner la fleche d'une simple touche ***/
/**************************************************/
void Game::TourneFleche()
{
    int To = Touche[0];
    bool Cherche = false;
    int const x = Lo.PInter % LT;
    int const y = Lo.PInter / LT;

    do {
        // Fait toucher la direction dans le sens des aiguilles d'une montre
        // et test si la nouvelle direction est possible
        switch (To) {
        case D_Top:
            To = D_Right;
            if (Lo.PEntree != D_Right && x + 1 < LT && T[Lo.PInter + 1] != 0) {
                Cherche = true;
            }
            break;
        case D_Right:
            To = D_Bottom;
            if (Lo.PEntree != D_Bottom && y + 1 < HT && T[Lo.PInter + LT] != 0) {
                Cherche = true;
            }
            break;
        case D_Bottom:
            To = D_Left;
            if (Lo.PEntree != D_Left && x > 0 && T[Lo.PInter - 1] != 0) {
                Cherche = true;
            }
            break;
        case D_Left:
            To = D_Top;
            if (Lo.PEntree != D_Top && y > 0 && T[Lo.PInter - LT] != 0) {
                Cherche = true;
            }
            break;
        }
    } while (Cherche == false);

    BufTouche(To); // Mémorise la nouvelle touche par defaut.
}

/*** Mémorise une touche dans le buffet des touches ***/
/******************************************************/
void Game::BufTouche(int Tou)
{
    int n = 0;

    // Favorise la touche
    while (Touche[n] != Tou) {
        n++; // Prend position de la touche
    }

    if (n) { // Si changement doit faire un décalage
        while (n) {
            Touche[n] = Touche[n - 1];
            n--;
        }
        Touche[0] = Tou; // Mémorise la touche
    }

    // Cherche son oposé
    switch (Tou) {
    case D_Top:
        Tou = D_Bottom;
        break;
    case D_Bottom:
        Tou = D_Top;
        break;
    case D_Left:
        Tou = D_Right;
        break;
    case D_Right:
        Tou = D_Left;
        break;
    }

    // Défavorise son oposé.
    n = 3;
    while (Touche[n] != Tou) {
        n--; // Prend position de la touche
    }

    if (n < 3) { // Si changement doit faire un décalage
        while (n < 3) {
            Touche[n] = Touche[n + 1];
            n++;
        }
        Touche[3] = Tou; // Mémorise la touche
    }
}

/*** Test les directions possibles pour les fleches ***/
/******************************************************/
int Game::TestFleche(int Haut, int Bas, int Gauche, int Droite)
{
    int i;
    int const x = Lo.PInter % LT;
    int const y = Lo.PInter / LT;

    for (i = 0; i < 4; i++) {
        switch (Touche[i]) {
        case D_Top:
            if (y > 0 && Haut != -1 && T[Lo.PInter - LT] != 0) {
                return Haut;
            }
            break;
        case D_Bottom:
            if (y + 1 < HT && Bas != -1 && T[Lo.PInter + LT] != 0) {
                return Bas;
            }
            break;
        case D_Left:
            if (x > 0 && Gauche != -1 && T[Lo.PInter - 1] != 0) {
                return Gauche;
            }
            break;
        case D_Right:
            if (x + 1 < LT && Droite != -1 && T[Lo.PInter + 1] != 0) {
                return Droite;
            }
            break;
        }
    }
    return 0;
}

/*** Affiche un ecran du jeu ***/
/*******************************/
void Game::AfficheEcran()
{
    int i;
    int ndir = 0;

    // Fait nouvelle Affichage
    Lo.Display(); // Affiche la loco

    if (Lo.PInter != -1 && Help) { // Affiche la fleche sur la futur intersection
        switch (Lo.PEntree) {
        case D_Left:
            ndir = TestFleche(0, 2, -1, 1);
            break;
        case D_Right:
            ndir = TestFleche(8, 6, 7, -1);
            break;
        case D_Top:
            ndir = TestFleche(-1, 4, 5, 3);
            break;
        case D_Bottom:
            ndir = TestFleche(10, -1, 9, 11);
            break;
        }

        //Ec.PrintSprite(dir, ndir, (Lo.PInter % LT) * D_Case + D_Case / 2, (Lo.PInter / LT) * D_Case + D_Case / 2);
    }

    // Affiche les options
    for (i = 0; i < LT * HT; i++) {
        switch (T[i]) {
        case C_Wagon: // Si un loco
            Graphics->EnableTexture(wagon);
            break;
        case C_Allonge: // Si plus long
            Graphics->EnableTexture(pluslong);
            break;
        case C_Reduit: // Si plus court
            Graphics->EnableTexture(pluscourt);
            break;
        case C_Speed: // Si plus vite
            Graphics->EnableTexture(speed);
            break;
        case C_Live: // Si une vie
            Graphics->EnableTexture(life);
            break;
        }
    }

    Graphics->BeginQuad();
    Graphics->DrawQuad(i % LT * D_Case + D_Case / 2, i / LT * D_Case + D_Case / 2, 50, 50, 0);
    Graphics->End();

    // Si en pose demande une touche
    if (Pause) {
        //Ec.PrintText(T_press_any_key, LT * D_Case / 2, 300);
    }

    // Affiche tableau de bord
    //Ec.PrintOptions(Pref.Lives, Pref.Score);
    if (Pref.WagonGap < WAGON_GAP_MIN) {
        Graphics->EnableTexture(pluscourt);
        Graphics->BeginQuad();
        Graphics->DrawQuad(715, 295, Graphics->GetTextureWidth(pluscourt), Graphics->GetTextureHeight(pluscourt), 0);
        Graphics->End();
    }
    if (Pref.WagonGap > WAGON_GAP_AVERAGE) {
        Graphics->EnableTexture(pluslong);
        Graphics->BeginQuad();
        Graphics->DrawQuad(715, 295, Graphics->GetTextureWidth(pluslong), Graphics->GetTextureHeight(pluslong), 0);
        Graphics->End();
    }
    if (Pref.SpeedAverage > Pref.Speed) {
        Graphics->EnableTexture(speed);
        Graphics->BeginQuad();
        Graphics->DrawQuad(765, 295, Graphics->GetTextureWidth(speed), Graphics->GetTextureHeight(speed), 0);
        Graphics->End();
    }
}
