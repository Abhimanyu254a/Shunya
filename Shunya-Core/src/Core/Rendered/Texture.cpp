#include "SNY-PCH.h"
#include <memory>
#include "Renderer.h"
#include "Core/openGL/OpenGLTexture.h"
#include "Texture.h"

namespace Shunya {

	Ref<Texture2D> Texture2D::Create(uint32_t breadth, uint32_t length) {

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 			SHUNYA_CORE_ASSERT(false, "RendererAPI is not found or not Implemented Right now"); return nullptr;


		case RendererAPI::API::OpenGL:  			return CreateRef<OpenGLTexture2D>(breadth,length);
		case RendererAPI::API::DirectX12:		SHUNYA_CORE_ASSERT(false, "DirectX12 is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Vulkan: 			SHUNYA_CORE_ASSERT(false, "Vulkan is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Metal: 			SHUNYA_CORE_ASSERT(false, "Metal is not Implemented Right now"); return nullptr;

		}

		SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}

	
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		

			switch (Renderer::GetAPI())
			{
			case RendererAPI::API::None: 			SHUNYA_CORE_ASSERT(false, "RendererAPI is not found or not Implemented Right now"); return nullptr;


			case RendererAPI::API::OpenGL:  			return CreateRef<OpenGLTexture2D>(path);
			case RendererAPI::API::DirectX12:		SHUNYA_CORE_ASSERT(false, "DirectX12 is not Implemented Right now"); return nullptr;
			case RendererAPI::API::Vulkan: 			SHUNYA_CORE_ASSERT(false, "Vulkan is not Implemented Right now"); return nullptr;
			case RendererAPI::API::Metal: 			SHUNYA_CORE_ASSERT(false, "Metal is not Implemented Right now"); return nullptr;

			}

			SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;

	}

	



}