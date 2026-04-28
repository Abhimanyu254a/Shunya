#include "SNY-PCH.h"
#include "OpenGLUniformBuffer.h"
#include <glad/glad.h>

namespace Shunya {

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
	{
		SHUNYA_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		SHUNYA_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		SHUNYA_PROFILE_FUNCTION();
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}

}