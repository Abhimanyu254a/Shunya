#include "SNY-PCH.h"
#include "Log.h"

#include <vector>
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"

namespace Shunya
{
#define BIND_FUN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SHUNYA_CORE_ASSERT(!s_Instance, "Applicational ready exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_FUN(OnEvent));


		m_ImGuiLayer = new imGUILayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);



		float vertices[3 * 3] = {
			// X      Y      Z
			-0.5f, -0.5f, 0.0f, // Bottom Left
			 0.5f, -0.5f, 0.0f, // Bottom Right
			 0.0f,  0.5f, 0.0f  // Top Center
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

        std::string vertexSrc = R"(
            #version 410 core
            
            layout(location = 0) in vec3 a_Position;

            // Define an output variable to send data to the Fragment Shader
            out vec3 v_Position;

            void main()
            {
                // Pass the raw position data to the next stage
                v_Position = a_Position;
                
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

 
        std::string fragmentSrc = R"(
            #version 410 core
            
            layout(location = 0) out vec4 color;

            // This 'in' variable must match the 'out' variable from the Vertex Shader exactly
            in vec3 v_Position;

            void main()
            {
                // MATHEMATICAL MAGIC:
                // v_Position values range from approx -0.5 to 0.5.
                // Colors need to be 0.0 to 1.0.
                // (v_Position * 0.5) + 0.5 shifts the range perfectly.
                
                // X controls Red, Y controls Green, Z controls Blue
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";




		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();

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