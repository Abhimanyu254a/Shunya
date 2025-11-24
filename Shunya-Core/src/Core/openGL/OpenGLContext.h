#pragma once

#include "SNY-PCH.h"

#include "Core/Rendered/GraphicsContext.h"

struct GLFWwindow;

namespace Shunya
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* m_WindowHandle);
		virtual void Init() override ;
		virtual void SwapBuffers() override;


	private:
		GLFWwindow* m_WindowHandle;

	};
}