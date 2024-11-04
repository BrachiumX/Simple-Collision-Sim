#include "window.h"
#include <stdio.h>

struct WindowObject createWindowObject(int width, int height, int positionX, int positionY) {
	
	SDL_Window* window;

	if(width <= 0 || height <= 0) {
		width = 600;
		height = 600;
	}

	if(positionX < 0 || positionY < 0) {
		window = SDL_CreateWindow("Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
	}
	else {
		window = SDL_CreateWindow("Collision", positionX, positionY, width, height, SDL_WINDOW_SHOWN);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(window) {
		printf("Window created\n");
		struct WindowObject result = {renderer, window, width, height};
		return result;
	}
	printf("Failed to create window\n");
	abort();
}

int destroyWindowObject(struct WindowObject *windowObject) {
	//SDL_DestroyWindow(windowObject->window);
	SDL_DestroyRenderer(windowObject->renderer);
	return 0;
}

int updateSize(struct WindowObject* windowObject) {
	SDL_GetWindowSize(windowObject->window, &(windowObject->width), &(windowObject->height));
	return 0;
}

int drawCircle(struct Circle* circle, struct WindowObject* windowObject) {

	SDL_SetRenderDrawColor(windowObject->renderer, circle->colorR, circle->colorG, circle->colorB, 255);

	double offsetX, offsetY, d;

	offsetX = 0;
	offsetY = circle->radius;
	d = circle->radius -1;

	while (offsetY >= offsetX) {

		SDL_RenderDrawLine(windowObject->renderer, circle->position.x - offsetY, circle->position.y + offsetX, circle->position.x + offsetY, circle->position.y + offsetX);
		SDL_RenderDrawLine(windowObject->renderer, circle->position.x - offsetX, circle->position.y + offsetY, circle->position.x + offsetX, circle->position.y + offsetY);
		SDL_RenderDrawLine(windowObject->renderer, circle->position.x - offsetX, circle->position.y - offsetY, circle->position.x + offsetX, circle->position.y - offsetY);
		SDL_RenderDrawLine(windowObject->renderer, circle->position.x - offsetY, circle->position.y - offsetX, circle->position.x + offsetY, circle->position.y - offsetX);

		if (d >= 2*offsetX) {
			d -= 2*offsetX + 1;
			offsetX +=1;
		}
		else if (d < 2 * (circle->radius - offsetY)) {
			d += 2 * offsetY - 1;
			offsetY -= 1;
		}
		else {
			d += 2 * (offsetY - offsetX - 1);
			offsetY -= 1;
			offsetX += 1;
		}
	}
	return 0;
}

int drawCircleList(struct Node* circleList, struct WindowObject* windowObject) {

	if(!circleList) {
		return 0;
	}

	struct Node* curr = circleList;

	do{
		drawCircle((struct Circle*)curr->value, windowObject);
	}while((curr = curr->next));

	return 0;
}

int presentBuffer(struct WindowObject* windowObject) {
	SDL_RenderPresent(windowObject->renderer);
	SDL_SetRenderDrawColor(windowObject->renderer, 255, 255, 255, 0);
	SDL_RenderClear(windowObject->renderer);
	return 0;
}

int presentGrayBuffer(struct WindowObject* windowObject) {
	SDL_RenderPresent(windowObject->renderer);
	SDL_SetRenderDrawColor(windowObject->renderer, 80, 80, 80, 0);
	SDL_RenderClear(windowObject->renderer);
	return 0;
}
