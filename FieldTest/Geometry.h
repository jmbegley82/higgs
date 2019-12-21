#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct {
	double x, y;
} DoublePair;

typedef DoublePair Point;
typedef DoublePair Motion;

typedef struct {
	Point topLeft;
	Point topRight;
	Point bottomLeft;
	Point bottomRight;
} QuadPoint;

#endif //GEOMETRY_H
