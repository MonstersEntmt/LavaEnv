#pragma once

#include "Flags.h"
#include "Register/Method.h"
#include "Type.h"
#include "Utility.h"

#include <string>
#include <string_view>
#include <vector>

namespace LavaEnv {
	struct Class;
	struct Object;

	struct Method {
	public:
		friend Class;

	public:
		Method(Class& clazz, RegisterMethod&& method);

		template <class R, class... Params>
		LAVA_CALL_CONV R invokeStatic(Params... params);

		template <class R, class... Params>
		LAVA_CALL_CONV R invoke(Object* object, Params... params);

		LAVA_CALL_CONV auto& getClass() { return m_Class; }
		LAVA_CALL_CONV auto& getClass() const { return m_Class; }

		LAVA_CALL_CONV auto getFlags() const { return m_Flags; }
		LAVA_CALL_CONV auto& getId() const { return m_Id; }
		LAVA_CALL_CONV auto getName() const { return m_Name; }
		LAVA_CALL_CONV auto getReturnType() const { return m_ReturnType; }
		LAVA_CALL_CONV auto& getParameterTypes() const { return m_ParameterTypes; }
		LAVA_CALL_CONV auto& getFunctionPtr() const { return m_FunctionPtr; }

	private:
		Class& m_Class;

		EMethodFlags m_Flags;
		std::string m_Id;
		std::string_view m_Name;
		Type m_ReturnType;
		std::vector<Type> m_ParameterTypes;
		FunctionPtr<void> m_FunctionPtr;
	};
} // namespace LavaEnv
