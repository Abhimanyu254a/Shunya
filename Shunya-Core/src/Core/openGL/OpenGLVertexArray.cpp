#include "SNY-PCH.h"

#include "OpenGLVertexArray.h"
#include "Core/Rendered/Buffer.h"
#include "glad/glad.h"

namespace Shunya
{
	static uint32_t ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case  Shunya::ShaderDataType::Bool:  return 4;
			case  Shunya::ShaderDataType::Float:  return 4;
			case  Shunya::ShaderDataType::Float2:  return 4 * 2;
			case  Shunya::ShaderDataType::Float3:  return 4 * 3;
			case  Shunya::ShaderDataType::Float4:  return 4 * 4;
			case  Shunya::ShaderDataType::Mat3:  return 4 * 3 * 3;
			case  Shunya::ShaderDataType::Mat4:  return 4 * 4 * 4;
			case  Shunya::ShaderDataType::Int:  return 4;
			case  Shunya::ShaderDataType::Int2:  return 4 * 2;
			case  Shunya::ShaderDataType::Int3:  return 4 * 3;
			case  Shunya::ShaderDataType::Int4:  return 4 * 4;
			case  Shunya::ShaderDataType::None:  return 1;

		}

		SHUNYA_CORE_ASSERT(false, "Unknow ShaderDataType");
		return 0;
	}

		OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
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
    
    uint32_t index = 0;
    for (const auto& element : layout)
    {
        // ENABLE THE ATTRIBUTE (Essential!)
        glEnableVertexAttribArray(index);

        // TELL OPENGL HOW TO READ THE DATA
        // This links the specific 'index' (like location=0) to the data structure
        glVertexAttribPointer(
            index,                          // location = 0, 1, etc.
            element.GetComponentCount(),    // vec3 = 3, vec2 = 2
            ShaderDataTypeToOpenGLBaseType(element.Type), // GL_FLOAT, etc.
            element.Normalized ? GL_TRUE : GL_FALSE,      // Is it normalized?
            layout.GetStride(),             // Stride (The total size of one vertex)
            (const void*)(uintptr_t)element.Offset       // Offset (Where this specific data starts)
        );
        index++;

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