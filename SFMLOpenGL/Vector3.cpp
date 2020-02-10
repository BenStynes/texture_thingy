#include "vector3.h"

// Constructor 1
vector3::vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

// Constructor 2
vector3::vector3(float x1, float y1, float z1)
{ // To allow other values for X, Y and Z to be declared
	x = x1;
	y = y1;
	z = z1;
}


float vector3::getZ()
{
	return z;
}
void vector3::setZ(float t_z)
{
	z = t_z;
}





float vector3::Length()
{  // A method to return the length of the vector
	return sqrt(x * x + y * y + z * z);
}
float vector3::LengthSquared()
{  // A method to return the length squared of the vector
	return (x * x + y * y + z * z);
}

void vector3::Normalise()
{  // A method to reduce the length of the vector to 1.0 
	// keeping the direction the same
	if (Length() > 0.0)
	{  // Check for divide by zero
		float magnit = Length();
		x /= magnit;
		y /= magnit;
		z /= magnit;
	}
}




vector3 vector3::operator +(vector3 V1)
{  // An overloaded operator + to return the sum of 2 vectors
	return   { x + V1.x, y + V1.y, z + V1.z };
}

vector3 vector3::operator -(vector3 V1)
{ // An overloaded operator - to return the difference of 2 vectors
	return  { x - V1.x, y - V1.y, z - V1.z };
}

 vector3 vector3::operator -()
{// An overloaded operator - to return the negation of a single vector
	

	 return {-x,-y,-z};
}

 float vector3::operator *(vector3 V1)
{// An overloaded operator * to return the scalar product of 2 vectors
	return (x * V1.x + y * V1.y + z * V1.z);
}

 vector3 vector3::operator *(float k)
{// An overloaded operator * to return the product of a scalar by a vector
	 return { x * k, y * k, z * k };
}



 vector3 vector3::operator *(int k)
{// An overloaded operator * to return the product of a scalar by a vector
	 return  { x * k, y * k, z * k };
}

 vector3 vector3::operator ^(vector3 V1)
{// An overloaded operator ^ to return the vector product of 2 vectors
	 return { y * V1.z - z * V1.y, z * V1.x - x * V1.z, x * V1.y - y * V1.x };
}

std::string vector3::ToString()
{
	return "(" + std::to_string(x)  + "," + std::to_string(y)  + "," + std::to_string(z)  + ")";
}
vector3 vector3::operator*(double k)
{// An overloaded operator * to return the product of a scalar by a vector
	return  vector3(x * (float)k, y * (float)k, z * (float)k);
}
float vector3::getX()
{
	return x;
}
void vector3::setX(float t_x)
{
	x = t_x;
}

float vector3::getY()
{
	return y;
}
void vector3::setY(float t_y)
{
	y = t_y;
}