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
#include "imGui/imguiLayer.h"


#include "Core/Rendered/Shader.h"
#include "Core/Rendered/Buffer.h"
#include "Core/openGL/OpenGLVertexArray.h"

#include "Rendered/OrthographicCamera.h"

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
		imGUILayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
		

		//unsigned int m_VertexArray;
		static Application* s_Instance;
		std::shared_ptr<Shader>m_Shader;
		std::shared_ptr<VertexArray>m_VertexArray;

		std::shared_ptr<Shader>m_BlueShader;
		std::shared_ptr<VertexArray>m_SquareVA;

		OrthographicCamera m_Camera;
	};

	Application* CreateApplication();

}




