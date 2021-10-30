#pragma once

#include "Utility.h"

#include <string_view>

namespace LavaEnv {
	struct Class;
	class ClassRegistry;

	enum class EPrimitiveType : std::uint32_t {
		Int8    = 0x00'00'00'00U,
		Int16   = 0x00'00'00'01U,
		Int32   = 0x00'00'00'02U,
		Int64   = 0x00'00'00'03U,
		UInt8   = 0x00'00'01'00U,
		UInt16  = 0x00'00'01'01U,
		UInt32  = 0x00'00'01'02U,
		UInt64  = 0x00'00'01'03U,
		Char8   = 0x00'00'02'00U,
		Char16  = 0x00'00'02'01U,
		Char32  = 0x00'00'02'02U,
		Float32 = 0x00'00'03'00U,
		Float64 = 0x00'00'03'01U,
		Void    = 0xFF'FF'FF'FEU,
		None    = 0xFF'FF'FF'FFU
	};

	LAVA_CALL_CONV std::size_t getSizeOfPrimitiveType(EPrimitiveType primitiveType);

	struct Type {
	public:
		Type();
		Type(EPrimitiveType primitiveType);
		Type(Class* clazz);

		LAVA_CALL_CONV std::size_t getSize() const;

		LAVA_CALL_CONV bool isPrimitive() const { return !m_Class; }
		LAVA_CALL_CONV auto getClass() const { return m_Class; }
		LAVA_CALL_CONV auto getPrimitiveType() const { return m_PrimitiveType; }

	private:
		Class* m_Class;
		EPrimitiveType m_PrimitiveType;
	};

	LAVA_CALL_CONV Type parseType(ClassRegistry& registry, std::string_view typeString);
} // namespace LavaEnv
