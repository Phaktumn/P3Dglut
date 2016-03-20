#include "Matrix.h"
#include "../vec3f.h"
#include "../Quaternion/Quaternion.h"
#include <vector>

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

		data[3] * matrix.data[0] + data[4] * matrix.data[3] + data[5] * matrix.data[6],
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


void Matrix::Matrix3::setInverse(const Matrix3& m) 
{
	auto t4 = m.data[0] * m.data[4];
	auto t6 = m.data[0] * m.data[5];
	auto t8 = m.data[1] * m.data[3];
	auto t10 = m.data[2] * m.data[3];
	auto t12 = m.data[1] * m.data[6];
	auto t14 = m.data[2] * m.data[6];
	
	// Calculate the determinant.
	auto t16 = t4*m.data[8] - t6*m.data[7] - t8*m.data[8] +
		t10*m.data[7] + t12*m.data[5] - t14*m.data[4];

	// Make sure the determinant is non-zero.
	if (t16 == float(0.0f)) return;
	auto t17 = 1 / t16;

	data[0] = (m.data[4] * m.data[8] - m.data[5] * m.data[7])*t17;
	data[1] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7])*t17;
	data[2] = (m.data[1] * m.data[5] - m.data[2] * m.data[4])*t17;
	data[3] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6])*t17;
	data[4] = (m.data[0] * m.data[8] - t14)*t17;
	data[5] = -(t6 - t10)*t17;
	data[6] = (m.data[3] * m.data[7] - m.data[4] * m.data[6])*t17;
	data[7] = -(m.data[0] * m.data[7] - t12)*t17;
	data[8] = (t4 - t8)*t17;
}

void Matrix::Matrix3::setTranspose(const Matrix3& matrix)
{
	data[0] = matrix.data[0];
	data[1] = matrix.data[3];
	data[2] = matrix.data[6];
	data[3] = matrix.data[1];
	data[4] = matrix.data[4];
	data[5] = matrix.data[7];
	data[6] = matrix.data[2];
	data[7] = matrix.data[5];
	data[8] = matrix.data[8];
}

Matrix::Matrix3 Matrix::Matrix3::Inverse() const
{
	Matrix3 result;
	result.setInverse(*this);
	return result;
}

void Matrix::Matrix3::Invert()
{
	setInverse(*this);
}

Matrix::Matrix3 Matrix::Matrix3::Transpose() const
{
	Matrix3 result;
	result.setTranspose(*this);
	return result;
}

void Matrix::Matrix3::setOrientation(const Quaternion& q)
{
	data[0] = 1 - (2  * q.y * q.y + 2   * q.z * q.z);
	data[1] = 2 * q.x * q.y + 2   * q.z * q.w;
	data[2] = 2 * q.x * q.z - 2   * q.y * q.w;
	data[3] = 2 * q.x * q.y - 2   * q.z * q.w;
	data[4] = 1 - (2  * q.x * q.x + 2   * q.z * q.z);
	data[5] = 2 * q.y * q.z + 2   * q.x * q.w;
	data[6] = 2 * q.y * q.z + 2   * q.x * q.w;
	data[7] = 2 * q.y * q.z - 2   * q.x * q.w;
	data[8] = 1 - (2  * q.x * q.x + 2   * q.y * q.y);
}

//END MATRIX 3 BY 3 ============================================================

//MATRIX 4 BY 4 ==========================================================
Matrix::Matrix4::Matrix4()
{

}

Matrix::Matrix4::Matrix4(float M11, float M12, float M13, float M14, 
	float M21, float M22, float M23, float M24,
	float M31, float M32, float M33, float M34)
{
	data[0] = M11;
	data[1] = M12;
	data[2] = M13;
	data[3] = M14;

	data[4] = M21;
	data[5] = M22;
	data[6] = M23;
	data[7] = M24;

	data[8] = M31;
	data[9] = M32;
	data[10] = M33;
	data[11] = M34;
}

Matrix::Matrix4::~Matrix4()
{

}

float Matrix::Matrix4::getDeterminant() const
{
	return data[8] * data[5] * data[2] +
		data[4] * data[9] * data[2] +
		data[8] * data[1] * data[6] -
		data[0] * data[9] * data[6] -
		data[4] * data[1] * data[10] +
		data[0] * data[5] * data[10];
}

Matrix::Matrix4 Matrix::Matrix4::Inverse() const
{
	Matrix4 result_matrix4;
	result_matrix4.setInverse(*this);
	return result_matrix4;
}

void Matrix::Matrix4::Invert()
{
	setInverse(*this);
}

void Matrix::Matrix4::setOrientationAndPos(Quaternion& q, vec::Vector3& pos)
{
	data[0] = 1 - (2  * q.y * q.y + 2   * q.z * q.z);
	data[1] = 2 * q.x * q.y +   2 * q.z * q.w;
	data[2] = 2 * q.x * q.z -   2 * q.y * q.w;
	data[3] = pos.x;
	data[4] = 2 * q.x * q.y - 2  * q.z * q.w;
	data[5] = 1 - (2  * q.x * q.x + 2  * q.z * q.z);
	data[6] = 2 * q.y * q.z + 2  * q.x * q.w;
	data[7] = pos.y;
	data[8] = 2 * q.x * q.z + 2   * q.y * q.w;
	data[9] = 2 * q.y * q.z - 2   * q.x * q.w;
	data[10]= 1 - (2  * q.x * q.x + 2   * q.y * q.y);
	data[11]= pos.z;
}

vec::Vector3 Matrix::Matrix4::transform(const vec::Vector3& vec)
{
	auto tmp = vec;
	tmp.x -= data[3];
	tmp.y -= data[7];
	tmp.z -= data[11];
	return vec::Vector3(
		tmp.x * data[0] + tmp.y * data[4] + tmp.z * data[8],
		tmp.x * data[1] + tmp.y * data[5] + tmp.z * data[9],
		tmp.x * data[2] + tmp.y * data[6] + tmp.z * data[10]);
}

void Matrix::Matrix4::setInverse(const Matrix4& m)
{
	// Make sure the determinant is non-zero
	//JUST THAT BRO!
	auto det = getDeterminant();
	if (det == 0) return;
	det = float(1.0) / det;
	//FUCKING GAY code
	data[0] = (-m.data[9] * m.data[6] + m.data[5] * m.data[10]) * det;
	data[4] = (m.data[8] * m.data[6] - m.data[4] * m.data[10]) * det;
	data[8] = (-m.data[8] * m.data[5] + m.data[4] * m.data[9] * m.data[15]) * det;
	data[1] = (m.data[9] * m.data[2] - m.data[1] * m.data[10]) * det;
	data[5] = (-m.data[8] * m.data[2] + m.data[0] * m.data[10]) * det;
	data[9] = (m.data[8] * m.data[1] - m.data[0] * m.data[9] * m.data[15]) * det;
	data[2] = (-m.data[5] * m.data[2] + m.data[1] * m.data[6] * m.data[15]) * det;
	data[6] = (+m.data[4] * m.data[2] - m.data[0] * m.data[6] * m.data[15]) * det;
	data[10] = (-m.data[4] * m.data[1] + m.data[0] * m.data[5] * m.data[15]) * det;
	data[3] = (m.data[9] * m.data[6] * m.data[3]
		- m.data[5] * m.data[10] * m.data[3]
		- m.data[9] * m.data[2] * m.data[7]
		+ m.data[1] * m.data[10] * m.data[7]
		+ m.data[5] * m.data[2] * m.data[11]
		- m.data[1] * m.data[6] * m.data[11]) * det;
	data[7] = (-m.data[8] * m.data[6] * m.data[3]
		+ m.data[4] * m.data[10] * m.data[3]
		+ m.data[8] * m.data[2] * m.data[7]
		- m.data[0] * m.data[10] * m.data[7]
		- m.data[4] * m.data[2] * m.data[11]
		+ m.data[0] * m.data[6] * m.data[11]) * det;
	data[11] = (m.data[8] * m.data[5] * m.data[3]
		- m.data[4] * m.data[9] * m.data[3]
		- m.data[8] * m.data[1] * m.data[7]
		+ m.data[0] * m.data[9] * m.data[7]
		+ m.data[4] * m.data[1] * m.data[11]
		- m.data[0] * m.data[5] * m.data[11]) * det;
}

vec::Vector3 Matrix::Matrix4::operator*(const vec::Vector3& vector) const
{
	return vec::Vector3(vector.x * data[0] + vector.y * data[1] + vector.z + data[2] + data[3],
	                    vector.x * data[4] + vector.y * data[5] + vector.z + data[6] + data[7],
	                    vector.x * data[8] + vector.y * data[9] + vector.z + data[10] + data[11]);
}

Matrix::Matrix4 Matrix::Matrix4::operator*(const Matrix4& o) const
{
	Matrix4 result;
	result.data[0] = o.data[0] * data[0] + o.data[4] * data[1] +
		o.data[8] * data[2];
	result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) +
		(o.data[8] * data[6]);
	result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) +
		(o.data[8] * data[10]);
	result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) +
		(o.data[9] * data[2]);
	result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) +
		(o.data[9] * data[6]);
	result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) +
		(o.data[9] * data[10]);
	result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) +
		(o.data[10] * data[2]);
	result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) +
		(o.data[10] * data[6]);
	result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) +
		(o.data[10] * data[10]);
	result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) +
		(o.data[11] * data[2]) + data[3];
	result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) +
		(o.data[11] * data[6]) + data[7];
	result.data[11] = o.data[3] * data[8] + o.data[7] * data[9] +
		o.data[11] * data[10] + data[11];

	return result;
}

//END MATRIX 4 BY 4 ============================================================
