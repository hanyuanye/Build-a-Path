#include "Vec2d.h"

Vec2d::Vec2d()
{
	x = 0;
	y = 0;
}

Vec2d::Vec2d(double _x, double _y)
{
	x = _x;
	y = _y;
}

Vec2d::Vec2d(const Vec2d & v)
{
	x = v.get_x();
	y = v.get_y();
}

Vec2d Vec2d::operator=(const Vec2d & v)
{
	x = v.get_x();
	y = v.get_y();
	return Vec2d();
}

Vec2d Vec2d::operator+(const Vec2d & v) const
{
	Vec2d result;
	result.set_x(this->x + v.get_x());
	result.set_y(this->y + v.get_y());
	return result;
}

Vec2d Vec2d::operator+=(const Vec2d & v)
{
	this->set_x(this->x + v.get_x());
	this->set_y(this->y + v.get_y());
	return *this;
}

Vec2d Vec2d::operator-(const Vec2d & v) const
{
	Vec2d result;
	result.set_x(this->x - v.get_x());
	result.set_y(this->y - v.get_y());
	return result;
}

Vec2d Vec2d::operator-=(const Vec2d & v)
{
	this->set_x(this->x - v.get_x());
	this->set_y(this->y - v.get_y());
	return *this;
}

double Vec2d::dotProduct(const Vec2d & v) const
{
	return (x * v.get_x() + y * v.get_x());
}

double Vec2d::crossProduct(const Vec2d & v) const
{
	return (x * v.get_y() - y * v.get_x());
}

double Vec2d::get_x() const
{
	return x;
}

double Vec2d::get_y() const
{
	return y;
}

void Vec2d::set_x(const double & _x)
{
	x = _x;
}

void Vec2d::set_y(const double & _y)
{
	y = _y;
}

void Vec2d::set_vector(const double & _x, const double & _y)
{
	x = _x;
	y = _y;
}

