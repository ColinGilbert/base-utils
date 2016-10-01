#pragma once

namespace noob
{
	template<class T>
	class singleton
	{
		public:
			static T& get() noexcept(true) { return t; }
		private:
			static T t;
	};
}
