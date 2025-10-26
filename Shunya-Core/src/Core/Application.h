// Shunya-Core\src\Core\Application.h
// Brief: Defines the main Application class which owns the window, runs the main loop,
//        manages the LayerStack, and dispatches events to layers and overlays.
// Notes: This header uses the SHUNYA_API export macro and relies on other core types:
//        Event, Window, KeyEvent, ApplicationEvent, LayerStack, and Layer.

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
		static Application* s_Instance;
	};

	Application* CreateApplication();

}




