#pragma once
#include<iostream>
#include"vector3.h"
#include<cmath>


class Matrix3
{


	// The class has nine variables, 3 rows and 3 columns
public:
			float A11;
			 float A12;
			 float A13;
			 float A21;
			 float A22;
			 float A23;
			 float A31;
			 float A32;
			 float A33;

			// Constructor 1 create a zero matrix
			 Matrix3();

			 Matrix3(vector3 Row1, vector3 Row2, vector3 Row3);

			 Matrix3(float _A11, float _A12, float _A13, float _A21, float _A22, float _A23, float _A31, float _A32, float _A33);

			 vector3 operator*(vector3 V1);

			 Matrix3 Transpose(Matrix3 M1);

			 Matrix3 operator+(Matrix3 M2);

			 Matrix3 operator-(Matrix3 M2);

			static Matrix3 RotationX(int _angle);

			 Matrix3 RotationY(int _angle);

			static Matrix3 RotationZ(int _angle);

			 Matrix3 Scale3D(int dx);

			 std::string toString() const;

			 Matrix3 operator*(float x);

			 Matrix3 operator*(Matrix3 M2);

			 float Determinant(Matrix3 M1);

			 vector3 Row(int i);

			 vector3 Column(int i);

			 Matrix3 Inverse(Matrix3 M1);

			 Matrix3 Rotation(int _angle);

			 Matrix3 Translate(double dx, double dy);

			 Matrix3 Scale(int dx, int dy);
			 Matrix3 operator-();
		};
	

