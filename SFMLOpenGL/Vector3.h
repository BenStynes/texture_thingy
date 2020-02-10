#pragma once
#include <iostream>
#include<math.h>
#include <string>
#include<cmath>

		class vector3
		{
			// The class has three variables x, y and z 
		private:
			float x;
			float y;
			float z;
		public:
			float getX();
			void setX(float t_x);
			vector3();
			const float PI = 3.14159265359f;
			vector3(float x1, float y1, float z1);

			
			
			 
			float getY();
			void setY(float t_y);

			float getZ();
			void setZ(float t_z);

			float Length();

			float LengthSquared();

			void Normalise();

			 vector3 operator+(vector3 V1);

			 vector3 operator-(vector3 V1);

			 vector3 operator-();

			float operator*(vector3 V1);

			 vector3 operator*(float k);

			 vector3 operator*(int k);

			 vector3 operator^(vector3 V1);

			std::string ToString();

			vector3 operator *(double k);
			

			

		};
	
	
