#include "LavaEnv/ClassRegistry.h"

namespace LavaEnv {
	LAVA_CALL_CONV Class* ClassRegistry::registerClass(RegisterClass&& clazz) {
		if (getClass(clazz.m_Id))
			return nullptr;

		Class* cls = new Class(std::move(clazz));
		m_Classes.insert({ clazz.m_Id, cls });
		return cls;
	}

	LAVA_CALL_CONV void ClassRegistry::deregisterClass(const std::string& id) {
		auto itr = m_Classes.find(id);
		if (itr != m_Classes.end())
			m_Classes.erase(itr);
	}

	LAVA_CALL_CONV Class* ClassRegistry::getClass(const std::string& id) const {
		auto itr = m_Classes.find(id);
		if (itr != m_Classes.end())
			return itr->second;
		return nullptr;
	}
} // namespace LavaEnv
