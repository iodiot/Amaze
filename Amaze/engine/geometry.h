#ifndef GEOMETRY_H
#define GEOMETRY_H

class Vector2;

struct Rect
{
	double x, y, w, h;

	Rect(double x, double y, double w, double h);
	bool Intersects(Rect &rect);
	bool PtInRect(const Vector2 &v);
};

// Vector2
class Vector2
{
public:
	double x, y;
	
	Vector2();
	Vector2(double x, double y);

	Vector2 operator+(const Vector2 &other) const;
	Vector2 operator-(const Vector2 &other) const;
	Vector2 operator/(const double &value) const;
	Vector2 operator*(const double &value) const;
	void operator=(const Vector2 &other);
	void operator+=(const Vector2 &other);
	void operator*=(double value);
	void operator-=(const Vector2 &other);

	double Length();
	void Normalize(const double &value = 1);
	Vector2 Normalized();

	double Dot(const Vector2 &v);
	void Rotate(double angle);
	bool IsZero();
};

inline Vector2 Vector2::operator+(const Vector2 &other) const
{
	return Vector2(x + other.x, y + other.y);
}

inline Vector2 Vector2::operator-(const Vector2 &other) const
{
	return Vector2(x - other.x, y - other.y);
}

inline Vector2 Vector2::operator*(const double &value) const
{
	return Vector2(x * value, y * value);
}

inline Vector2 Vector2::operator/(const double &value) const
{
	return Vector2(x / value, y / value);
}

#endif