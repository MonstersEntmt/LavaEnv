#pragma once

#include "LavaEnv/Flags.h"
#include "LavaEnv/Type.h"
#include "LavaEnv/Utility.h"

#include <cstdint>

#include <string>

namespace LavaEnv {
	struct Class;

	struct RegisterField {
	public:
		EFieldFlags m_Flags;
		std::string m_Id;
		Type m_Type;
	};
} // namespace LavaEnv
