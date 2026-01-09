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
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
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
    SHUNYA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    // GET THE LAYOUT YOU JUST FIXED
    const auto& layout = vertexBuffer->GetLayout();
	SHUNYA_CORE_INFO("Vertex Buffer has no layout!");
    
    uint32_t m_VertexBufferIndex = 0;
    for (const auto& element : layout)
    {
        // ENABLE THE ATTRIBUTE (Essential!)
        glEnableVertexAttribArray(m_VertexBufferIndex);

        // TELL OPENGL HOW TO READ THE DATA
        // This links the specific 'index' (like location=0) to the data structure
        glVertexAttribPointer(
			m_VertexBufferIndex,                          // location = 0, 1, etc.
            element.GetComponentCount(),    // vec3 = 3, vec2 = 2
            ShaderDataTypeToOpenGLBaseType(element.Type), // GL_FLOAT, etc.
            element.Normalized ? GL_TRUE : GL_FALSE,      // Is it normalized?
            layout.GetStride(),             // Stride (The total size of one vertex)
            (const void*)(uintptr_t)element.Offset       // Offset (Where this specific data starts)
        );
		m_VertexBufferIndex++;

    }

    m_VertexBuffers.push_back(vertexBuffer);
}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}