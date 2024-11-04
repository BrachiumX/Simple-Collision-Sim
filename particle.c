#include <stdlib.h>
#include <stdio.h>
#include "particle.h"
#include "vector.h"

struct Circle* createCircle(double mass, double radius, double positionX, double positionY, double speedX, double speedY, uint8_t colorR, uint8_t colorG, uint8_t colorB) {
	struct Circle* circle = (struct Circle*) malloc(sizeof(struct Circle));

	if(!circle) {
		return 0;
	}

	struct Vector position = {positionX, positionY};
	struct Vector speed = {speedX, speedY};

	circle->mass = mass;
	circle->radius = radius;
	circle->position = position;
	circle->speed = speed;
	circle->colorR = colorR;
	circle->colorG = colorG;
	circle->colorB = colorB;

	printf("Created Circle: \n Mass: %f \n Radius: %f \n PositionX: %f \n PositionY: %f \n SpeedX: %f \n SpeedY: %f \n ColorR: %d \n ColorG: %d \n ColorB: %d \n", mass, radius, positionX, positionY, speedX, speedY, colorR, colorG, colorB); 

	return circle;
}

struct Circle* createRandomCircle(int positionX, int positionY) {
	int radius = rand() % 40 + 2;

	double div = RAND_MAX / 4;
	double speedX = (rand() / div) - 2;
	double speedY = (rand() / div) - 2;

	return createCircle(radius, radius, positionX, positionY, speedX, speedY, rand() % 256, rand() % 256, rand() % 256);
}

int updateCirclePos(struct Circle* circle) {

	circle->position.x += circle->speed.x;
	circle->position.y += circle->speed.y;

	return 0;
}


int updateCircleList(struct Node *head, int width, int height) {
	
	if(!head) {
		return 0;
	}

	struct Node* curr = head;

	while(curr != NULL) {
		checkCollisionWalls(curr->value, width, height);

		struct Node* currin = curr->next;

		while(currin != NULL) {
			checkCollisionObject(curr->value, currin->value);
			currin = currin->next;	
		}

		updateCirclePos(curr->value);
		curr = curr->next;
	}

	return 0;
}

int checkCollisionWalls(struct Circle *circle, int width, int height) {

	if(circle->position.x + circle->speed.x - circle->radius < 0 && circle->speed.x < 0) {
		circle->speed.x *= -1;
	}
	else if(circle->position.x + circle->speed.x + circle->radius > width && circle->speed.x > 0) {
		circle->speed.x *= -1;
	}

	if(circle->position.y + circle->speed.y - circle->radius < 0 && circle->speed.y < 0) {
		circle->speed.y *= -1;
	}
	else if(circle->position.y + circle->speed.y + circle->radius > height && circle->speed.y > 0) {
		circle->speed.y *= -1;
	}

	return 0;
}

int checkCollisionObject(struct Circle *first, struct Circle *second) {

	double radius = (first->radius + second->radius);
	double distance = norm(subtract(add(first->position, first->speed), add(second->position, second->speed)));

	if(distance < radius) {
		struct Vector tempfirst = subtract(first->speed, multiply((2 * second->mass / (first->mass + second->mass)) * (dotProduct(subtract(first->speed, second->speed), subtract(first->position, second->position)) / (normsqua(subtract(first->position, second->position)))), subtract(first->position, second->position)));
		struct Vector tempsecond = subtract(second->speed, multiply((2 * first->mass / (second->mass + first->mass)) * (dotProduct(subtract(second->speed, first->speed), subtract(second->position, first->position)) / (normsqua(subtract(second->position, first->position)))), subtract(second->position, first->position)));

		if(distance < norm(subtract(add(first->position, tempfirst), add(second->position, tempsecond)))) {
			first->speed = tempfirst;
			second->speed = tempsecond;
		}
	}

	return 0;
}
