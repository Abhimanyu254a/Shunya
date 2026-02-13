//#pragma once
//
//
//#include<memory>
//
//#ifdef SHUNYA_CORE_EXPORTS
//#if SHUNYA_DYNLIB
//#ifdef	SHUNYA_BUILD_DLL	
//#define SHUNYA_API __declspec(dllexport)
//
//#else
//#define SHUNYA_API __declspec(dllimport)
//
//#endif
//#else
//#define SHUNYA_API
//#endif
//#else
//#error SHUNYA_CORE_EXPORTS not defined
//
//#endif
//
//#ifdef SHUNYA_ENABLE_ASSERTS
//#define	SHUNYA_ASSERT(x, ...) {if(!(x)) {SHUNYA_ERROR("Assertion Failed : {0}", __VA__ARGS__); __debugbreak(); }}
//#define SHUNYA_CORE_ASSERT(x , ...) {if(!x){SHUNYA_CORE_ERROR("Assertion Failed : {0}",__VA__ARGS__); __debugbreak(); } }
//#else
//#define SHUNYA_ASSERT(x, ...)
//#define SHUNYA_CORE_ASSERT(x, ...)
//#endif
//
//
//
//#define BIT(x) (1 << x)
//#define SHUNYA_BIND(fn) std::bind(&fn, this, std::placeholders::_1)
//
//
//
//namespace Shunya
//{
//	template<typename T>
//	using Scope = std::unique_ptr<T>;
//
//
//	template<typename T>
//	using Ref = std::shared_ptr<T>;
//}















#pragma once

#include <memory>

// -------------------------------------------------------------------------
// 1. PLATFORM DETECTION
// -------------------------------------------------------------------------
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define SHUNYA_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define SHUNYA_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define SHUNYA_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define SHUNYA_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define SHUNYA_PLATFORM_LINUX
#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection


// -------------------------------------------------------------------------
// 2. DLL SUPPORT
// -------------------------------------------------------------------------
#ifdef SHUNYA_PLATFORM_WINDOWS
#if SHUNYA_DYNAMIC_LINK
#ifdef SHUNYA_BUILD_DLL
#define SHUNYA_API __declspec(dllexport)
#else
#define SHUNYA_API __declspec(dllimport)
#endif
#else
#define SHUNYA_API
#endif
#else
#error Shunya only supports Windows!
#endif // End of DLL support


// -------------------------------------------------------------------------
// 3. ASSERTS
// -------------------------------------------------------------------------
#ifdef SHUNYA_DEBUG
#define SHUNYA_ENABLE_ASSERTS
#endif

#ifdef SHUNYA_ENABLE_ASSERTS
#define SHUNYA_ASSERT(x, ...) { if(!(x)) { SHUNYA_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SHUNYA_CORE_ASSERT(x, ...) { if(!(x)) { SHUNYA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SHUNYA_ASSERT(x, ...)
#define SHUNYA_CORE_ASSERT(x, ...)
#endif


// -------------------------------------------------------------------------
// 4. MACROS & UTILS
// -------------------------------------------------------------------------
#define BIT(x) (1 << x)

#define SHUNYA_BIND(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Shunya
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}