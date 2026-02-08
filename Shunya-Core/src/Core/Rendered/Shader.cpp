#include "SNY-PCH.h"
#include "Shader.h"
#include "Core/Rendered/Renderer.h"
#include "Core/openGL/OpenGLShader.h"

namespace Shunya
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 			SHUNYA_CORE_ASSERT(false, "RendererAPI is not found or not Implemented Right now"); return nullptr;


		case RendererAPI::API::OpenGL:  			return std::make_shared<OpenGLShader>(filepath);
		case RendererAPI::API::DirectX12:		SHUNYA_CORE_ASSERT(false, "DirectX12 is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Vulkan: 			SHUNYA_CORE_ASSERT(false, "Vulkan is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Metal: 			SHUNYA_CORE_ASSERT(false, "Metal is not Implemented Right now"); return nullptr;

		}

		SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}


	Ref<Shader> Shader::Create(const std::string& name ,const std::string& vertexSrc, const std::string& fragmentSrc) {

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 			SHUNYA_CORE_ASSERT(false, "RendererAPI is not found or not Implemented Right now"); return nullptr;


		case RendererAPI::API::OpenGL:  			return std::make_shared<OpenGLShader>(name,vertexSrc, fragmentSrc);
		case RendererAPI::API::DirectX12:		SHUNYA_CORE_ASSERT(false, "DirectX12 is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Vulkan: 			SHUNYA_CORE_ASSERT(false, "Vulkan is not Implemented Right now"); return nullptr;
		case RendererAPI::API::Metal: 			SHUNYA_CORE_ASSERT(false, "Metal is not Implemented Right now"); return nullptr;

		}

		SHUNYA_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}


	Ref<Shader>ShaderLibrary::Load(const std::string& filepath) 
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;


	}
	Ref<Shader>ShaderLibrary::Load(const std::string& name, const std::string& filepath) 
	{

		auto shader = Shader::Create(filepath);
		Add(name,shader);
		return shader;

	}
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& Shader)
	{
		SHUNYA_CORE_ASSERT(!Exists(name), "Location :- Shader.cpp :: Shader already exists!");
		m_Shaders[name] = Shader;

	}

	void ShaderLibrary::Add(const Ref<Shader>& Shader)
	{
		auto& name = Shader->GetName();
		Add(name, Shader);
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		SHUNYA_CORE_ASSERT(Exists(name), "Location :- Shader.cpp :: Shader not found!");
		return m_Shaders[name];


	}

	bool ShaderLibrary::Exists(const std::string& name)const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}