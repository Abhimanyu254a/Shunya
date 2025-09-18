#pragma once

#include "Core.h"

namespace Shunya
{
	class SHUNYA_API Application
	{
	public:
		Application();
		virtual ~Application();


		void Run();
	};

	Application* CreateApplication();

}


