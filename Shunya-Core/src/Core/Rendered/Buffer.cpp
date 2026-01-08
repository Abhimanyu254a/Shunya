#include "SNY-PCH.h"

#include "Core/Rendered/Buffer.h"
#include "Core/openGL/OpenglBuffer.h"
#include "Core/Rendered/Renderer.h"

namespace Shunya
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: 			SHUNYA_CORE_ASSERT(false, "RendererAPI is not found or not Implemented Right now"); return nullptr;

		case RendererAPI::OpenGL:  			return new OpenglVertexBuffer(vertices, size);
		case RendererAPI::DirectX12:		SHUNYA_CORE_ASSERT(false, "DirectX12 is not Implemented Right now"); return nullptr;
		case RendererAPI::Vulkan: 			SHUNYA_CORE_ASSERT(false, "Vulkan is not Implemented Right now"); return nullptr;
		case RendererAPI::Metal: 			SHUNYA_CORE_ASSERT(false, "Metal is not Implemented Right now"); return nullptr;

		}

		SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: 			SHUNYA_CORE_ASSERT(false, "RendererAPI is not found or not Implemented Right now"); return nullptr;
		case RendererAPI::OpenGL:  			return new OpenglIndexBuffer(indices, size);
		case RendererAPI::DirectX12:		SHUNYA_CORE_ASSERT(false, "DirectX12 is not Implemented Right now"); return nullptr;
		case RendererAPI::Vulkan: 			SHUNYA_CORE_ASSERT(false, "Vulkan is not Implemented Right now"); return nullptr;
		case RendererAPI::Metal: 			SHUNYA_CORE_ASSERT(false, "Metal is not Implemented Right now"); return nullptr;

		}

		SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}
}