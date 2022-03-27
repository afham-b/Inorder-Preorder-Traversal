#ifndef POINT_H
#define POINT_H

class Point {
private:
	int x, y;
public:
	Point () { x = 0; y = 0; }
	Point (int initx, int inity) { x = initx; y = inity; }
	int get_x () { return x; }
	int get_y () { return y; }
	bool operator< (const Point& p) const
		{ return x < p.x || (x == p.x && y < p.y); }
};

#endif
