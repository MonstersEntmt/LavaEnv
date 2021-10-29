#pragma once

#include "Utility.h"

namespace LavaEnv {
	struct Class;

	enum class EPrimitiveType : std::uint32_t {
		Int8   = 0,
		Int16  = 1,
		Int32  = 2,
		Int64  = 3,
		UInt8  = 4,
		UInt16 = 5,
		UInt32 = 6,
		UInt64 = 7,
		Char8  = 8,
		Char16 = 9,
		Char32 = 10,
		Float  = 11,
		Double = 12,
		None   = ~0U
	};

	std::size_t getSizeOfPrimitiveType(EPrimitiveType primitiveType);

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
} // namespace LavaEnv
