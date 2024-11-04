#ifndef VECTOR_H
#define VECTOR_H 

struct Vector {
	double x;
	double y;
};

double dotProduct(struct Vector first, struct Vector second);

double normsqua(struct Vector vector);
double norm(struct Vector vector);

struct Vector multiply(double scalar, struct Vector vector);

struct Vector add(struct Vector first, struct Vector second);
struct Vector subtract(struct Vector first, struct Vector second);

#endif
