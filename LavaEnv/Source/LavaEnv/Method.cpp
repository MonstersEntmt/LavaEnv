#include "LavaEnv/Method.h"

#include <utility>

namespace LavaEnv {
	Method::Method(Class* clazz, RegisterMethod&& method)
	    : m_Flags(method.m_Flags), m_Class(clazz), m_Id(std::move(method.m_Id)), m_FunctionPtr(method.m_FunctionPtr) { }
} // namespace LavaEnv
