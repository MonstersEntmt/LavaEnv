#include "LavaEnv/Field.h"

#include <utility>

namespace LavaEnv {
	Field::Field(Class* clazz, RegisterField&& field)
	    : m_Flags(field.m_Flags), m_Class(clazz), m_Id(std::move(field.m_Id)), m_Type(field.m_Type), m_Offset(0) { }
} // namespace LavaEnv
