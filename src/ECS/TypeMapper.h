#pragma once
#include <typeinfo>

namespace p3d
{
	long getMask(const type_info& type);

	template <typename T>
	long getMask()
	{
		return getMask(typeid(T));
	}
}