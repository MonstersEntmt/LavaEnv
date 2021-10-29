#pragma once

#include <cstdint>

#define LAVA_IS_FLAG(flags, flag) ((flags & flag) == flag)

#define LAVA_CONFIG_UNKNOWN 0
#define LAVA_CONFIG_DEBUG 1
#define LAVA_CONFIG_RELEASE 2
#define LAVA_CONFIG_DIST 3

#define LAVA_IS_CONFIG_DEBUG LAVA_IS_FLAG(LAVA_CONFIG, LAVA_CONFIG_DEBUG)
#define LAVA_IS_CONFIG_RELEASE LAVA_IS_FLAG(LAVA_CONFIG, LAVA_CONFIG_RELEASE)
#define LAVA_IS_CONFIG_DIST LAVA_IS_FLAG(LAVA_CONFIG, LAVA_CONFIG_DIST)

#define LAVA_SYSTEM_UNKNOWN 0
#define LAVA_SYSTEM_WINDOWS 1
#define LAVA_SYSTEM_MACOSX 2
#define LAVA_SYSTEM_LINUX 3

#define LAVA_IS_SYSTEM_WINDOWS LAVA_IS_FLAG(LAVA_SYSTEM, LAVA_SYSTEM_WINDOWS)
#define LAVA_IS_SYSTEM_MACOSX LAVA_IS_FLAG(LAVA_SYSTEM, LAVA_SYSTEM_MACOSX)
#define LAVA_IS_SYSTEM_LINUX LAVA_IS_FLAG(LAVA_SYSTEM, LAVA_SYSTEM_LINUX)

#define LAVA_TOOLSET_UNKNOWN 0
#define LAVA_TOOLSET_MSVC 1
#define LAVA_TOOLSET_CLANG 2
#define LAVA_TOOLSET_GCC 4

#define LAVA_IS_TOOLSET_MSVC LAVA_IS_FLAG(LAVA_TOOLSET, LAVA_TOOLSET_MSVC)
#define LAVA_IS_TOOLSET_GCC LAVA_IS_FLAG(LAVA_TOOLSET, LAVA_TOOLSET_GCC)
#define LAVA_IS_TOOLSET_CLANG LAVA_IS_FLAG(LAVA_TOOLSET, LAVA_TOOLSET_CLANG)

#define LAVA_PLATFORM_UNKNOWN 0
#define LAVA_PLATFORM_X86 1
#define LAVA_PLATFORM_AMD64 2

#define LAVA_IS_PLATFORM_X86 LAVA_IS_FLAG(LAVA_PLATFORM, LAVA_PLATFORM_X86)
#define LAVA_IS_PLATFORM_AMD64 LAVA_IS_FLAG(LAVA_PLATFORM, LAVA_PLATFORM_AMD64)

namespace Core {
	enum class ELavaConfigFlags : std::uint16_t {
		Unknown = 0,
		Debug   = 1,
		Dist    = 2
	};

	enum class ELavaSystemFlags : std::uint16_t {
		Unknown = 0,
		Windows = 1,
		Macosx  = 2,
		Linux   = 4,
		Unix    = 8
	};

	enum class ELavaToolsetFlags : std::uint16_t {
		Unknown = 0,
		MSVC    = 1,
		Clang   = 2,
		GCC     = 4
	};

	enum class ELavaPlatformFlags : std::uint16_t {
		Unknown = 0,
		X86     = 1,
		AMD64   = 2
	};

#if LAVA_IS_CONFIG_DEBUG
	static constexpr std::uint16_t s_Config = static_cast<std::uint16_t>(ELavaConfigFlags::Debug);
	static constexpr bool s_IsConfigDebug   = true;
	static constexpr bool s_IsConfigDist    = false;
#elif LAVA_IS_CONFIG_RELEASE
	static constexpr std::uint16_t s_Config   = static_cast<std::uint16_t>(ELavaConfigFlags::Debug) | static_cast<std::uint16_t>(ELavaConfigFlags::Dist);
	static constexpr bool s_IsConfigDebug     = true;
	static constexpr bool s_IsConfigDist      = true;
#elif LAVA_IS_CONFIG_DIST
	static constexpr std::uint16_t s_Config   = static_cast<std::uint16_t>(ELavaConfigFlags::Dist);
	static constexpr bool s_IsConfigDebug     = false;
	static constexpr bool s_IsConfigDist      = true;
#else
	static constexpr std::uint16_t s_Config  = static_cast<std::uint16_t>(ELavaConfigFlags::Unknown);
	static constexpr bool s_IsConfigDebug    = false;
	static constexpr bool s_IsConfigDist     = false;
#endif

#if LAVA_IS_SYSTEM_WINDOWS
	static constexpr std::uint16_t s_System = static_cast<std::uint16_t>(ELavaSystemFlags::Windows);
	static constexpr bool s_IsSystemWindows = true;
	static constexpr bool s_IsSystemMacosx  = false;
	static constexpr bool s_IsSystemLinux   = false;
	static constexpr bool s_IsSystemUnix    = false;
#elif LAVA_IS_SYSTEM_MACOSX
	static constexpr std::uint16_t s_System   = static_cast<std::uint16_t>(ELavaSystemFlags::Macosx) | static_cast<std::uint16_t>(ELavaSystemFlags::Unix);
	static constexpr bool s_IsSystemWindows   = false;
	static constexpr bool s_IsSystemMacosx    = true;
	static constexpr bool s_IsSystemLinux     = false;
	static constexpr bool s_IsSystemUnix      = true;
#elif LAVA_IS_SYSTEM_LINUX
	static constexpr std::uint16_t s_System   = static_cast<std::uint16_t>(ELavaSystemFlags::Linux) | static_cast<std::uint16_t>(ELavaSystemFlags::Unix);
	static constexpr bool s_IsSystemWindows   = false;
	static constexpr bool s_IsSystemMacosx    = false;
	static constexpr bool s_IsSystemLinux     = true;
	static constexpr bool s_IsSystemUnix      = true;
#else
	static constexpr std::uint16_t s_System  = static_cast<std::uint16_t>(ELavaConfigFlags::Unknown);
	static constexpr bool s_IsSystemWindows  = false;
	static constexpr bool s_IsSystemMacosx   = false;
	static constexpr bool s_IsSystemLinux    = false;
	static constexpr bool s_IsSystemUnix     = false;
#endif

#if LAVA_IS_TOOLSET_MSVC
	static constexpr std::uint16_t s_Toolset = static_cast<std::uint16_t>(ELavaToolsetFlags::MSVC);
	static constexpr bool s_IsToolsetMSVC    = true;
	static constexpr bool s_IsToolsetClang   = false;
	static constexpr bool s_IsToolsetGCC     = false;
#elif LAVA_IS_TOOLSET_CLANG
	static constexpr std::uint16_t s_Toolset  = static_cast<std::uint16_t>(ELavaToolsetFlags::Clang) | static_cast<std::uint16_t>(ELavaToolsetFlags::GCC);
	static constexpr bool s_IsToolsetMSVC     = false;
	static constexpr bool s_IsToolsetClang    = true;
	static constexpr bool s_IsToolsetGCC      = true;
#elif LAVA_IS_TOOLSET_GCC
	static constexpr std::uint16_t s_Toolset  = static_cast<std::uint16_t>(ELavaToolsetFlags::GCC);
	static constexpr bool s_IsToolsetMSVC     = false;
	static constexpr bool s_IsToolsetClang    = false;
	static constexpr bool s_IsToolsetGCC      = true;
#else
	static constexpr std::uint16_t s_Toolset = static_cast<std::uint16_t>(ELavaConfigFlags::Unknown);
	static constexpr bool s_IsToolsetMSVC    = false;
	static constexpr bool s_IsToolsetClang   = false;
	static constexpr bool s_IsToolsetGCC     = false;
#endif

#if LAVA_IS_PLATFORM_X86
	static constexpr std::uint16_t s_Platform = static_cast<std::uint16_t>(ELavaPlatformFlags::X86);
	static constexpr bool s_IsPlatformX86     = true;
	static constexpr bool s_IsPlatformAMD64   = false;
#elif LAVA_IS_PLATFORM_AMD64
	static constexpr std::uint16_t s_Platform = static_cast<std::uint16_t>(ELavaPlatformFlags::AMD64);
	static constexpr bool s_IsPlatformX86     = false;
	static constexpr bool s_IsPlatformAMD64   = true;
#else
	static constexpr std::uint16_t s_Platform = static_cast<std::uint16_t>(ELavaConfigFlags::Unknown);
	static constexpr bool s_IsPlatformX86     = false;
	static constexpr bool s_IsPlatformAMD64   = false;
#endif
} // namespace Core

#if LAVA_IS_PLATFORM_X86
	#warning "X86 is very buggy and might not work to its fullest potential."
	#if LAVA_IS_TOOLSET_MSVC
		#define LAVA_CALL_CONV __stdcall
	#elif LAVA_IS_TOOLSET_GCC || LAVA_IS_TOOLSET_CLANG
		#define LAVA_CALL_CONV __attribute__((stdcall))
	#else
		#define LAVA_CALL_CONV
		#error The given toolset isn't supported for platform X86, please use either msvc, gcc or clang
	#endif
#elif LAVA_IS_PLATFORM_AMD64
	#warning "I might switch to ms_abi both for compatibility with msvc, though I doubt that I would."
	#if LAVA_IS_TOOLSET_MSVC
		#define LAVA_CALL_CONV __declspec(sysv_abi)
		#error MSVC Currently isn't supported for AMD64 as this requires the use of SystemV AMD64 ABI calling convention which MSVC sadly doesnt support.
	#elif LAVA_IS_TOOLSET_GCC || LAVA_IS_TOOLSET_CLANG
		#define LAVA_CALL_CONV __attribute__((sysv_abi))
	#else
		#define LAVA_CALL_CONV
		#error The given toolset isn't supported for AMD64, please use either gcc or clang.
	#endif
#else
	#error The given platform isn't supported, please request support if necessary.
#endif
