#pragma once

#include "Class.h"
#include "Utility.h"

#include <string>
#include <unordered_map>

namespace LavaEnv {
	class ClassRegistry {
	public:
		LAVA_CALL_CONV Class* registerClass(RegisterClass&& clazz);
		LAVA_CALL_CONV void deregisterClass(const std::string& id);

		LAVA_CALL_CONV Class* getClass(const std::string& id) const;
		LAVA_CALL_CONV Class* getClassC(const char* id) const { return getClass(id); }

	private:
		std::unordered_map<std::string, Class*> m_Classes;
	};
} // namespace LavaEnv
