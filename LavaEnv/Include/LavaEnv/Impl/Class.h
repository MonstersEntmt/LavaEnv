#pragma once

#include "LavaEnv/Class.h"

#include <type_traits>
#include <utility>

namespace LavaEnv {
	template <class R, class... Params>
	LAVA_CALL_CONV R Class::invokeStatic(std::string_view id, Params... args) {
		Method* method = getMethod(id);
		if constexpr (!std::is_void_v<R>)
			if (!method)
				throw std::runtime_error("Method '" + std::string(id) + "' not found");
		return method->invokeStatic<R, Params...>(std::forward<Params>(args)...);
	}

	template <class R, class... Params>
	LAVA_CALL_CONV R Class::invoke(std::string_view id, Object* object, Params... args) {
		Method* method = getMethod(id);
		if constexpr (!std::is_void_v<R>)
			if (!method)
				throw std::runtime_error("Method '" + std::string(id) + "' not found");
		return method->invoke<R, Params...>(object, std::forward<Params>(args)...);
	}

	template <class T>
	LAVA_CALL_CONV T& Class::getStatic(std::string_view id) {
		Field* field = getField(id);
		if (!field)
			throw std::runtime_error("Field '" + std::string(id) + "' not found");
		return field->getStatic<T>();
	}

	template <class T>
	LAVA_CALL_CONV T& Class::setStatic(std::string_view id, T value) {
		Field* field = getField(id);
		if (!field)
			throw std::runtime_error("Field '" + std::string(id) + "' not found");
		return field->setStatic<T>(std::forward<T>(value));
	}

	template <class T>
	LAVA_CALL_CONV T& Class::get(std::string_view id, Object* object) {
		Field* field = getField(id);
		if (!field)
			throw std::runtime_error("Field '" + std::string(id) + "' not found");
		return field->get<T>(object);
	}

	template <class T>
	LAVA_CALL_CONV T& Class::set(std::string_view id, Object* object, T value) {
		Field* field = getField(id);
		if (!field)
			throw std::runtime_error("Field '" + std::string(id) + "' not found");
		return field->set<T>(object, std::forward<T>(value));
	}
} // namespace LavaEnv
