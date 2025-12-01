#include "SNY-PCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Shunya
{
	

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		if (m_WindowHandle == nullptr) {
			SHUNYA_CORE_ERROR("OpenGLContext created with NULL GLFWwindow*");
		}
		else {
			SHUNYA_CORE_INFO("OpenGLContext created with valid window handle");
		}
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SHUNYA_CORE_ASSERT(status, "Failed to initialize Glad!");

	
		const GLubyte* vendor = glGetString(GL_VENDOR);
		const GLubyte* renderer = glGetString(GL_RENDERER); // CORREC	T: GL_RENDERER, not GL_RENDER


		SHUNYA_CORE_INFO("GPU Vendor   : {0}", vendor ? reinterpret_cast<const char*>(vendor) : "NULL");
		SHUNYA_CORE_INFO("GPU Renderer : {0}", renderer ? reinterpret_cast<const char*>(renderer) : "NULL");
		
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
	

}