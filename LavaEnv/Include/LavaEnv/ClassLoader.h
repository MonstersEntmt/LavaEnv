#pragma once

#include <string_view>

namespace LavaEnv {
	struct Class;

	class ClassLoader {
	public:
		virtual bool canLoadClass(std::string_view classId) = 0;
		virtual Class* loadClass(std::string_view classId)  = 0;
	};
} // namespace LavaEnv