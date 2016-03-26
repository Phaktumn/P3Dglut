#pragma once
class Quaternion;

namespace vec{
	class Vector3;
}

/*Matrix Name Space Containig Tensor Matrix 3x3 and Tranform Matrix 4x4*/
namespace Matrix {
	class Matrix3
	{
	public:
		Matrix3();
		/*
		*Create a Matrix from 9 raw values Float
		*/
		Matrix3(float M11, float M12, float M13, 
				float M21, float M22, float M23, 
				float M31, float M32, float M33);
		/**
		*Create a Matrix from 3 vectors 3
		*/
		Matrix3(vec::Vector3 col1, vec::Vector3 col2, vec::Vector3 col3);
		~Matrix3();

		Matrix3 Inverse() const;
		void Invert();
		Matrix3 Transpose() const;
		void setOrientation(const Quaternion& quaternion);
			 
		static Matrix3 Identity() { return Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1); }

		//Tensor Matrix Data
		float data[9];

		Matrix3 operator*(const Matrix3 & matrix)const;
		vec::Vector3 operator*(const vec::Vector3 & vec)const;
		void setInverse(const Matrix3& matrix);
	private:
		float matrix_data_count = 9;
		void setTranspose(const Matrix3 &matrix);
	};

	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(float M11, float M12, float M13, float M14,
			float M21, float M22, float M23, float M24,
			float M31, float M32, float M33, float M34);
		~Matrix4();

		/** Returns the determinant of the matrix.*/
		float getDeterminant() const;

		Matrix4 Inverse() const;
		void Invert();
		void setOrientationAndPos(Quaternion &q, vec::Vector3 &vec);
		vec::Vector3 transformInverse(const vec::Vector3 &vec);
		vec::Vector3 transformDirection(const vec::Vector3 &vec);
		vec::Vector3 tranformInverseDirection(const vec::Vector3 &vec);
		vec::Vector3 transform(const vec::Vector3 &vec);

		static Matrix4 Identity() { return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0); }

		//Transform Matrix Data
		float data[12];

      /** Transform the given vector by Matrix
		* @param vector The vector to Transform*/
		vec::Vector3 operator*(const vec::Vector3 & vector) const;
		//Multiplies a matrix 4 by a matrix 4 and returns + 0001 last line
		Matrix4 operator*(const Matrix4 & matrix) const;
	private:
		float matrix_data_count = 12;
	    /**Sets the matrix to be the inverse of the given matrix.
		* @param m The matrix to invert and use to set this.*/
		void setInverse(const Matrix4 &m);
	};
}
