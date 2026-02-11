#pragma once

#include "RendererAPI.h"

namespace Shunya
{
	class RendererCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t breadth, uint32_t lenght)
		{
			s_RendererAPI->SetViewport(x,y,breadth,lenght);
		}
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};


}