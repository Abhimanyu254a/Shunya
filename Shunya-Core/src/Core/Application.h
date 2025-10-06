#pragma once

#include "Core.h"
#include "Events/Event.h"

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


