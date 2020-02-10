#pragma once
#include <iostream>
#include<math.h>
#include <string>
#include<cmath>
class Vector2f
{
	// The class has three variables x, y and z 
private:
	float x;
	float y;
	float z;
public:
	float getX();
	void setX(float t_x);
	Vector2f();
	const float PI = 3.14159265359f;
	Vector2f(float x1, float y1);




	float getY();
	void setY(float t_y);

	

	float Length();

	float LengthSquared();

	void Normalise();

	Vector2f operator+(Vector2f V1);

	Vector2f operator-(Vector2f V1);

	Vector2f operator-();

	float operator*(Vector2f V1);

	Vector2f operator*(float k);

	Vector2f operator*(int k);

	

	std::string ToString();

	Vector2f operator *(double k);


};

