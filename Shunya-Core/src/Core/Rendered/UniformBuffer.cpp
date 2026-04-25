#include "SNY-PCH.h"
#include "UniformBuffer.h"

#include "Core/Rendered/Renderer.h"
#include "Core/openGL/OpenGLUniformBuffer.h"

namespace Shunya {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SHUNYA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}