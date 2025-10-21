#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Core/LayerStack.h"
#include "Layer.h"

namespace Shunya
{
	class SHUNYA_API Application
	{
	public:
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* Overlay);


		void Run();
	private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	Application* CreateApplication();

}


