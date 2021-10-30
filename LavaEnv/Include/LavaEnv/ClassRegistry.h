#pragma once

#include "Class.h"
#include "ClassLoader.h"
#include "Utility.h"

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

namespace LavaEnv {
	class ClassRegistry {
	public:
		LAVA_CALL_CONV Class* loadClass(std::string_view id);

		LAVA_CALL_CONV Class* registerClass(RegisterClass&& clazz);
		LAVA_CALL_CONV void deregisterClass(const std::string& id);

		LAVA_CALL_CONV void registerClassLoader(ClassLoader& classLoader);
		LAVA_CALL_CONV void deregisterClassLoader(ClassLoader& classLoader);

		LAVA_CALL_CONV Class* getClass(const std::string& id);
		LAVA_CALL_CONV Class* getClassC(const char* id) { return getClass(id); }

	private:
		std::unordered_set<ClassLoader*> m_ClassLoaders;
		std::unordered_map<std::string, Class*> m_Classes;
	};
} // namespace LavaEnv
