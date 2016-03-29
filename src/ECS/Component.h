#pragma once
#include <typeinfo>

namespace p3d
{
	struct Component
	{
		friend class EntityFactory;

		Component() { }

		const type_info& getType() const
		{
			return typeid(*this);
		}

	protected:
		virtual ~Component()
		{
		}
	};
}