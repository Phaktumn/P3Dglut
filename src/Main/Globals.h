#pragma once
/*
astronomical unit(A.U.)	149, 597, 870.691 kilometers
light year(ly)	9.460536207× 10^12 km = 63, 240 A.U.
parsec(pc)	3.08567802× 10^13 km = 206, 265 A.U.
sidereal year	365.2564 days
tropical year	365.2422 days
Gregorian year	365.2425 days
Earth mass	5.9736× 1024 kilograms
Sun mass	1.9891× 1030 kg = 332, 980 × Earth
mean Earth radius	6371 kilometers
Sun radius	6.96265 × 105 km = 109 × Earth
Sun luminosity	3.827× 1026 watts
Physical Constants

Quantity	Value
speed of light(c)	299, 792.458 kilometers / second
*/


inline float _pow(float num,int _i)
{
	long float _a = 0.0f;
	for (size_t i = 0; i < _i; i++)
		_a *= num;
	return _a;
}

static const float      Universal_Metric_Scale      = 0.000001f;
static const float	    Universal_Size_Scale		= 0.0001f;

static const float      SiderealYear                = 365.2564f;
static const float      TropicalYear                = 365.2422f;
static const float      Gregorianyear		        = 365.2425;
											        
static const long float AstronomicalUnit            = 149597870691;
static const long float lightYear_KM		        = _pow(9.460536207 * 10, 12);
static const long float lightYear_AU                = _pow(9.460536207 * 10, 12) / AstronomicalUnit;
static const long float Parsec_KM	                = _pow(3.08567802  * 10, 13);
static const long float Parsec_AU                   = _pow(3.08567802  * 10, 13) / AstronomicalUnit;
static const long float meanEarthRadius_KM          = 6371.3f;
 											        
static const long float speed_of_light_MS           = 299792458;
