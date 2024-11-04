#ifndef WINDOW_H
#define WINDOW_H

#include "linkedList.h"
#include "particle.h"
#ifdef _WIN64
#include <SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

struct WindowObject {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int width;
    int height;
};

struct WindowObject createWindowObject(int width, int height, int positionX, int positionY);
int destroyWindowObject(struct WindowObject *windowObject);
int updateSize(struct WindowObject *windowObject);

int drawCircle(struct Circle *circle, struct WindowObject *windowObject);

int drawCircleList(struct Node *circleList, struct WindowObject *windowObject);

int presentBuffer(struct WindowObject *windowObject);
int presentGrayBuffer(struct WindowObject *windowObject);

#endif
