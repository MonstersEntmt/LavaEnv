#include "LavaEnv/Type.h"
#include "LavaEnv/Class.h"

namespace LavaEnv {
	std::size_t getSizeOfPrimitiveType(EPrimitiveType primitiveType) {
		switch (primitiveType) {
		case EPrimitiveType::Int8:
			return 1;
		case EPrimitiveType::Int16:
			return 2;
		case EPrimitiveType::Int32:
			return 4;
		case EPrimitiveType::Int64:
			return 8;
		case EPrimitiveType::UInt8:
			return 1;
		case EPrimitiveType::UInt16:
			return 2;
		case EPrimitiveType::UInt32:
			return 4;
		case EPrimitiveType::UInt64:
			return 8;
		case EPrimitiveType::Char8:
			return 1;
		case EPrimitiveType::Char16:
			return 2;
		case EPrimitiveType::Char32:
			return 4;
		case EPrimitiveType::Float:
			return 4;
		case EPrimitiveType::Double:
			return 8;
		default:
			return 0;
		}
	}

	Type::Type()
	    : m_Class(nullptr), m_PrimitiveType(EPrimitiveType::None) { }

	Type::Type(EPrimitiveType primitiveType)
	    : m_Class(nullptr), m_PrimitiveType(primitiveType) { }

	Type::Type(Class* clazz)
	    : m_Class(clazz), m_PrimitiveType(EPrimitiveType::None) { }

	LAVA_CALL_CONV std::size_t Type::getSize() const {
		return m_Class ? m_Class->getSize() : getSizeOfPrimitiveType(m_PrimitiveType);
	}
} // namespace LavaEnv
