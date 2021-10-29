#pragma once

#include "LavaEnv/Flags.h"
#include "LavaEnv/Utility.h"

#include <string>

namespace LavaEnv {
	struct RegisterMethod {
	public:
		EMethodFlags m_Flags;
		std::string m_Id;
		FunctionPtr<void> m_FunctionPtr;
	};
} // namespace LavaEnv
