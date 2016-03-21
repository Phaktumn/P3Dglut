#pragma once
class BoxShape
{
public:
	BoxShape();
	~BoxShape();

	float width;
	float height;
	float depth;
	float mass;
	Quaternion momentOfInertia;

	static void calculateBoxInertia(BoxShape* box_shape);
};

inline BoxShape::BoxShape(): 
	width(0), height(0), depth(0), mass(0)
{
}

inline BoxShape::~BoxShape()
{
}

inline void BoxShape::calculateBoxInertia(BoxShape* box_shape)
{
	auto m = box_shape->mass;
	auto w = box_shape->width;
	auto h = box_shape->height;
	auto d = box_shape->depth;
	box_shape->momentOfInertia = Quaternion(m / 12 * (w*w + d*d),
		m / 12 * (d*d + h*h),m / 12 * (w*w + h*h), 0);
}
