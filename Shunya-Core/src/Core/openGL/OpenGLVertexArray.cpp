#include "SNY-PCH.h"

#include "OpenGLVertexArray.h"
#include "Core/Rendered/Buffer.h"
#include "glad/glad.h"

namespace Shunya
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Shunya::ShaderDataType::Float:    return GL_FLOAT;
		case Shunya::ShaderDataType::Float2:   return GL_FLOAT;
		case Shunya::ShaderDataType::Float3:   return GL_FLOAT;
		case Shunya::ShaderDataType::Float4:   return GL_FLOAT;
		//{
		//	glEnableVertexAttribArray(m_VertexBufferIndex);
		//	glVertexAttribPointer(m_VertexBufferIndex,
		//		element.GetComponentCount(),
		//		ShaderDataTypeToOpenGLBaseType(element.Type),
		//		element.Normalized ? GL_TRUE : GL_FALSE,
		//		layout.GetStride(),
		//		(const void*)element.Offset);
		//	m_VertexBufferIndex++;
		//	break;
		//}
		case Shunya::ShaderDataType::Mat3:     return GL_FLOAT;
		case Shunya::ShaderDataType::Mat4:     return GL_FLOAT;
		case Shunya::ShaderDataType::Int:      return GL_INT;
		case Shunya::ShaderDataType::Int2:     return GL_INT;
		case Shunya::ShaderDataType::Int3:     return GL_INT;
		case Shunya::ShaderDataType::Int4:     return GL_INT;
		case Shunya::ShaderDataType::Bool:     return GL_BOOL;
		}

		SHUNYA_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		SHUNYA_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		SHUNYA_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		SHUNYA_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		SHUNYA_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}
	/*void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		SHUNYA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index++);
			glVertexAttribPointer(index++,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(uintptr_t)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}*/

	// In OpenGLVertexArray.cpp

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		SHUNYA_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		SHUNYA_CORE_ASSERT(layout.GetElement().size(), "Vertex Buffer has no layout!");

		uint32_t m_VertexBufferIndex = 0;
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				// FLOATS: Use glVertexAttribPointer (NO 'I')
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)(uintptr_t)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				// INTEGERS (EntityID): Use glVertexAttribIPointer (WITH 'I')
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)(uintptr_t)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			default:
				SHUNYA_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		SHUNYA_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}