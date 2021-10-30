#include "LavaEnv/Field.h"
#include "LavaEnv/Class.h"
#include "LavaEnv/ClassRegistry.h"

#include <utility>

namespace LavaEnv {
	Field::Field(Class& clazz, RegisterField&& field)
	    : m_Class(clazz), m_Flags(field.m_Flags), m_Id(std::move(field.m_Id)), m_Offset(0) {
		std::string_view view = m_Id;
		auto nameEnd          = view.find_first_of(';');
		m_Name                = view.substr(0, nameEnd);

		m_Type = parseType(m_Class.getRegistry(), view.substr(nameEnd + 1));
	}
} // namespace LavaEnv
