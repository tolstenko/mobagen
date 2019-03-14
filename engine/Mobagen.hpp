#pragma once

#ifndef _WIN32
	#include<signal.h>
#endif // _WIN32

#ifdef _WIN32
	#ifdef _WIN64
		#define PLATFORM64 
	#else
		#define PLATFORM32
	#endif // _WIN64
#elif defined(__linux__)
	#ifdef __x86_64__
		#define PLATFORM64
	#else
		#define PLATFORM32
#endif // __x86_64__
#elif defined(__EMSCRIPTEN__)
	#define PLATFORM32
#elif ANDROID
	#define PLATFORM32

#endif  _WIN32

#define STRINGIZE_2( _ ) #_
#define STRINGIZE( _ ) STRINGIZE_2( _ )

namespace Mobagen
{
	typedef char i8;
	typedef unsigned char u8;
	typedef short i16;
	typedef unsigned short u16;
	typedef int i32;
	typedef unsigned int u32;
	typedef unsigned int uint;

	#ifdef _WIN32
		typedef long long i64;
		typedef unsigned long long u64;
		#define MOBAGEN_ALIGN_BEGIN(_align) __declspec(align(_align))
		#define MOBAGEN_ALIGN_END(_align)
	#elif defined __EMSCRIPTEN__
		typedef long long i64;
		typedef unsigned long long u64;
		#define MOBAGEN_ALIGN_BEGIN(_align)
		#define MOBAGEN_ALIGN_END(_align) __attribute__((aligned(_align)))
	#else
	#ifdef PLATFORM64
		typedef long i64;
		typedef unsigned long u64;
	#else
		typedef long long i64;
		typedef unsigned long long u64;
	#endif // PLATFORM64
	#define MOBAGEN_ALIGN_BEGIN(_align)
	#define MOBAGEN_ALIGN_END(_align) __attribute__((aligned(_align)))

#endif // _WIN32


#ifdef PLATFORM64
		typedef u64 uintptr;
#else
		typedef u32 uintptr;
#endif // PLATFORM64

static_assert(sizeof(uintptr) == sizeof(void*), "Incorrect size of uintptr");
static_assert(sizeof(i64) == 8, "Incorrect size of i64");
static_assert(sizeof(i32) == 4, "Incorrect size of i32");
static_assert(sizeof(i16) == 2, "Incorrect size of i16");
static_assert(sizeof(i8) == 1, "Incorrect size of i8");

const u32 MAX_PATH_LENGTH = 260;

struct Entity
{
	int index;
	bool operator==(const Entity& rhs) const { return rhs.index == index; }
	bool operator<(const Entity& rhs) const { return rhs.index < index; }
	bool operator>(const Entity& rhs) const { return rhs.index > index; }
	bool operator!=(const Entity& rhs) const { return rhs.index != index; }
	bool isValid() const { return index >= 0; }

};

struct ComponentType
{
	enum { MAX_TYPES_COUNT = 64 };

	int index;
	bool operator==(const ComponentType& rhs) const { return rhs.index == index; }
	bool operator<(const ComponentType& rhs) const { return rhs.index < index; }
	bool operator>(const ComponentType& rhs) const { return rhs.index > index; }
	bool operator!=(const ComponentType& rhs) const { return rhs.index != index; }
};
const ComponentType INVALID_COMPONENT_TYPE = { -1 };
const Entity INVALID_ENTITY = { -1 };

template <typename T, int count> int lengthOf(const T(&)[count])
{
	return count;
};


} 

#ifndef ASSERT
#ifdef NDEBUG
#define ASSERT(x) { false ? (void)(x) : (void)0; }
#else
#ifdef _WIN32
#define MOBAGEN_DEBUG_BREAK() __debugbreak()
#else
#define MOBAGEN_DEBUG_BREAK()  raise(SIGTRAP) 
#endif
#define ASSERT(x) do { const volatile bool mobagen_assert_b____ = !(x); if(mobagen_assert_b____) MOBAGEN_DEBUG_BREAK(); } while (false)
#endif
#endif


#ifdef _WIN32
#define MOBAGEN_FINAL final
#define MOBAGEN_LIBRARY_EXPORT __declspec(dllexport)
#define MOBAGEN_LIBRARY_IMPORT __declspec(dllimport)
#define MOBAGEN_FORCE_INLINE __forceinline
#define MOBAGEN_RESTRICT __restrict
#define MOBAGEN_ATTRIBUTE_USED
#else 
#define MOBAGEN_FINAL final
#define MOBAGEN_LIBRARY_EXPORT __attribute__((visibility("default")))
#define MOBAGEN_LIBRARY_IMPORT 
#define MOBAGEN_FORCE_INLINE __attribute__((always_inline)) inline
#define MOBAGEN_RESTRICT __restrict__
#define MOBAGEN_ATTRIBUTE_USED __attribute__((used))
#endif

#ifdef STATIC_PLUGINS
#define MOBAGEN_ENGINE_API
#elif defined BUILDING_ENGINE
#define MOBAGEN_ENGINE_API MOBAGEN_LIBRARY_EXPORT
#else
#define MOBAGEN_ENGINE_API MOBAGEN_LIBRARY_IMPORT
#endif

#ifdef STATIC_PLUGINS
#define MOBAGEN_EDITOR_API
#elif defined BUILDING_EDITOR
#define MOBAGEN_EDITOR_API MOBAGEN_LIBRARY_EXPORT
#else
#define MOBAGEN_EDITOR_API MOBAGEN_LIBRARY_IMPORT
#endif


#ifdef STATIC_PLUGINS
#define MOBAGEN_RENDERER_API
#elif defined BUILDING_RENDERER
#define MOBAGEN_RENDERER_API MOBAGEN_LIBRARY_EXPORT
#else
#define MOBAGEN_RENDERER_API MOBAGEN_LIBRARY_IMPORT
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4251)
#pragma warning(disable : 4996)
#if _MSC_VER == 1900 
#pragma warning(disable : 4091)
#endif
#endif

