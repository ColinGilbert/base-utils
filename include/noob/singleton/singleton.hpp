#pragma once

namespace noob
{
	template<class T>
		class singleton
		{
			public:
				static T& get() noexcept(true)
				{
					static T t;
					return t;
				}
		};
}
