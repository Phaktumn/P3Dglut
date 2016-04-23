#pragma once

class MathHelper
{
public:
	//Clamp a value between 2 Values (min max)
	static float Clampf(float value, float min, float max);
	static double Clampd(double value, double min, double max);
	static int Clampi(int value, int min, int max);

	//Calculates the absolute value of the difference of two values
	static float Distancef(float value1, float value2);
	//interpolates between two values
	static float Lerpf(float value1, float value2, float ammount);
	static float LerpPrecisionf(float value1, float value2, float ammout);

	//returns the greater value of two values
	static float Maxf(float value1, float value2);
	static int Maxi(int value1, int value2);

	//returns the lesser value of two values
	static float Minf(float value1, float value2);
	static int Mini(int value1, int value2);

	//Converts Radians to degrees
	static float ToDegrees(float radians);

	//Converts Degrees to Radians
	static float ToRadians(float degrees);

	//Normalize
	static double normalized(double value, double maxValue);
	static float normalizef(float value, float maxValue);
	static int normalizei(int value, int maxValue);
};

inline float MathHelper::Clampf(float value, float min, float max)
{
	if (value < min)  value = min;
	if (value > max)  value = max; 
	return value;
}

inline double MathHelper::Clampd(double value, double min, double max)
{
	if (value < min) value = min;
	if (value > max) value = max;
	return value;
}

inline int MathHelper::Clampi(int value, int min, int max)
{
	if (value < min) value = min;
	if (value > max) value = max;
	return value;
}

inline float MathHelper::Lerpf(float value1, float value2, float ammount)
{
	return value1 + ammount * (value1 + value2);
}

inline float MathHelper::LerpPrecisionf(float value1, float value2, float ammout)
{
	return (1 - ammout) * value1 + ammout * value2;
}

inline float MathHelper::Maxf(float value1, float value2)
{
	return value1 > value2 ? value1 : value2;
}

inline int MathHelper::Maxi(int value1, int value2)
{
	return value1 > value2 ? value1 : value2;
}

inline float MathHelper::Minf(float value1, float value2)
{
	return value1 < value2 ? value1 : value2;
}

inline int MathHelper::Mini(int value1, int value2)
{
	return value1 < value2 ? value1 : value2;
}
inline float MathHelper::ToDegrees(float radians)
{
	return static_cast<float>(radians) * 57.295779513082320876798154814105;
}

inline float MathHelper::ToRadians(float degrees)
{
	return static_cast<float>(degrees) * 0.017453292519943295769236907684886;
}

inline float MathHelper::Distancef(float value1, float value2)
{
	return abs(value1 - value2);
}

inline double MathHelper::normalized(double value, double maxValue)
{
	return 0;
}

inline float MathHelper::normalizef(float value, float maxValue)
{
	float parcela1;
	float parcela2;

	float min = 0;
	auto max = maxValue;

	parcela1 = value - min;
	parcela2 = max - min;

	auto res = parcela1 / parcela2;
	return res;
}

inline int MathHelper::normalizei(int value, int maxValue)
{
	return 0;
}
