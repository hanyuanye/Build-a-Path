#pragma once
#include <vector>
//This is a 2d Vector class used for my own games which uses physics
//It defines a lot of functionality which may not be used in the projects
//Which include this file. 

class Vec2d
{
private:
	double x;
	double y;

public:
	Vec2d();
	Vec2d(double _x, double _y);
	Vec2d(const Vec2d& v);

	Vec2d operator=(const Vec2d&);
	Vec2d operator+(const Vec2d&) const;
	Vec2d operator+=(const Vec2d&);
	Vec2d operator-(const Vec2d&) const;
	Vec2d operator-=(const Vec2d&);

	double dotProduct(const Vec2d&) const;
	double crossProduct(const Vec2d&) const;

	double get_x() const;
	double get_y() const;

	void set_x(const double &_x);
	void set_y(const double &_y);
	void set_vector(const double  &_x, const double  &_y);

};