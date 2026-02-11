#pragma once



#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Shunya
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DirectX12 = 2, Vulkan = 3,Metal = 4
		};
	public:
		virtual void Init() = 0;


		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t breadth, uint32_t length ) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;


		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}