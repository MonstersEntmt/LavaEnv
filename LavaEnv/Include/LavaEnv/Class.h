#pragma once

#include "Core.h"
#include "Field.h"
#include "Flags.h"
#include "Method.h"
#include "Object.h"
#include "Register/Class.h"
#include "Type.h"
#include "Utility.h"

#include <string>
#include <string_view>
#include <vector>

namespace LavaEnv {
	class ClassRegistry;

	struct Class {
	public:
		friend ClassRegistry;

	public:
		Class(ClassRegistry& registry);

		template <class R, class... Params>
		LAVA_CALL_CONV R invokeStatic(std::string_view id, Params... args);
		template <class R, class... Params>
		LAVA_CALL_CONV R invoke(std::string_view id, Object* object, Params... args);

		template <class T>
		LAVA_CALL_CONV T& getStatic(std::string_view id);
		template <class T>
		LAVA_CALL_CONV T& setStatic(std::string_view id, T value);
		template <class T>
		LAVA_CALL_CONV T& get(std::string_view id, Object* object);
		template <class T>
		LAVA_CALL_CONV T& set(std::string_view id, Object* object, T value);

		LAVA_CALL_CONV Object* instantiate() const;
		LAVA_CALL_CONV void destroy(Object* object) const;

		LAVA_CALL_CONV Method* getMethod(std::string_view id) const;
		LAVA_CALL_CONV Method* getMethodC(const char* id) const { return getMethod(id); }
		LAVA_CALL_CONV Field* getField(std::string_view id) const;
		LAVA_CALL_CONV Field* getFieldC(const char* id) const { return getField(id); }

		LAVA_CALL_CONV auto& getRegistry() { return m_Registry; }
		LAVA_CALL_CONV auto& getRegistry() const { return m_Registry; }

		LAVA_CALL_CONV auto getFlags() const { return m_Flags; }
		LAVA_CALL_CONV auto& getId() const { return m_Id; }
		LAVA_CALL_CONV auto& getSupers() const { return m_Supers; }
		LAVA_CALL_CONV auto& getMethods() const { return m_Methods; }
		LAVA_CALL_CONV auto& getFields() const { return m_Fields; }

		LAVA_CALL_CONV auto getSize() const { return m_Size; }
		LAVA_CALL_CONV auto getStaticSize() const { return m_StaticSize; }
		LAVA_CALL_CONV auto& getStaticData() { return m_StaticData; }
		LAVA_CALL_CONV auto& getStaticData() const { return m_StaticData; }

	private:
		LAVA_CALL_CONV void setup(RegisterClass&& clazz);

	private:
		ClassRegistry& m_Registry;

		EClassFlags m_Flags;
		std::string m_Id;
		std::vector<Class*> m_Supers;
		std::vector<Method> m_Methods;
		std::vector<Field> m_Fields;

		std::size_t m_Size;
		std::size_t m_StaticSize;
		std::vector<std::uint8_t> m_StaticData;
	};
} // namespace LavaEnv
