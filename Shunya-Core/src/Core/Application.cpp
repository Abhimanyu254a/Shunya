#include "SNY-PCH.h"
#include "Log.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"


namespace Shunya
{
	Application::Application()
	{

	}
	Application::~Application()
	{
	}



	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		SHUNYA_TRACE(e.ToString());

		while (true);
	}

	
}