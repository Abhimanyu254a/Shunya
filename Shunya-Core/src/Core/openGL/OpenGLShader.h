//#pragma once
//
//#include "Core/Rendered/Shader.h"
//#include <string.h>
//#include <unordered_map>
//#include <glm/glm.hpp>
//#include <vector>
//#include <string>
//
//// typedef unsigned int GLenum;
//
//// namespace Shunya
//// {
//// 	class OpenGLShader : public Shader
//// 	{
//// 	public:
//// 		OpenGLShader(const std::string& filepath);
//// 		OpenGLShader(const std::string& name ,const std::string& vertexSrc, const std::string& fragmentSrc);
//// 		virtual ~OpenGLShader();
//
//
//// 		virtual void Bind() const override;
//// 		virtual void UnBind() const override;
//
//// 		virtual void SetInt(const std::string& name, int value) override;
//// 		virtual void SetIntArray(const std::string& name, int* value, uint32_t count) override;
//// 		virtual void SetFloat(const std::string& name ,float value)  override ;
//// 		virtual void SetFloat3(const std::string& name ,const glm::vec3& value)  override ;
//// 		virtual void SetFloat4(const std::string& name ,const glm::vec4& value) override ;
//// 		virtual void SetMat4(const std::string& name ,const glm::mat4& value)   override;
//
//// 		virtual const std::string& GetName() const override { return m_Name; }
//
//// 		void UploadUniformInt(const std::string& name, int value);
//// 		void UploadUniformIntArray(const std::string& name, int* value, uint32_t count);
//		
//// 		void UploadUniformFloat(const std::string& name, float value);
//// 		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
//// 		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
//// 		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
//		
//// 		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
//// 		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
//
//// 	private:
//// 		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
//// 		std::string ReadFile(const std::string& filepath);
//// 		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
//// 	private:
//// 		uint32_t m_RendererID = 0;
//// 		std::string m_Name;
//
//// 	};
//// }
//
//
//
//
//// Forward declare GLenum to avoid bringing glad into header if possible, or include glad
//typedef unsigned int GLenum; 
//
//namespace Shunya {
//
//	class OpenGLShader : public Shader
//	{
//	public:
//		OpenGLShader(const std::string& filepath);
//		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
//		virtual ~OpenGLShader();
//
//		virtual void Bind() const; // Assuming override
//		virtual void UnBind() const; // Assuming override
//
//		virtual void SetInt(const std::string& name, int value);
//		virtual void SetIntArray(const std::string& name, int* values, uint32_t count);
//		virtual void SetFloat(const std::string& name, float value);
//		virtual void SetFloat2(const std::string& name, const glm::vec2& value);
//		virtual void SetFloat3(const std::string& name, const glm::vec3& value);
//		virtual void SetFloat4(const std::string& name, const glm::vec4& value);
//		virtual void SetMat4(const std::string& name, const glm::mat4& value);
//
//		virtual const std::string& GetName() const { return m_Name; }
//
//		void UploadUniformInt(const std::string& name, int value);
//		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
//		void UploadUniformFloat(const std::string& name, float value);
//		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
//		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
//		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
//		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
//		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
//
//	private:
//		std::string ReadFile(const std::string& filepath);
//		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
//
//		void CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources);
//		void CompileOrGetOpenGLBinaries();
//		void CreateProgram();
//		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
//
//	private:
//		uint32_t m_RendererID;
//		std::string m_FilePath;
//		std::string m_Name;
//
//		std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
//		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;
//		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
//	};
//}










#pragma once
#include "Core/Rendered/Shader.h" // Ensure this path matches your abstract Shader path
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <string>

typedef unsigned int GLenum;

namespace Shunya {

	// FIXED: "public Shader" ensures polymorphism works for Create()
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		void CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources);
		void CompileOrGetOpenGLBinaries();
		void CreateProgram();
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);

	private:
		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;
		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	};
}