#include "SNY-PCH.h"
#include "Log.h"

#include <vector>
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Shunya
{
#define BIND_FUN(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_FUN(OnEvent)) ;
  
	}
	Application::~Application()
	{
	} 

	 
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_FUN(OnWindowClose));

		SHUNYA_CORE_TRACE("{0}", e.ToString());
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

	}

	void Application::Run()
	{
		while (m_Running)
		{

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;


		return true;
	}
	
}