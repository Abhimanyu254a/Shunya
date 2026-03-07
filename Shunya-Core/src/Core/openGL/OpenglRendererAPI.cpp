#include "SNY-PCH.h"
#include "OpenglRendererAPI.h"

#include "glad/glad.h"


namespace Shunya
{
	void OpenGLRendererAPI::Init()
	{
		SHUNYA_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t breadth, uint32_t length) 
	{
		glViewport(x, y, breadth, length);
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);

	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES,count,GL_UNSIGNED_INT,nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}