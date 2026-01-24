#include "SNY-PCH.h"
#include "Shader.h"
#include "Core/openGL/OpenGLShader.h"
#include "Core/Rendered/Renderer.h"

namespace Shunya
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 			SHUNYA_CORE_ASSERT(false, "RendererAPI is not found or not Implemented Right now"); return nullptr;


		case RendererAPI::API::OpenGL:  			return new OpenGLShader(vertexSrc, fragmentSrc);
		case RendererAPI::API::DirectX12:		SHUNYA_CORE_ASSERT(false, "DirectX12 is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Vulkan: 			SHUNYA_CORE_ASSERT(false, "Vulkan is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Metal: 			SHUNYA_CORE_ASSERT(false, "Metal is not Implemented Right now"); return nullptr;

		}

		SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}
}