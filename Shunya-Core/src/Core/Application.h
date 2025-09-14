#pragma once

#include "Core.h"

namespace Shunya
{
	class SHUNYA_CORE_API Application
	{
	public:
		Application();
		virtual ~Application();


		void Run();
	};

	Application* CreateApplication();

}


