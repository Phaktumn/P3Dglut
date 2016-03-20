#include "Matrix.h"
#include "../vec3f.h"

//MATRIX 3 BY 3 ==========================================================
Matrix::Matrix3::Matrix3()
{
	//Initialize Matrix all with 0 values!
	for (size_t i = 0; i < matrix_data_count; i++){
		data[i] = 0;
	}
}

Matrix::Matrix3::Matrix3(float M11, float M12, float M13, 
	float M21, float M22, float M23, 
	float M31, float M32, float M33)
{
	data[0] = M11;
	data[1] = M12;
	data[2] = M13;

	data[3] = M21;
	data[4] = M22;
	data[5] = M23;

	data[6] = M31;
	data[7] = M32;
	data[8] = M33;
}

/**
*Create a Matrix from 3 vectors 3
*/
Matrix::Matrix3::Matrix3(vec::Vector3 col1, vec::Vector3 col2, vec::Vector3 col3)
{
	data[0] = col1.x;
	data[1] = col1.y;
	data[2] = col1.z;

	data[3] = col2.x;
	data[4] = col2.y;
	data[5] = col2.z;

	data[6] = col3.x;
	data[7] = col3.y;
	data[8] = col3.z;

}

Matrix::Matrix3::~Matrix3()
{

}

Matrix::Matrix3 Matrix::Matrix3::operator*(const Matrix3& matrix) const
{
	return Matrix3(
		data[0] * matrix.data[0] + data[1] * matrix.data[3] + data[2] * matrix.data[6],
		data[0] * matrix.data[1] + data[1] * matrix.data[4] + data[2] * matrix.data[7],
		data[0] * matrix.data[2] + data[1] * matrix.data[5] + data[2] * matrix.data[8],

		data[3] * matrix.data[4] + data[4] * matrix.data[3] + data[5] * matrix.data[6],
		data[3] * matrix.data[1] + data[4] * matrix.data[4] + data[5] * matrix.data[7],
		data[3] * matrix.data[2] + data[4] * matrix.data[5] + data[5] * matrix.data[8],
		
		data[6] * matrix.data[0] + data[7] * matrix.data[3] + data[8] * matrix.data[6],
		data[6] * matrix.data[1] + data[7] * matrix.data[4] + data[8] * matrix.data[7],
		data[6] * matrix.data[2] + data[7] * matrix.data[5] + data[8] * matrix.data[8]);
}

vec::Vector3 Matrix::Matrix3::operator*(const vec::Vector3& vec) const
{
	return {};
}

//END MATRIX 3 BY 3 ============================================================

//MATRIX 4 BY 4 ==========================================================
Matrix::Matrix4::Matrix4()
{

}

Matrix::Matrix4::Matrix4(float M11, float M12, float M13, float M14, 
	float M21, float M22, float M23, float M24,
	float M31, float M32, float M33, float M34,
	float M41, float M42, float M43, float M44)
{
}

Matrix::Matrix4::~Matrix4()
{

}

vec::Vector3 Matrix::Matrix4::operator*(const vec::Vector3& vector) const
{
	return vec::Vector3(vector.x * data[0] + vector.y * data[1] + vector.z + data[2] + data[3],
	                    vector.x * data[4] + vector.y * data[5] + vector.z + data[6] + data[7],
	                    vector.x * data[8] + vector.y * data[9] + vector.z + data[10] + data[11]);
}

//END MATRIX 4 BY 4 ============================================================
