#pragma once



namespace Shunya
{
	enum class RendererAPI
	{
		None = 0, // No rendering API								//Done
		OpenGL = 1, // OpenGL Renderering API						//Done
		DirectX12 = 2, // DirectX 12 Rendering API 
		Vulkan = 3, //Vulkan Rendering API
		Metal = 4 // Metal Rendering API
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};

}