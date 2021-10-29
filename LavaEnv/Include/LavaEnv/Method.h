#pragma once

#include "Flags.h"
#include "Register/Method.h"
#include "Utility.h"

#include <string>

namespace LavaEnv {
	struct Class;
	struct Object;

	struct Method {
	public:
		friend Class;

	public:
		Method(Class* clazz, RegisterMethod&& method);

		template <class R, class... Params>
		LAVA_CALL_CONV R invokeStatic(Params... params);

		template <class R, class... Params>
		LAVA_CALL_CONV R invoke(Object* object, Params... params);

		LAVA_CALL_CONV auto getFlags() const { return m_Flags; }
		LAVA_CALL_CONV auto getClass() const { return m_Class; }
		LAVA_CALL_CONV auto& getId() const { return m_Id; }
		LAVA_CALL_CONV auto& getFunctionPtr() const { return m_FunctionPtr; }

	private:
		EMethodFlags m_Flags;
		Class* m_Class;
		std::string m_Id;
		FunctionPtr<void> m_FunctionPtr;
	};
} // namespace LavaEnv
