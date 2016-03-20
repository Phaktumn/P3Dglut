#pragma once
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
		*Create a Matrix from 9 raw values sizeOf Float
		*/
		Matrix3(float M11, float M12, float M13, 
				float M21, float M22, float M23, 
				float M31, float M32, float M33);
		/**
		*Create a Matrix from 3 vectors 3
		*/
		Matrix3(vec::Vector3 col1, vec::Vector3 col2, vec::Vector3 col3);
		~Matrix3();

		static Matrix3 Identity() { return Matrix3(1, 0, 0,
												   0, 1, 0, 
												   0, 0, 1); }

		//Tensor Matrix Data
		float data[9];

		Matrix3 operator*(const Matrix3 & matrix)const;
		vec::Vector3 operator*(const vec::Vector3 & vec)const;
	private:
		float matrix_data_count = 9;
	};

	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(float M11, float M12, float M13, float M14,
			float M21, float M22, float M23, float M24,
			float M31, float M32, float M33, float M34, 
			float M41, float M42, float M43, float M44);
		~Matrix4();

		//Transform Matrix Data
		float data[12];

		/**
		* Transform the given vector by Matrix
		*
		* @param vector The vector to Transform
		*/
		vec::Vector3 operator*(const vec::Vector3 & vector) const;
	private:
		float matrix_data_count = 12;
	};
}
