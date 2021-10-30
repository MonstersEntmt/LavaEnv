#pragma once

#include "LavaEnv/Class.h"
#include "LavaEnv/Field.h"

namespace LavaEnv {
	template <class T>
	LAVA_CALL_CONV T& Field::getStatic() {
		if (!(m_Flags & EFieldFlag::Static))
			throw std::runtime_error("Field '" + m_Id + "' is not static");
		return *reinterpret_cast<T*>(m_Class.getStaticData().data() + m_Offset);
	}

	template <class T>
	LAVA_CALL_CONV T& Field::setStatic(T value) {
		return getStatic<T>() = std::forward<T>(value);
	}

	template <class T>
	LAVA_CALL_CONV T& Field::get(Object* object) {
		if (m_Flags & EFieldFlag::Static)
			throw std::runtime_error("Field '" + m_Id + "' is static");
		return *reinterpret_cast<T*>(reinterpret_cast<std::uint8_t*>(object) + m_Offset);
	}

	template <class T>
	LAVA_CALL_CONV T& Field::set(Object* object, T value) {
		return get<T>(object) = std::forward<T>(value);
	}
} // namespace LavaEnv
