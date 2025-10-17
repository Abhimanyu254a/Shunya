#include "SNY-PCH.h"
#include "Log.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Shunya
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());

	}
	Application::~Application()
	{
	}



	void Application::Run()
	{

		while (true) {
			m_Window->OnUpdate();
		}
	}

	
}