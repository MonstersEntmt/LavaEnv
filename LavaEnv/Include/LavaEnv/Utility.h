#pragma once

#include "Core.h"

#include <ostream>
#include <utility>

namespace LavaEnv {
	template <class From, class To>
	union __ub_cast {
	public:
		__ub_cast(From from) : m_From(from) { }
		From m_From;
		To m_To;
	};

	template <class To, class From>
	LAVA_CALL_CONV To __builtin_ub_cast(From from) { return __ub_cast<From, To>(from).m_To; }

	template <class R, class... Params>
	using FunctionPtrT = R (*)(Params...);

	template <class R, class... Params>
	struct FunctionPtr {
	public:
		FunctionPtr() : m_Func(nullptr) { }
		template <class OldR, class... OldParams>
		FunctionPtr(FunctionPtrT<OldR, OldParams...> func) : m_Func(__builtin_ub_cast<FunctionPtrT<R, Params...>>(func)) { }

		template <class NewR, class... NewParams>
		LAVA_CALL_CONV FunctionPtrT<NewR, NewParams...> cast() const { return __builtin_ub_cast<FunctionPtrT<NewR, NewParams...>>(m_Func); }

		LAVA_CALL_CONV R operator()(Params&&... args) const { return m_Func(std::forward<Params>(args)...); }

		LAVA_CALL_CONV void* getPointer() const { return __builtin_ub_cast<void*>(m_Func); }

	private:
		FunctionPtrT<R, Params...> m_Func;
	};

	template <class T>
	struct Flags {
	public:
		constexpr Flags() : m_Value({}) { }
		constexpr Flags(T value) : m_Value(value) { }
		template <class U>
		constexpr Flags(const Flags<U>& flags) : m_Value(flags.m_Value) { }

		LAVA_CALL_CONV constexpr operator T() const { return m_Value; }
		LAVA_CALL_CONV constexpr T getValue() const { return m_Value; }
		LAVA_CALL_CONV constexpr void setValue(T value) { m_Value = value; }

		template <class U>
		LAVA_CALL_CONV constexpr bool isFlag(const Flags<U>& other) const {
			return (m_Value & other.m_Value) == other.m_Value;
		}

		LAVA_CALL_CONV constexpr Flags<T>& operator=(T value) {
			m_Value = value;
			return *this;
		}

		template <class U>
		LAVA_CALL_CONV constexpr Flags<T>& operator=(const Flags<U>& flags) {
			m_Value = flags.m_Value;
			return *this;
		}

		LAVA_CALL_CONV friend constexpr Flags<T> operator~(const Flags<T>& flags) { return ~flags.m_Value; }
		template <class U>
		LAVA_CALL_CONV friend constexpr bool operator==(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value == rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV friend constexpr bool operator!=(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value != rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV friend constexpr bool operator<(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value < rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV friend constexpr bool operator>(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value > rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV friend constexpr bool operator<=(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value <= rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV friend constexpr bool operator>=(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value >= rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV friend constexpr Flags<T> operator&(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value & rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV constexpr Flags<T>& operator&=(Flags<U> other) {
			m_Value &= other.m_Value;
			return *this;
		}
		template <class U>
		LAVA_CALL_CONV friend constexpr Flags<T> operator|(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value | rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV constexpr Flags<T>& operator|=(Flags<U> other) {
			m_Value |= other.m_Value;
			return *this;
		}
		template <class U>
		LAVA_CALL_CONV friend constexpr Flags<T> operator^(Flags<T> lhs, Flags<U> rhs) { return lhs.m_Value ^ rhs.m_Value; }
		template <class U>
		LAVA_CALL_CONV constexpr Flags<T>& operator^=(Flags<U> other) {
			m_Value ^= other.m_Value;
			return *this;
		}
		LAVA_CALL_CONV friend constexpr Flags<T> operator<<(Flags<T> lhs, std::size_t count) { return lhs.m_Value << count; }
		LAVA_CALL_CONV friend constexpr Flags<T> operator>>(Flags<T> lhs, std::size_t count) { return lhs.m_Value >> count; }
		LAVA_CALL_CONV constexpr Flags<T>& operator<<=(std::size_t count) {
			m_Value <<= count;
			return *this;
		}
		LAVA_CALL_CONV constexpr Flags<T>& operator>>=(std::size_t count) {
			m_Value >>= count;
			return *this;
		}

		LAVA_CALL_CONV friend std::ostream& operator<<(std::ostream& stream, Flags<T> flags) { return stream << flags.m_Value; }

	protected:
		T m_Value;
	};
} // namespace LavaEnv
