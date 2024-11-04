#include <math.h>
#include "vector.h"

double dotProduct(struct Vector first, struct Vector second) {
	return first.x * second.x + first.y * second.y;
}

double normsqua(struct Vector vector) {
	return dotProduct(vector, vector);
}

double norm(struct Vector vector) {
	return sqrt(normsqua(vector));
}

struct Vector multiply(double scalar, struct Vector vector) {
	struct Vector result = {scalar * vector.x, scalar * vector.y};
	return result;
}

struct Vector add(struct Vector first, struct Vector second) {
	struct Vector result = {first.x + second.x, first.y + second.y};
	return result;
}

struct Vector subtract(struct Vector first, struct Vector second) {
	struct Vector result = {first.x - second.x, first.y - second.y};
	return result;
}

