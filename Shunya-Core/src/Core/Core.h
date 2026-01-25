#pragma once


#include<memory>

#ifdef SHUNYA_CORE_EXPORTS
#if SHUNYA_DYNLIB
#ifdef	SHUNYA_BUILD_DLL	
#define SHUNYA_API __declspec(dllexport)

#else
#define SHUNYA_API __declspec(dllimport)

#endif
#else
#define SHUNYA_API
#endif
#else
#error SHUNYA_CORE_EXPORTS not defined

#endif

#ifdef SHUNYA_ENABLE_ASSERTS
#define	SHUNYA_ASSERT(x, ...) {if(!(x)) {SHUNYA_ERROR("Assertion Failed : {0}", __VA__ARGS__); __debugbreak(); }}
#define SHUNYA_CORE_ASSERT(x , ...) {if(!x){SHUNYA_CORE_ERROR("Assertion Failed : {0}",__VA__ARGS__); __debugbreak(); } }
#else
#define SHUNYA_ASSERT(x, ...)
#define SHUNYA_CORE_ASSERT(x, ...)
#endif



#define BIT(x) (1 << x)
#define SHUNYA_BIND(fn) std::bind(&fn, this, std::placeholders::_1)



namespace Shunya
{
	template<typename T>
	using Scope = std::unique_ptr<T>;


	template<typename T>
	using Ref = std::shared_ptr<T>;
}