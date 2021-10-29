#pragma once

#include "Field.h"
#include "LavaEnv/Flags.h"
#include "LavaEnv/Utility.h"
#include "Method.h"

#include <string>
#include <vector>

namespace LavaEnv {
	struct Class;

	struct RegisterClass {
	public:
		EClassFlags m_Flags;
		std::string m_Id;
		std::vector<Class*> m_Supers;
		std::vector<RegisterMethod> m_Methods;
		std::vector<RegisterField> m_Fields;
	};
} // namespace LavaEnv
