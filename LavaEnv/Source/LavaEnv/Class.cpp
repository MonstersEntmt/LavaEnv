#include "LavaEnv/Class.h"
#include "LavaEnv/Method.h"
#include "LavaEnv/Object.h"

#include "LavaEnv/Impl/Class.h"
#include "LavaEnv/Impl/Field.h"
#include "LavaEnv/Impl/Method.h"

namespace LavaEnv {
	Class::Class(ClassRegistry& registry)
	    : m_Registry(registry), m_Size(0), m_StaticSize(0) { }

	Class::~Class() {
		auto method = getMethod("_sdtor;()V");
		if (method)
			method->invokeStatic<void, Class*>(this);
	}

	LAVA_CALL_CONV Object* Class::instantiate() const {
		Object* object = reinterpret_cast<Object*>(std::malloc(getSize()));

		// TODO(MarcasRealAccount): Hacky solution to set Class& inside Object*
		*reinterpret_cast<Class**>(object) = const_cast<Class*>(this);

		auto method = getMethod("_ctor;(L" + m_Id + ";)V");
		if (method)
			method->invoke<void>(object);
		return object;
	}

	LAVA_CALL_CONV void Class::destroy(Object* object) const {
		auto method = getMethod("_dtor;(L" + m_Id + ";)V");
		if (method)
			method->invoke<void>(object);
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

	LAVA_CALL_CONV void Class::setup(RegisterClass&& clazz) {
		m_Flags  = clazz.m_Flags;
		m_Id     = std::move(clazz.m_Id);
		m_Supers = std::move(clazz.m_Supers);

		m_Methods.reserve(clazz.m_Methods.size());
		for (std::size_t i = 0; i < clazz.m_Methods.size(); ++i)
			m_Methods.emplace_back(*this, std::move(clazz.m_Methods[i]));

		m_Fields.reserve(clazz.m_Fields.size());
		m_Size             = sizeof(Object);
		m_StaticSize       = 0;
		std::size_t offset = 0;
		for (std::size_t i = 0; i < clazz.m_Fields.size(); ++i) {
			auto& res = m_Fields.emplace_back(*this, std::move(clazz.m_Fields[i]));
			if (res.m_Flags & EFieldFlag::Static) {
				offset = static_cast<std::uintptr_t>(m_StaticSize);
				m_StaticSize += res.getType().getSize();
			} else {
				offset = static_cast<std::uintptr_t>(m_Size);
				m_Size += res.getType().getSize();
			}
			res.m_Offset = offset;
		}

		m_StaticData.resize(m_StaticSize, 0);

		// TODO(MarcasRealAccount): Add support for pointer types.
		auto method = getMethod("_sctor;()V");
		if (method)
			method->invokeStatic<void, Class*>(this);
	}
} // namespace LavaEnv
