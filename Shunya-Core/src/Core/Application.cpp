#include "SNY-PCH.h"
#include "Log.h"

#include <vector>
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

#include "Rendered/RendererAPI.h"
#include "Rendered/Renderer.h"
#include "Rendered/RendererCommand.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/openGL/OpenGLVertexArray.h"
#include "Rendered/OrthographicCamera.h"
#include "input.h"

namespace Shunya
{
#define BIND_FUN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;


Application::Application()
	
{
	SHUNYA_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_FUN(OnEvent));
	/*m_Window->SetVSync(false);*/  // to set up the frame rate with the respect of the Screen

	m_ImGuiLayer = new imGUILayer();
	PushOverlay(m_ImGuiLayer);

}
	Application::~Application()
	{
	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
		Overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_FUN(OnWindowClose));

		SHUNYA_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
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

			float time = (float)glfwGetTime();
			Timestamp timestep = time - m_LastTimeFrame;
			m_LastTimeFrame = time;


			 
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;


		return true;
	}

}