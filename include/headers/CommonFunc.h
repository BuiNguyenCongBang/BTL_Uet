#pragma once

#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <mmsystem.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

const int FRAME_PER_SECOND = 40;

const int NUM_THREAT1S = 90;
const int NUM_THREAT2S = 60;
const int NUM_THREAT1S_ROUND_1 = 5;
const int NUM_THREAT2S_ROUND_1 = 2;

const int NUM_THREAT1S_ROUND_2 = 20;
const int NUM_THREAT2S_ROUND_2 = 10;

const int NUM_THREAT1S_ROUND_3 = 25;
const int NUM_THREAT2S_ROUND_3 = 18;

const int NUM_THREAT1S_ROUND_4 = 40;
const int NUM_THREAT2S_ROUND_4 = 30;


#endif // !1


