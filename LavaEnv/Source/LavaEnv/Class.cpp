#include "LavaEnv/Class.h"
#include "LavaEnv/Method.h"
#include "LavaEnv/Object.h"

#include "LavaEnv/Impl/Class.h"
#include "LavaEnv/Impl/Field.h"
#include "LavaEnv/Impl/Method.h"

namespace LavaEnv {
	Class::Class(RegisterClass&& clazz)
	    : m_Flags(clazz.m_Flags), m_Id(std::move(clazz.m_Id)), m_Supers(std::move(clazz.m_Supers)) {
		m_Methods.reserve(clazz.m_Methods.size());
		for (std::size_t i = 0; i < clazz.m_Methods.size(); ++i)
			m_Methods.emplace_back(this, std::move(clazz.m_Methods[i]));

		m_Fields.reserve(clazz.m_Fields.size());
		m_Size       = sizeof(Object);
		m_StaticSize = 0;
		for (std::size_t i = 0; i < clazz.m_Fields.size(); ++i) {
			std::size_t offset = 0;
			auto& field        = clazz.m_Fields[i];
			if (field.m_Flags & EFieldFlag::Static) {
				offset = static_cast<std::uintptr_t>(m_StaticSize);
				m_StaticSize += field.m_Type.getSize();
			} else {
				offset = static_cast<std::uintptr_t>(m_Size);
				m_Size += field.m_Type.getSize();
			}
			auto& res    = m_Fields.emplace_back(this, std::move(clazz.m_Fields[i]));
			res.m_Offset = offset;
		}

		m_StaticData.resize(m_StaticSize, 0);
	}

	LAVA_CALL_CONV Object* Class::instantiate() const {
		Object* object  = reinterpret_cast<Object*>(std::malloc(getSize()));
		object->m_Class = const_cast<Class*>(this);
		auto method     = getMethod("_ctor");
		if (method) method->invoke<void>(object);
		return object;
	}

	LAVA_CALL_CONV void Class::destroy(Object* object) const {
		auto method = getMethod("_dtor");
		if (method) method->invoke<void>(object);
		std::free(object);
	}

	LAVA_CALL_CONV Method* Class::getMethod(std::string_view id) const {
		for (auto& method : m_Methods)
			if (method.getId() == id)
				return const_cast<Method*>(&method);
		return nullptr;
	}

	LAVA_CALL_CONV Field* Class::getField(std::string_view id) const {
		for (auto& field : m_Fields)
			if (field.getId() == id)
				return const_cast<Field*>(&field);
		return nullptr;
	}
} // namespace LavaEnv
