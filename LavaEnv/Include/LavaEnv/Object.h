#pragma once

#include "Utility.h"

#include <string_view>

namespace LavaEnv {
	struct Class;

	struct Object {
	public:
		LAVA_CALL_CONV void destroy();

		template <class R, class... Params>
		LAVA_CALL_CONV R invoke(std::string_view id, Params... args);

		template <class T>
		LAVA_CALL_CONV T& get(std::string_view id);
		template <class T>
		LAVA_CALL_CONV T& set(std::string_view id, T value);

		LAVA_CALL_CONV auto getClass() const { return m_Class; }
		LAVA_CALL_CONV std::uint8_t* getData() const { return reinterpret_cast<std::uint8_t*>(const_cast<Object*>(this)) + sizeof(Object); }

	private:
		Object()  = delete;
		~Object() = delete;

	public:
		Class* m_Class;
	};
} // namespace LavaEnv
