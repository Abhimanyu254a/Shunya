#include "SNY-PCH.h"
#include "VertexArray.h"
#include "Core/openGL/OpenGLVertexArray.h"
#include "Core/Rendered/Renderer.h"

namespace Shunya
{
	VertexArray* VertexArray::Create() {

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 			SHUNYA_CORE_ASSERT(false, "RendererAPI is not found or not Implemented Right now"); return nullptr;


		case RendererAPI::API::OpenGL:  			return new OpenGLVertexArray();
		case RendererAPI::API::DirectX12:		SHUNYA_CORE_ASSERT(false, "DirectX12 is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Vulkan: 			SHUNYA_CORE_ASSERT(false, "Vulkan is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Metal: 			SHUNYA_CORE_ASSERT(false, "Metal is not Implemented Right now"); return nullptr;

		}

		SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}
}