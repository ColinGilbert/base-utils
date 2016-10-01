#pragma once

namespace noob
{
	template<class T>
	class singleton
	{
		public:
			singleton(T arg) noexcept(true) : t(arg) {}
			T& get() const noexcept(true) { return t; }
		private:
			T t;
	};
}
