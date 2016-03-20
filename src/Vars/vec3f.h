#pragma once
#include <string>
#include "MathHelper.h"
#include "Matrix/Matrix.h"

namespace Matrix{
	class Matrix4;
}

namespace vec
{
	//operators + - /
	//enum float1 float2 float3
	//       x       y      z

	class Vector3
	{
	public:
		//Static Fields
		static Vector3 zero() { return  Vector3(.0f, .0f, .0f); }
		static Vector3 one() { return Vector3(1.0f, 1.0f, 1.0f); }
		static Vector3 unitX() { return Vector3(1.0f, 0.0f, 0.0f); }
		static Vector3 unitY() { return Vector3(0.0f, 1.0f, 0.0f); }
		static Vector3 unitZ() { return Vector3(0.0f, 0.0f, 1.0f); }
		static Vector3 up() { return Vector3(0.0f, 1.0f, 0.0f); }
		static Vector3 down() { return Vector3(0.0f, -1.0f, 0.0f); }
		static Vector3 right() { return Vector3(1.0f, 0.0f, 0.0f); }
		static Vector3 left() { return Vector3(-1.0f, 0.0f, 0.0f); }
		
		//Public Fields
  		float x;
		float y;
		float z;

		Vector3();
		Vector3(float x, float y, float z);
		explicit Vector3(float value);
		Vector3(float value, float z);

		Vector3 localToWord(const Vector3& local, Matrix::Matrix4& transform);
		Vector3 worldToLocal(const Vector3& local, Matrix::Matrix4& transform);

		~Vector3();

		std::string debugString() const;

		static Vector3* Clamp(Vector3* value1, Vector3* min, Vector3* max);
		static Vector3* Cross(Vector3* vector1, Vector3* vector2);
		static float Distance(Vector3* vector1, Vector3* vector2);
		static float DistanceSquared(Vector3* vector1, Vector3* vector2);
		static Vector3* Normalize(Vector3* value);

		Vector3 operator+(const Vector3 & v) const
		{
			auto vec = Vector3();
			vec.x = this->x + v.x;
			vec.y = this->y + v.y;
			vec.z = this->z + v.z;
			return vec;
		}

		Vector3* operator-(const Vector3 & v) const
		{
			auto vec = new Vector3();
			vec->x = this->x - v.x;
			vec->y = this->y - v.y;
			vec->z = this->z - v.z;
			return vec;
		}

		Vector3 operator*(const Vector3 & v) const {
			auto vec = Vector3();
			vec.x = this->x * v.x;
			vec.y = this->y * v.y;
			vec.z = this->z * v.z;
			return vec;
		}

		Vector3 operator*(const float f) const {
			auto vec = Vector3();
			vec.x = this->x * f;
			vec.y = this->y * f;
			vec.z = this->z * f;
			return vec;
		}

		Vector3 operator/(const float scalar) const {
			auto vec = Vector3();
			vec.x = this->x / scalar;
			vec.y = this->y / scalar;
			vec.z = this->z / scalar;
			return vec;
		}

		bool operator==(const Vector3 & v) const
		{
			return this->x == v.x 
				&& this->y == v.y 
				&& this->z == v.z;
		}

		bool operator!=(const Vector3& v1) const
		{
			return this->x != v1.x
				&& this->y != v1.y
				&& this->z != v1.z;
		}
	};

	inline Vector3::Vector3(): x(0), y(0), z(0)
	{ /*empty tho XDDD*/ }

	inline Vector3::Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline Vector3::Vector3(float value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
	}

	inline Vector3::Vector3(float value, float z)
	{
		this->x = value;
		this->y = value;
		this->z = z;
	}

	inline Vector3 Vector3::localToWord(const Vector3& local, Matrix::Matrix4& transform)
	{
		return transform.transform(local);
	}

	inline Vector3 Vector3::worldToLocal(const Vector3& local, Matrix::Matrix4& transform)
	{
		Matrix::Matrix4 inverse_matrix4;
		inverse_matrix4 = transform.Inverse();
		return inverse_matrix4.transform(local);
	}

	inline Vector3::~Vector3()
	{

	}

	inline std::string Vector3::debugString() const
	{
		auto value1 = this->x, value2 = this->y, value3 = this->z;
		auto debug = "{ X: " + std::to_string(value1) + " Y: "+ std::to_string(value2) + " Z: " + std::to_string(value3) + " }";
		return debug;
	}

	inline Vector3 * Vector3::Clamp(Vector3 * value1, Vector3* min, Vector3* max)
	{
		return new Vector3(
			MathHelper::Clampf(value1->x, min->y, max->z),
			MathHelper::Clampf(value1->y, min->y, max->y),
			MathHelper::Clampf(value1->z, min->z, max->z));
	}

	inline Vector3 * Vector3::Cross(Vector3* vector1, Vector3* vector2)
	{
		auto x = vector1->y * vector2->z - vector2->y * vector1->z;
		auto y = -(vector1->x * vector2->z - vector2->x * vector1->z);
		auto z = vector1->x * vector2->x - vector2->x * vector1->y;
		return new Vector3(x, y, z);
	}

	inline float Vector3::Distance(Vector3* vector1, Vector3* vector2)
	{
		float result;
		result = DistanceSquared(vector1, vector2);
		return static_cast<float>(sqrtf(result));
	}

	inline float Vector3::DistanceSquared(Vector3* vector1, Vector3* vector2)
	{
		return (vector1->x - vector2->x) * (vector1->x - vector2->x) +
			   (vector1->y - vector2->y) * (vector1->y - vector2->y) +
			   (vector1->z - vector2->z) * (vector1->z - vector2->z);
	}

	inline Vector3*
		
		Vector3::Normalize(Vector3* value)
	{
		auto Factor = Distance(value, &zero());
		Factor = 1.0f / Factor;
		return new Vector3(value->x * Factor, value->y * Factor, value->z * Factor);
	}
}
