#include "SNY-PCH.h"

#include "OpenglBuffer.h"
#include <glad/glad.h>

namespace Shunya
{
	OpenglVertexBuffer::OpenglVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size,vertices, GL_STATIC_DRAW);
	}
	OpenglVertexBuffer::~OpenglVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenglVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void OpenglVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	///////////////////////////////////////////////////////////////////////


	OpenglIndexBuffer::OpenglIndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenglIndexBuffer::~OpenglIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenglIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenglIndexBuffer::Unbind() const
	{

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}