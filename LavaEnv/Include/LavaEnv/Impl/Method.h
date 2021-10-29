#pragma once

#include "LavaEnv/Method.h"

namespace LavaEnv {
	template <class R, class... Params>
	LAVA_CALL_CONV R Method::invokeStatic(Params... params) {
		if (!(m_Flags & EMethodFlag::Static))
			throw std::runtime_error("Method '" + m_Id + "' is not static");
		return m_FunctionPtr.cast<R, Params...>()(std::forward<Params>(params)...);
	}

	template <class R, class... Params>
	LAVA_CALL_CONV R Method::invoke(Object* object, Params... params) {
		if (m_Flags & EMethodFlag::Static)
			throw std::runtime_error("Method '" + m_Id + "' is static");
		return m_FunctionPtr.cast<R, Object*, Params...>()(object, std::forward<Params>(params)...);
	}
} // namespace LavaEnv
