#pragma once

#include "LavaEnv/Class.h"
#include "LavaEnv/Object.h"

#include <utility>

namespace LavaEnv {
	template <class R, class... Params>
	LAVA_CALL_CONV R Object::invoke(std::string_view id, Params... args) {
		return m_Class->invoke<R, Params...>(id, this, std::forward<Params>(args)...);
	}

	template <class T>
	LAVA_CALL_CONV T& Object::get(std::string_view id) {
		return m_Class->get<T>(id, this);
	}

	template <class T>
	LAVA_CALL_CONV T& Object::set(std::string_view id, T value) {
		return m_Class->set<T>(id, this, std::forward<T>(value));
	}
} // namespace LavaEnv
