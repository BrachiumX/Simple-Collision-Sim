#include "init.h"
#include "linkedList.h"
#include "particle.h"
#include "window.h"

#include <time.h>

#ifdef _WIN64
#include <SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

int init(int width, int height, int positionX, int positionY) {

    struct WindowObject windowObject = createWindowObject(width, height, positionX, positionY);

    srand(time(NULL));

    struct Node *head = insertNode(NULL, createRandomCircle(rand() % windowObject.width, rand() % windowObject.height));
    head = insertNode(head, createRandomCircle(rand() % windowObject.width, rand() % windowObject.height));
    head = insertNode(head, createRandomCircle(rand() % windowObject.width, rand() % windowObject.height));

    SDL_Event event;
    int quit = 1;
    int delay = 10;

    while (quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 0;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == 19) {
                    while (1) {
                        SDL_PollEvent(&event);

                        if (event.type == SDL_QUIT) {
                            quit = 0;
                            break;
                        } else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == 19) {
                            break;
                        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                            if (event.button.button == SDL_BUTTON_LEFT) {
                                struct Node *curr = head;
                                struct Vector pos = {event.button.x, event.button.y};
                                struct Circle *circle = (struct Circle *)curr->value;

                                while (norm(subtract(circle->position, pos)) > circle->radius) {
                                    if (!(curr = curr->next)) {
                                        break;
                                    }
                                    circle = (struct Circle *)curr->value;
                                }

                                if (!curr) {
                                    head = insertNode(head, createRandomCircle(event.button.x, event.button.y));
                                }

                            } else if (event.button.button == SDL_BUTTON_RIGHT && head) {
                                struct Node *curr = head;
                                struct Vector pos = {event.button.x, event.button.y};
                                struct Circle *circle = (struct Circle *)curr->value;

                                while (norm(subtract(circle->position, pos)) > circle->radius) {
                                    if (!(curr = curr->next)) {
                                        break;
                                    }
                                    circle = (struct Circle *)curr->value;
                                }

                                if (curr) {
                                    free(circle);
                                    head = deleteNode(head, curr);
                                }
                            }
                        }

                        drawCircleList(head, &windowObject);
                        presentGrayBuffer(&windowObject);
                    }

                } else if (event.key.keysym.scancode == 79 && delay) {
                    delay--;
                } else if (event.key.keysym.scancode == 80 && delay < 21) {
                    delay++;
                }
            }
        }

        updateCircleList(head, windowObject.width, windowObject.height);
        drawCircleList(head, &windowObject);
        presentBuffer(&windowObject);

        SDL_Delay(delay);
    }

    return 0;
}
