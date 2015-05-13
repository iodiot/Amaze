#include "stdafx.h"

#include "all_in_one.h"

Rect::Rect(double x, double y, double w, double h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

bool Rect::PtInRect(const Vector2 &v)
{
	return (v.x > x && v.x < x + w && v.y > y && v.y < y + h);
}

bool Rect::Intersects(Rect &rect)
{
	return PtInRect(Vector2(rect.x, rect.y)) 
		|| PtInRect(Vector2(rect.x + rect.w, rect.y)) 
		|| PtInRect(Vector2(rect.x, rect.y + rect.h))
		|| PtInRect(Vector2(rect.x + rect.w, rect.y + rect.h))
		|| rect.PtInRect(Vector2(x, y))
		|| rect.PtInRect(Vector2(x + w, y))
		|| rect.PtInRect(Vector2(x, y + h))
		|| rect.PtInRect(Vector2(x + w, y + h));
}

// Vector2 
Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Vector2::operator=(const Vector2 &other)
{
	x = other.x;
	y = other.y;
}

void Vector2::operator+=(const Vector2 &other)
{
	x += other.x;
	y += other.y;
}

void Vector2::operator-=(const Vector2 &other)
{
	x -= other.x;
	y -= other.y;
}

void Vector2::operator*=(double value)
{
	x *= value;
	y *= value;
}

double Vector2::Length()
{
	return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

void Vector2::Normalize(const double &value)
{
	double length = Length();
	if (length > 0) {
		x = x / length * value;
		y = y / length * value;
	} else 
		x = y = 0;
}

double Vector2::Dot(const Vector2 &v)
{
	return x * v.x + y * v.y;
}

void Vector2::Rotate(double angle)
{
	double rCos = cos(angle);
	double rSin = sin(angle);

	double t = x;
	x = x * rCos - y * rSin;
	y = t * rSin + y * rCos;
}

Vector2 Vector2::Normalized()
{
	Vector2 r = *this;
	r.Normalize();
	return r;
}

bool Vector2::IsZero()
{
	const double eps = 0.000001;

	return (fabs(x) < eps && fabs(y) < eps);
}