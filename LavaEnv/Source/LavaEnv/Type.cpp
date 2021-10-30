#include "LavaEnv/Type.h"
#include "LavaEnv/Class.h"
#include "LavaEnv/ClassRegistry.h"

namespace LavaEnv {
	LAVA_CALL_CONV std::size_t getSizeOfPrimitiveType(EPrimitiveType primitiveType) {
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
		case EPrimitiveType::Float32:
			return 4;
		case EPrimitiveType::Float64:
			return 8;
		case EPrimitiveType::Void:
			return 0;
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

	LAVA_CALL_CONV Type parseType(ClassRegistry& registry, std::string_view typeString) {
		if (typeString.empty())
			return {};

		if (typeString[0] == 'L') {
			auto typeEnd = typeString.find_first_of(';');
			return registry.getClass(std::string(typeString.substr(1, typeEnd - 1)));
		} else if (typeString == "I1") {
			return EPrimitiveType::Int8;
		} else if (typeString == "I2") {
			return EPrimitiveType::Int16;
		} else if (typeString == "I4") {
			return EPrimitiveType::Int32;
		} else if (typeString == "I8") {
			return EPrimitiveType::Int64;
		} else if (typeString == "UI1") {
			return EPrimitiveType::UInt8;
		} else if (typeString == "UI2") {
			return EPrimitiveType::UInt16;
		} else if (typeString == "UI4") {
			return EPrimitiveType::UInt32;
		} else if (typeString == "UI8") {
			return EPrimitiveType::UInt64;
		} else if (typeString == "C1") {
			return EPrimitiveType::Char8;
		} else if (typeString == "C2") {
			return EPrimitiveType::Char16;
		} else if (typeString == "C4") {
			return EPrimitiveType::Char32;
		} else if (typeString == "F4") {
			return EPrimitiveType::Float32;
		} else if (typeString == "F8") {
			return EPrimitiveType::Float64;
		} else if (typeString == "V") {
			return EPrimitiveType::Void;
		} else {
			return {};
		}
	}
} // namespace LavaEnv
