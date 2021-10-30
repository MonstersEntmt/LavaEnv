#pragma once

#include "Flags.h"
#include "Register/Field.h"
#include "Utility.h"

#include <cstdint>

#include <string>

namespace LavaEnv {
	struct Class;
	struct Object;

	struct Field {
	public:
		friend Class;

	public:
		Field(Class& clazz, RegisterField&& field);

		template <class T>
		LAVA_CALL_CONV T& getStatic();
		template <class T>
		LAVA_CALL_CONV T& setStatic(T value);

		template <class T>
		LAVA_CALL_CONV T& get(Object* object);
		template <class T>
		LAVA_CALL_CONV T& set(Object* object, T value);

		LAVA_CALL_CONV auto& getClass() { return m_Class; }
		LAVA_CALL_CONV auto& getClass() const { return m_Class; }

		LAVA_CALL_CONV auto getFlags() const { return m_Flags; }
		LAVA_CALL_CONV auto& getId() const { return m_Id; }
		LAVA_CALL_CONV auto getName() const { return m_Name; }
		LAVA_CALL_CONV auto getType() const { return m_Type; }
		LAVA_CALL_CONV auto getOffset() const { return m_Offset; }

	private:
		Class& m_Class;

		EFieldFlags m_Flags;
		std::string m_Id;
		std::string_view m_Name;
		Type m_Type;
		std::uintptr_t m_Offset;
	};
} // namespace LavaEnv
