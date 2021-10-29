#pragma once

#include "Utility.h"

#include <cstddef>
#include <cstdint>

namespace LavaEnv {
	struct EFieldFlags : public Flags<std::uint16_t> {
	public:
		constexpr EFieldFlags() : Flags({}) { }
		constexpr EFieldFlags(std::uint16_t value) : Flags(value) { }
		template <class U>
		constexpr EFieldFlags(const Flags<U>& flags) : Flags(flags) { }

		LAVA_CALL_CONV std::string toString() const;

		LAVA_CALL_CONV friend std::ostream& operator<<(std::ostream& stream, EFieldFlags flags) { return stream << flags.toString(); }
	};
	struct EMethodFlags : public Flags<std::uint16_t> {
	public:
		constexpr EMethodFlags() : Flags({}) { }
		constexpr EMethodFlags(std::uint16_t value) : Flags(value) { }
		template <class U>
		constexpr EMethodFlags(const Flags<U>& flags) : Flags(flags) { }

		LAVA_CALL_CONV std::string toString() const;

		LAVA_CALL_CONV friend std::ostream& operator<<(std::ostream& stream, EMethodFlags flags) { return stream << flags.toString(); }
	};
	struct EClassFlags : public Flags<std::uint16_t> {
	public:
		constexpr EClassFlags() : Flags({}) { }
		constexpr EClassFlags(std::uint16_t value) : Flags(value) { }
		template <class U>
		constexpr EClassFlags(const Flags<U>& flags) : Flags(flags) { }

		LAVA_CALL_CONV std::string toString() const;

		LAVA_CALL_CONV friend std::ostream& operator<<(std::ostream& stream, EClassFlags flags) { return stream << flags.toString(); }
	};

	namespace EFieldFlag {
		static constexpr EFieldFlags None   = 0x0U;
		static constexpr EFieldFlags Static = 0x1U;
	} // namespace EFieldFlag

	namespace EMethodFlag {
		static constexpr EMethodFlags None   = 0x0U;
		static constexpr EMethodFlags Static = 0x1U;
	} // namespace EMethodFlag

	namespace EClassFlag {
		static constexpr EClassFlags None   = 0x0U;
		static constexpr EClassFlags Static = 0x1U;
	} // namespace EClassFlag
} // namespace LavaEnv
