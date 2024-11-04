#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdint.h>
#include "linkedList.h"
#include "vector.h"

struct Circle {
	struct Vector position;
	struct Vector speed;
	double mass;
	double radius;
	uint8_t colorR;
	uint8_t colorG;
	uint8_t colorB;
};

struct Circle* createCircle(double mass, double radius, double positionX, double positionY, double speedX, double speedY, uint8_t colorR, uint8_t colorG, uint8_t colorB);
struct Circle* createRandomCircle(int positionX, int positionY);

int updateCirclePos(struct Circle* circle);
int checkCollisionWalls(struct Circle* circle, int width, int height);
int checkCollisionObject(struct Circle* first, struct Circle* second); 
int updateCircleList(struct Node* head, int width, int height);

#endif
