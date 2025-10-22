#include "SNY-PCH.h"

#include <glad/glad.h>
#include "WindowMaker.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"

namespace Shunya {
	static bool is_GLFWInitialized = false;

	static void GLFWErrorCallBack(int error, const char* description)
	{
		SHUNYA_CORE_ERROR("{0}\n {1}", error, description);
	}
	
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowMaker(props);
	}

	WindowMaker::WindowMaker(const WindowProps& props)
	{
		Init(props);
	}

	WindowMaker::~WindowMaker(){ }

	void WindowMaker::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Length = props.Height;
		m_Data.Width = props.Breadth;

		SHUNYA_CORE_INFO("Creating a Window Of properties {0}, {1}, {2}", props.Title, props.Breadth, props.Height);

		if (!is_GLFWInitialized) {
			int window_start = glfwInit();
			SHUNYA_CORE_ASSERT(window_start, "Couldn't initalize GLFW")
			glfwSetErrorCallback(GLFWErrorCallBack);
			is_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)props.Breadth, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window); 
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SHUNYA_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width,int length) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 

			data.Width = width;
			data.Length = length;
			
			WindowResizeEvent event(width, length);
			data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
			
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowClosedEvent(event);
				data.EventCallback(event);

			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonRelasedEvent event(button);
					data.EventCallback(event);
					break;

				}
				}

		});
		
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double Xoffset, double Yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)Xoffset, (float)Yoffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});


			







	}



		void WindowMaker::Shutdown()
		{
			glfwDestroyWindow(m_Window);
		}
		void WindowMaker::OnUpdate()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}
		void WindowMaker::SetVSync(bool Enabled)
		{
			if (Enabled)
				glfwSwapInterval(1);
			else
				glfwSwapInterval(0);

			m_Data.VSync = Enabled;
		}

		bool WindowMaker::IsVSync() const
		{
			return m_Data.VSync;
		}


	
	

	
}