#include "Vector2f.h"
// Constructor 1
Vector2f::Vector2f()
{
	x = 0.0f;
	y = 0.0f;
	 
}

// Constructor 2
Vector2f::Vector2f(float x1, float y1)
{ // To allow other values for X, Y and  to be declared
	x = x1;
	y = y1;
	 
}








float Vector2f::Length()
{  // A method to return the length of the vector
	return sqrt(x * x + y * y );
}
float Vector2f::LengthSquared()
{  // A method to return the length squared of the vector
	return (x * x + y * y  );
}

void Vector2f::Normalise()
{  // A method to reduce the length of the vector to 1.0 
	// keeping the direction the same
	if (Length() > 0.0)
	{  // Check for divide by ero
		float magnit = Length();
		x /= magnit;
		y /= magnit;
		
	}
}




Vector2f Vector2f::operator +(Vector2f V1)
{  // An overloaded operator + to return the sum of 2 vectors
	return   { x + V1.x, y + V1.y };
}

Vector2f Vector2f::operator -(Vector2f V1)
{ // An overloaded operator - to return the difference of 2 vectors
	return  { x - V1.x, y - V1.y };
}

Vector2f Vector2f::operator -()
{// An overloaded operator - to return the negation of a single vector


	return { -x,-y};
}

float Vector2f::operator *(Vector2f V1)
{// An overloaded operator * to return the scalar product of 2 vectors
	return (x * V1.x + y * V1.y);
}

Vector2f Vector2f::operator *(float k)
{// An overloaded operator * to return the product of a scalar by a vector
	return { x * k, y * k };
}



Vector2f Vector2f::operator *(int k)
{// An overloaded operator * to return the product of a scalar by a vector
	return  { x * k, y * k };
}



std::string Vector2f::ToString()
{
	return "(" + std::to_string(x) + "," + std::to_string(y) +  ")";
}
Vector2f Vector2f::operator*(double k)
{// An overloaded operator * to return the product of a scalar by a vector
	return  Vector2f(x * (float)k, y * (float)k);
}
float Vector2f::getX()
{
	return x;
}
void Vector2f::setX(float t_x)
{
	x = t_x;
}

float Vector2f::getY()
{
	return y;
}
void Vector2f::setY(float t_y)
{
	y = t_y;
}