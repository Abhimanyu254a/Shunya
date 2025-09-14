#pragma once

#ifdef SHUNYA_CORE_EXPORTS
	#ifdef	SHUNYA_BUILD_DLL	
		#define SHUNYA_CORE_API __declspec(dllexport)

	#else
		#define SHUNYA_CORE_API __declspec(dllimport)
	
	#endif
#else
	#error SHUNYA_CORE_EXPORTS not defined

#endif

