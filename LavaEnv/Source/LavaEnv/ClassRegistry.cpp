#include "LavaEnv/ClassRegistry.h"

namespace LavaEnv {
	LAVA_CALL_CONV Class* ClassRegistry::loadClass(std::string_view id) {
		for (auto classLoader : m_ClassLoaders)
			if (classLoader->canLoadClass(id))
				return classLoader->loadClass(id);
		return nullptr;
	}

	LAVA_CALL_CONV Class* ClassRegistry::registerClass(RegisterClass&& clazz) {
		if (getClass(clazz.m_Id))
			return nullptr;

		Class* cls = new Class(*this);
		m_Classes.insert({ clazz.m_Id, cls });
		cls->setup(std::move(clazz));
		return cls;
	}

	LAVA_CALL_CONV void ClassRegistry::deregisterClass(const std::string& id) {
		auto itr = m_Classes.find(id);
		if (itr != m_Classes.end())
			m_Classes.erase(itr);
	}

	LAVA_CALL_CONV void ClassRegistry::registerClassLoader(ClassLoader& classLoader) {
		m_ClassLoaders.insert(&classLoader);
	}

	LAVA_CALL_CONV void ClassRegistry::deregisterClassLoader(ClassLoader& classLoader) {
		m_ClassLoaders.erase(&classLoader);
	}

	LAVA_CALL_CONV Class* ClassRegistry::getClass(const std::string& id) {
		auto itr = m_Classes.find(id);
		if (itr != m_Classes.end())
			return itr->second;
		return loadClass(id);
	}
} // namespace LavaEnv
