#include "TypeMapper.h"
#include <map>
#include <typeindex>

namespace p3d
{
	static long maskCount;
	static std::map<std::type_index, long> masks;

	long getTypeMask(const type_info& type)
	{
		std::type_index index = std::type_index(type);
		std::map<std::type_index, long>::iterator it = masks.find(index);
		if (it != masks.end())
		{
			return it->second;
		}

		masks[index] = pow(2, maskCount);
		maskCount++;

		return masks[index];
	}

	long getMask(const type_info& type)
	{
		return getTypeMask(type);
	}
}
